<?php

/**
 * @file
 * Drush integration for the devel module.
 */

/**
 * Implements hook_drush_command().
 */
function somi_drush_command() {
  $items['somi-manager'] = array(
    'description' => dt('Check access to node (e.g. reception door) in context of SOMI.'),
    'arguments' => array(
      '$id' => dt('Id of the rfid tag that attempting access the node.'),
    ),
  );
  $items['somi-month-reset-user-accounts'] = array(
    'description' => dt('Resets All Users Debet Accounts According Month Limits Settings.'),
  );

  return $items;
}

/**
 * Logs somi events.
 * @param $context
 * @param $access
 */
function somi_log_event($context, $access) {
  // Prevent fault if log failed (missing table, etc).
  try {
    $log_fq_limit = $context['time'] - 3;
    // seconds, log couldn't be created frequently more than onece per 3 seconds.
    $query = db_query("select * from log WHERE uid = '{$context['uid']}' AND access >= $log_fq_limit;");

    if (!$query->rowCount()) {
      db_query("insert into log (id, uid, access) values('{$context['rfid']}', '{$context['uid']}', {$context['time']});");
    }
  }
  catch (Exception $e) {
    // Do nothing.
  }

  somi_realtime_board_trigger($context);
  somi_slack_webhook_trigger($context['uid'], $context, $access);
}

/**
 * A command callback.
 */
function drush_somi_month_reset_user_accounts() {
  // Set the batch operations.
  $batch = array(
    'title' => dt('Updating users debet accounts'),
    'operations' => array(
      array(
        'somi_month_reset_user_accounts_batch',
        array()
      ),
    ),
  );
  batch_set($batch);
  drush_backend_batch_process();
}

/**
 * @param $context
 */
function somi_month_reset_user_accounts_batch(&$context) {
  if (!isset($context['results']['uids'])) {
    $query = db_select('users', 'u');
    $query->addField('u', 'uid');
    $query->condition('status', 1);
    $uids = $query->execute()->fetchCol();

    $context['results']['uids'] = $uids;
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($uids);

    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];

    $context['message'] = 'Preparing data for operations, found ' . $context['sandbox']['max'] . ' active users.';

    return;
  }

  $chunk = array_slice($context['results']['uids'], $context['sandbox']['progress'], 30);
  $source_uid = 1;
  $roles = user_roles();
  $msg = '';

  foreach ($chunk as $uid) {
    if ($account = user_load($uid)) {
      switch (TRUE) {
        case array_search('top', $roles) !== FALSE && user_has_role(array_search('top', $roles), $account):
          $message = t($msg . ' для роли :role', [':role' => 'top']);
          $limit = SOMI_TOP_MONTH_ACCOUNT_BALANCE_LIMIT;
          break;

        case array_search('core', $roles) !== FALSE && user_has_role(array_search('core', $roles), $account):
          $message = t($msg . ' для роли :role', [':role' => 'core']);
          $limit = SOMI_CORE_MONTH_ACCOUNT_BALANCE_LIMIT;
          break;

        case array_search('active', $roles) !== FALSE && user_has_role(array_search('active', $roles), $account):
          $message = t($msg . ' для роли :role', [':role' => 'active']);
          $limit = SOMI_ACTIVE_MONTH_ACCOUNT_BALANCE_LIMIT;
          break;

        default:
          $message = t($msg . ' для роли :role', [':role' => 'авторизованный пользователь']);
          $limit = SOMI_REGULAR_MONTH_ACCOUNT_BALANCE_LIMIT;
          break;
      }

      foreach (somi_get_cron_account_balance_tids() as $account_tid) {
        if ($currency = taxonomy_term_load($account_tid)->name) {
          $account_msg = "Ежемесячное обновление пользовательского счета $currency" . $message;
          $balance = somi_get_user_account_balance($account->uid, $account_tid);

          if ($balance < $limit) {
            $new_amount = $limit - $balance;
          }
          elseif ($balance > $limit) {
            $new_amount = -1 * ($balance - $limit);
          }

          if (!empty($new_amount)) {
            somi_add_user_account_balance($account->uid, $new_amount, $account_tid, $account_msg, $source_uid);
            unset($new_amount);
          }
        }
      }
    }

    $context['sandbox']['progress']++;

    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    $context['message'] = 'Updating Users Debet Accounts (' . $context['sandbox']['progress'] . ' of ' . $context['sandbox']['max'] . ' users).';
  }
}

/**
 * A command callback.
 */
function drush_somi_manager($id = NULL) {
  $time = time();

  // If no path is provided by the user, set our default path.
  $rank = '[0-9ABCDEF]{2,2}';
  $validate_pattern = "/$rank:$rank:$rank:$rank/";

  if (!empty($id) && preg_match($validate_pattern, $id)) {
    ob_clean();

    module_load_include('inc', 'somi', 'somi.pages');

    $account = somi_get_user_by_rfid($id);
    $rfid = somi_get_rfid_by_id($id);
    $access = somi_access_handler($id);

    if ($access) {
      echo "granted";
    }
    else {
      echo "denied";
    }

    if ($account && $rfid) {
      $context = array(
        'uid' => $account->uid,
        'rfid' => $rfid->nid,
        'name' => $account->name,
        'time' => $time,
        'mail' => $account->mail,
        'card' => $id,
      );

      somi_log_event($context, $access);
    }
  }
}

/**
 * Slack Web Hooks Integration.
 */
function somi_slack_webhook_trigger($id, $context, $status) {
  // PHP apache doesn't able deal with pcntl functions, only CDG or CLI modes.
  // so do it in the same process for web request access loging :'C.
  if (function_exists('pcntl_fork')) {
    $pid = pcntl_fork();

    // Parent process should immediately response to hardware.
    if ($pid === -1 || $pid > 0) {
      return;
    }

    // Allow parent process (udpsrv to response avr MCU immediately without waiting curl delay).
    fclose(STDIN);
    fclose(STDOUT);
    fclose(STDERR);
  }

  // Child process continues HTTP Slack API invocation.
  $slack_webhook_url = array(
    "https://hooks.slack.com/services/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",
    "https://hooks.slack.com/services/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",
  );

  $somi_base_url = 'http://somibo.qajedi.ru';

  $slack_bot_name = "Smart Office";

  $i20_logo_url = "http://i20.biz/sites/all/themes/gki20/logo.png";

  $somi_chart_url = "$somi_base_url/admin/somi/chart";
  $somi_user_chart_url = "$somi_base_url/admin/somi/chart";
  $somi_user_chart_url = is_numeric($id) ? "$somi_user_chart_url/$id" : $somi_chart_url;

  $somi_user_name = $context['name'];
  $somi_user_mail_hash = md5($context['mail']);

  $color = $status ? '' : '"color": "danger",';
  $status_msg = $status ? 'доступ разрешен' : 'доступ запрещен';
  $node = "ресепшен";
  $event = "запрос доступа";
  $rfid_tag = $context['card'];
  $time = date('H:i:s d.m', $context['time']);
  $short_time = date('H:i:s', $context['time']);

  if ($rfid = somi_get_rfid_by_id($rfid_tag)) {
    $rfid_color = somi_get_device_color_by_nid($rfid->nid, TRUE);
    $rfid_device = somi_get_device_type_by_nid($rfid->nid, TRUE);
  }
  else {
    $rfid_color = '-';
    $rfid_device = 'карта';
  }

  $slack_payload = <<< EOS
{
	"icon_url":	"$i20_logo_url",
	"username":	"$slack_bot_name",
	"text": "<$somi_chart_url|$short_time  /  $somi_user_name  /  $node>",
	"mrkdwn": true,
	"attachments":	[
		{
    	$color
			"thumb_url":	"http://www.gravatar.com/avatar/$somi_user_mail_hash",
			"author_name":	"$somi_user_name",
			"author_link":	"$somi_user_chart_url",
			"author_icon":	"http://www.gravatar.com/avatar/$somi_user_mail_hash",
			"fields": [
				{
					"title": "Идентификатор:",
					"value": "$id",
					"short": true
				},
				{
					"title": "Идентификатор устройства:",
					"value": "$rfid_tag",
					"short": true
				},
				{
					"title": "Тип устройства:",
					"value": "$rfid_device",
					"short": true
				},
				{
					"title": "Цвет устройства:",
					"value": "$rfid_color",
					"short": true
				},
				{
					"title": "Событие:",
					"value": "$event",
					"short": true
				},
				{
					"title": "Узел:",
					"value": "$node",
					"short": true
				},
				{
					"title": "Статус:",
					"value": "$status_msg",
					"short": true
				},
				{
					"title": "Время:",
					"value": "$time",
					"short": true
				}
			]

		}
	]
}
EOS;

  $params = http_build_query(['payload' => $slack_payload]);

  // Send event to all listeners.
  foreach ($slack_webhook_url as $webhook_url) {
    $defaults = array(
      CURLOPT_URL => $webhook_url,
      CURLOPT_POST => TRUE,
      CURLOPT_POSTFIELDS => $params,
    );

    $ch = curl_init();

    curl_setopt_array($ch, $defaults);

    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_HTTPHEADER, array(
      'Content-type: application/x-www-form-urlencoded',
    ));

    curl_exec($ch);
    curl_close($ch);
  }

  if (function_exists('pcntl_fork')) {
    exit;
  }
}

/**
 * Slack Web Hooks Integration.
 */
function somi_realtime_board_trigger($context) {
  // PHP apache doesn't able deal with pcntl functions, only CDG or CLI modes.
  // so do it in the same process for web request access loging :'C.
  if (function_exists('pcntl_fork')) {
    $pid = pcntl_fork();

    // Parent process should immediately response to hardware.
    if ($pid === -1 || $pid > 0) {
      return;
    }

    // Allow parent process (udpsrv to response avr MCU immediately without waiting curl delay).
    fclose(STDIN);
    fclose(STDOUT);
    fclose(STDERR);
  }

  // Child process continues HTTP Slack API invocation.
  $node_js_url = array(
    "http://127.0.0.1:8300",
  );

  $nodejs_payload = array(
    'id' => $context['uid'],
    'info' => date('H:i:s', time()),
    'class' => 'active',
  );

  $data_string = json_encode($nodejs_payload);
  // Send event to all listeners.
  foreach ($node_js_url as $nodejs_url) {
    $defaults = array(
      CURLOPT_URL => $nodejs_url,
      CURLOPT_POST => TRUE,
      CURLOPT_POSTFIELDS => $data_string,
    );

    $ch = curl_init();

    curl_setopt_array($ch, $defaults);

    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_HTTPHEADER, array(
      'Content-type: application/json',
      'Content-Length: ' . strlen($data_string),
    ));

    curl_exec($ch);
    curl_close($ch);
  }

  if (function_exists('pcntl_fork')) {
    exit;
  }
}