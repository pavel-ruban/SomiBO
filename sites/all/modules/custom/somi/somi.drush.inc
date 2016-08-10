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

  $items['somi-check-birthdays'] = array(
    'description' => dt('Checks birthdays and note slack channel about upcoming events.'),
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
      db_query("insert into log (id, uid, access, node_id) values('{$context['rfid']}', '{$context['uid']}', {$context['time']}, {$context['rfid_node']});");
    }
  }
  catch (Exception $e) {
    // Do nothing.
  }

  somi_realtime_board_trigger($context);
  somi_slack_webhook_trigger($context['uid'], $context, $access);
}

/**
 * Logs somi events.
 * @param $context
 * @param $access
 */
function drush_somi_check_birthdays() {
  // Set the batch operations.
  $batch = array(
    'title' => dt('Checking users birthdays'),
    'operations' => array(
      array(
        'drush_somi_check_birthdays_batch',
        array()
      ),
    ),
  );
  batch_set($batch);
  drush_backend_batch_process();
}

/**
 * Logs somi events.
 * @param $context
 * @param $access
 */
function drush_somi_check_birthdays_batch(&$context) {
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
  static $logo = NULL;

  if (!$logo) $logo = taxonomy_term_load(41);

  foreach ($chunk as $uid) {
    if (!empty($uid) && $uid != 1 && is_numeric($uid) && ($account = user_load($uid))) {
      $is_birthday = somi_is_birthday_upcoming($account);

      if (!empty($account->field_department[LANGUAGE_NONE][0]['target_id'])) {
        if ($dep = taxonomy_term_load($account->field_department[LANGUAGE_NONE][0]['target_id'])) {
          $dep_name = $dep->name;
        }
      }

      if ($is_birthday === 'today') {
        somi_sent_custom_message_trigger(
          [
            'uid' => $account->uid,
            'image' => somi_get_gravatar_image_url_by_mail($account->mail),
//            'icon' => 'http://www.freeiconspng.com/uploads/birthday-icon-9.png',
            'icon' => 'http://somibo.qajedi.ru/sites/default/files/styles/thumbnail/public/notification_icons/logo-i20_1.png?itok=9rhuI33A',
//            'icon' => image_style_url('thumbnail', $logo->field_icon[LANGUAGE_NONE][0]['uri']),
            'header' => t('Поздравляем с днём рождения!'),
            'channel' => 'general',
            'color' => '#daf6ff',
            'text' => t(
              'Сегодня у @name @dep день рождения! Поздравляем и желаем успехов во всех начинаниях!',
              [
                '@name' => $account->name,
                '@dep' => !empty($dep_name) ? "из отдела $dep_name" : ''
              ]
            ),
          ]
        );
      }
    }

    $context['sandbox']['progress']++;

    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    $context['message'] = 'Checking users birthdays (' . $context['sandbox']['progress'] . ' of ' . $context['sandbox']['max'] . ' users).';
  }
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
          $limit = somi_get_role_account_month_limit('top');
          break;

        case array_search('core', $roles) !== FALSE && user_has_role(array_search('core', $roles), $account):
          $message = t($msg . ' для роли :role', [':role' => 'core']);
          $limit = somi_get_role_account_month_limit('core');
          break;

        case array_search('active', $roles) !== FALSE && user_has_role(array_search('active', $roles), $account):
          $message = t($msg . ' для роли :role', [':role' => 'active']);
          $limit = somi_get_role_account_month_limit('active');
          break;

        default:
          $message = t($msg . ' для роли :role', [':role' => 'авторизованный пользователь']);
          $limit = somi_get_role_account_month_limit('regular');
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
function drush_somi_manager($id = NULL, $rfid_node) {
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

    $rfid_node = hexdec($rfid_node);
    watchdog(WATCHDOG_DEBUG, "card:$id node:$rfid_node");
    if ($account && $rfid) {
      $context = array(
        'uid' => $account->uid,
        'rfid' => $rfid->nid,
        'rfid_node' => $rfid_node,
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
  $rfid_node = somi_get_rfid_pcd_node_by_id($context['rfid_node']);
  if (!empty($rfid_node->title)) {
    $node = $rfid_node->title;
  }

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

/**
 * Slack Integration.
 */
function somi_sent_custom_message_trigger($context) {
  // PHP apache doesn't able deal with pcntl functions, only CDG or CLI modes.
  // so do it in the same process for web request access login in :'C.
  if (0 && function_exists('pcntl_fork')) {
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
    "http://127.0.0.1:" . SOMI_NODEJS_HTTP_SERVER_PORT,
  );

  $nodejs_payload = array(
    'id' => $context['uid'],
    'image' => $context['image'],
    'icon' => $context['icon'],
    'header' => $context['header'],
    'color' => $context['color'],
    'text' => $context['text'],
    'action' => 'notification',
    'channel' => $context['channel'],
    'type' => 'birthday',
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

  if (0 && function_exists('pcntl_fork')) {
    exit;
  }
}