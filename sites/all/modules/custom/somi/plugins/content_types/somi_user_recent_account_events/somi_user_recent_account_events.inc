<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi User Recent Account Events'),
  'description' => t('Provides user account data events details'),
  'content_types' => 'somi_user_recent_account_events',
  'single' => TRUE,
  'render callback' => 'somi_user_recent_account_events_content_type_render',
  'category' => t('Somi'),
  'hook theme' => 'somi_user_recent_account_events_content_type_theme',
);

/**
 * Output function for the content type.
 */
function somi_user_recent_account_events_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  $events = somi_get_recent_account_events();
  if (!empty($events)) {
    $date_format = 'd-m-Y H:i:s';

    $rows = [];

    foreach ($events as $event) {
      if ($account = user_load($event['entity_id'])) {
        if ($src_account = user_load($event['uid'])) {
          $src = $src_account->name;
        }
        else {
          $src = '-';
        }

        if (is_numeric($event['value_type']) && $currency_term = taxonomy_term_load($event['value_type'])) {
          $account_type = $currency_term->name;
        }
        else {
          $account_type = $event['value_type'];
        }

        $row = [];
        $row [] = date($date_format, $event['timestamp']);
        $row [] = $src;
        $row [] = $account->name;
        $row [] = $account_type;
        $row [] = $event['value'];
        $row [] = $event['message'];

        $rows[] = $row;
      }
    }

    $accounts_events = theme('table', [
      'header' => [
        'Дата',
        'Отправитель',
        'Получатель',
        'Сумма',
        'Счет',
        'Сообщение',
      ],
      'rows' => $rows
    ]);

    $block->content = theme(
      'somi_user_recent_account_events',
      array(
        'accounts_events' => $accounts_events,
      )
    );
  }

  return $block;
}

/**
 * CCT hook_theme.
 */
function somi_user_recent_account_events_content_type_theme(&$theme, $plugin) {
  $theme['somi_user_recent_account_events'] = array(
    'variables' => array(),
    'path' => $plugin['path'],
    'template' => 'somi-user-recent-account-events',
  );
}
