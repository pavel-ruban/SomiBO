<?php

/**
 * @file
 */

/**
 * Page callback: Displays add taxonomy links for available content types.
 */
function somi_taxonomy_add_page($check = FALSE) {
  static $items;

  if (empty($items)) {
    $vocs = taxonomy_vocabulary_get_names();
    $items = array();
    foreach ($vocs as $machine_name => $voc) {
      if (user_access("edit terms in $machine_name")) {
        $items[] = array(
          'localized_options  ' => [],
          'description' => '',
          'href' => "admin/structure/taxonomy/{$machine_name}/add",
          'title' => "Add {$voc->name}",
        );
      }
    }
  }

  if (!empty($check)) {
    return count($items);
  }
  else {
    if (count($items) == 1) {
      drupal_goto("admin/structure/taxonomy/{$machine_name}/add");
    } else {
      return theme('node_add_list', array('content' => $items));
    }
  }
}

/**
 * Provides CSV export.
 */
function somi_accounts_csv_export_form($form, &$form_state) {
  global $base_url;

  $currencies = [];

  foreach (somi_get_currencies() as $currency) {
    $currencies[somi_get_currency_tid($currency)] = $currency;
  }


  $form['totals'] = [
    '#type' => 'checkbox',
    '#title' => t('Только суммы.'),
    '#default_value' => TRUE,
    '#desctiption' => t('Будут показаны только текущие остатки.'),
  ];

  $form['currency'] = [
    '#type' => 'checkboxes',
    '#title' => t('Валюты.'),
    '#desctiption' => t('Если не выбрана ни одна опция, то все опции будут экспортированы'),
    '#options' => $currencies,
    '#sufix' => '<br />',
  ];

  $form['destination'] = [
    '#type' => 'hidden',
    '#value' => '/admin/content/accounts',
  ];

  $form['user'] = [
    '#type' => 'entityreference',
    '#title' => t('Пользователи'),
    '#era_entity_type' => 'user',
    '#era_cardinality' => -1,
    '#desctiption' => t('Можно выбрать несколько пользователей через запятую, если поле пусто все пользователи будут выгружены'),
  ];

  $form['submit'] = [
    '#type' => 'submit',
    '#value' => t('Скачать'),
  ];

  return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function somi_accounts_csv_export_form_submit($form, &$form_state) {

  // Set the batch operations.
  $batch = array(
    'title' => t('Экпрот данных'),
    'error_message' => t('При экспортировании случилась ошибка.'),
    'init_message' => t('Подготовка данных'),
    'finished' => 'somi_accounts_csv_export_batch_finished',
    'operations' => array(
      array(
        'somi_accounts_csv_export_batch',
        array([
          'users' => !empty($form_state['values']['user'])
            ? $form_state['values']['user']
            : [],
          'currencies' => !empty($form_state['values']['currency'])
            ? array_filter($form_state['values']['currency'], function($v) {
              return !empty($v);
            })
            : [],
          'totals' => !empty($form_state['values']['totals'])
            ? TRUE
            : FALSE
        ]),
      ),
    ),
    'progressive' => TRUE,
    'file' => SOMI_MODULE_PATH . '/somi.pages.inc',
  );

  batch_set($batch);

  batch_process(array($form_state['values']['destination'], array()));
}

/**
 * @param $context
 */
function somi_accounts_csv_export_batch_finished($status, $results) {
  if (!empty($status)) {
    $filename = drupal_realpath(file_directory_temp()) . '/' . $results['filename'];

    file_put_contents($filename, $results['csv_data']);

    $_SESSION['csv_export_filename'] = $filename;
  }
}

/**
 * @param $context
 */
function somi_accounts_csv_export_batch($filters, &$context) {
  $context['finished'] = 0;

  if (!isset($context['sandbox']['currencies'])) {
    $currencies = [];

    foreach (somi_get_currencies() as $currency) {
      $currencies[somi_get_currency_tid($currency)] = $currency;
    }

    $context['sandbox']['currencies'] = $currencies;
    $context['finished'] = 0;

    return;
  }

  if (!isset($context['sandbox']['transactions'])) {
    $users = [];

    if (!empty($filters['users'])) {
      $users = array_keys($filters['users']);
    }

    $currency = [];

    if (!empty($filters['currencies'])) {
      $currency = $filters['currencies'];
    }

    $transactions = somi_get_filtered_account_events($users, $currency);

    $context['sandbox']['transactions'] = $transactions;
    $context['finished'] = 0;

    $total_items = count($transactions);

    if (empty($total_items)) {
      $context['finished'] = 1;
      return;
    }

    $context['sandbox']['offset'] = 0;
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['updated'] = 0;
    $context['sandbox']['max'] = $total_items;
    $context['sandbox']['bunch_size'] = 20;

    return;
  }

  $transactions = array_slice(
    $context['sandbox']['transactions'],
    $context['sandbox']['offset'],
    $context['sandbox']['bunch_size']
  );

  $context['sandbox']['offset'] += $context['sandbox']['bunch_size'];
  $context['sandbox']['progress'] += count($transactions);

  $rows_array = [];
  $currencies = &$context['sandbox']['currencies'];

  foreach ($transactions as $t) {
    if (empty($t)) continue;

    if (!empty($filters['totals'])) {
      $key = "$t[entity_id]-$t[value_type]";
    } else {
      $key = "$t[timestamp]-$t[entity_id]-$t[value_type]-$t[uid]";
    }

    $recipient = user_load($t['entity_id']);
    $initiator = user_load($t['uid']);

    if (!isset($context['sandbox']['rows_array'][$key])) {
      if (!empty($filters['totals'])) {
        $context['sandbox']['rows_array'][$key] = [
          'recipient' => !empty($recipient->name)
            ? $recipient->name
            : $t['entity_id'],
          'amount' => $t['value'],
          'currency' => $currencies[$t['value_type']],
        ];

      } else {

        $context['sandbox']['rows_array'][$key] = [
          'date' => date('d.m.Y H:s:i', $t['timestamp']),
          'recipient' => !empty($recipient->name)
            ? $recipient->name
            : $t['entity_id'],
          'amount' => $t['value'],
          'currency' => $currencies[$t['value_type']],
          'initiator' => !empty($initiator->name)
            ? $initiator->name
            : $t['uid']
          ,
          'message' => $t['message'],
        ];
      }
    } else {
      $context['sandbox']['rows_array'][$key]['amount'] += $t['value'];
    }
  }

  $context['message'] = t('Обработано %count записей. (Всего %total)', array(
    '%count' => $context['sandbox']['progress'],
    '%total' => $context['sandbox']['max']
  ));

  if ($context['sandbox']['progress'] >= $context['sandbox']['max']) {

    $context['finished'] = 1;
    $context['message'] = t('Экспортирование закончено.') . ' ' . $context['message'];

    drupal_set_message($context['message']);

    ob_clean();

    $filename = 'i20-user-accounts-export-' . date('d-m-Y') . '.csv';

    header('Content-Type: text/csv');
    header('Content-Disposition: attachment; filename=' . $filename);

    if (!empty($filters['totals'])) {
      $column_titles = [
        'Пользователь',
        'Сумма',
        'Валюта',
      ];

      ksort($context['sandbox']['rows_array']);
    } else {
      $column_titles = [
        'Дата',
        'Кому',
        'Сумма',
        'Валюта',
        'От кого',
        'Сообщение',
      ];
    }

    foreach($column_titles as $key => $value) {
      $keys[] = '"' . $value . '"';
    }

    if ($keys) print implode(',', $keys) . "\r\n";
    unset($keys);

    $context['finished'] = 1;

    foreach($context['sandbox']['rows_array'] as $row_array) {
      $values = [];

      // Fetching the field values.
      foreach ($row_array as $key => $value) {
        $values[] = '"' . $value . '"';
      }

      if ($values) {
        print implode(',', $values) . "\r\n";
      }
    }

    $context['results']['csv_data'] = ob_get_contents();
    $context['results']['filename'] = $filename;

    ob_clean();
  }
}

/**
 * Opens Somi Door.
 */
function somi_open_node($node_id) {
  global $user;
  $server_ip   = gethostbyname(SOMI_SERVER_HOST);;
  $server_port = SOMI_SERVER_PORT;

  // @todo make dynamic node_id open.
  switch ($node_id) {
    case 255:
      $message = "command: admin academ open $node_id";
      break;

    default:
      $message = "command: admin open $node_id";
      break;
  }

  ob_clean();

  header('content-type: application:json');

  if ($socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP)) {
    socket_sendto($socket, $message, strlen($message), 0, $server_ip, $server_port);
    echo drupal_json_encode(['status' => "OK"]);
  } else {
    echo drupal_json_encode(['status' => "can't create socket"]);
  }

  if ($rfid = somi_get_web_rfid_by_user($user)) {
    $context = array(
      'uid' => $user->uid,
      'rfid' => $rfid->nid,
      'rfid_node' => 0,
      'name' => $user->name,
      'time' => time(),
      'mail' => $user->mail,
      'card' => $rfid->title,
    );

    module_load_include('inc', 'somi', 'somi.drush');
    somi_log_event($context, 1);
  }
  drupal_exit();
}

function somi_access_handler($id = FALSE) {
  if (($device = somi_get_rfid_by_id($id)) && ($account = somi_get_user_by_rfid($id))) {
    $w = entity_metadata_wrapper('user', $account);

    // If user active.
    if ($w->status->value() && !empty($device->status)) {
      return TRUE;
    }
  }

  return FALSE;
}

/**
 * Used to display content on Android Board.
 */
function somi_realtime_board() {
  drupal_add_css(SOMI_MODULE_PATH . '/theme/css/availability.css');

  drupal_add_css(SOMI_MODULE_PATH . '/theme/css/realtime_board.css');
  drupal_add_js(SOMI_MODULE_PATH . '/theme/js/realtime_board.js');

  // Realtime data update.
  drupal_add_library('somi', 'jquery-color');
  drupal_add_library('somi', 'socket-io');
  $title = "Активность сотрудников I20";

  return theme('somi_board', array('title' => $title, 'class' => 'availability', 'data' => somi_get_availability_data()));
}