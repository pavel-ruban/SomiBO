<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi User Crystalls Log'),
  'description' => t('Provides user crystalls log pane'),
  'content_types' => 'somi_user_crystalls_log',
  'single' => TRUE,
  'render callback' => 'somi_user_crystalls_log_content_type_render',
  'category' => t('Somi'),
  'hook theme' => 'somi_user_crystalls_log_content_type_theme',
);

/**
 * Output function for the content type.
 */
function somi_user_crystalls_log_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  if ($account = user_load($panel_args[0])) {
    $title = t('История изменения по счетам кристаллов пользователя "%u"', ['%u' => $account->name]);

    $date_format = 'd-m-Y H:i:s';

    $user_votes = votingapi_select_votes(
      array(
        'entity_id' => $account->uid,
        'entity_type' => 'user',
        'value_type' => 'crystalls',
      )
    );

   ;
    $rows = [];
    foreach ($user_votes as $vote) {
      $negative = (int) $vote['value'] < 0;
      $class = $negative ? 'negative' : 'positive';
      $row = [];
      $row[] = $negative ? 'Кредит' : 'Дебет';
      $row[] = !empty($vote['uid']) ? user_load($vote['uid'])->name : t('аноним');
      $row[] = $vote['value'];
      $row[] = date($date_format, $vote['timestamp']);
      $row[] = t('отсутствует');

      foreach ($row as &$data) {
        $data = '<span class="' . $class . "\">$data</span";
      }

      $rows[] = $row;
    }

    $crystalls_log = theme('table', [
      'attributes' => ['class' => ['crystalls-log']],
      'header' => [
        'Событие',
        'Источник',
        'Количество',
        'Дата',
        'Сообщение',
      ],
      'rows' => $rows
    ]);

    $user_votes = votingapi_select_votes(
      array(
        'entity_id' => $account->uid,
        'entity_type' => 'user',
        'value_type' => 'crystalls_debet',
      )
    );

    $rows = [];
    foreach ($user_votes as $vote) {
      $negative = (int) $vote['value'] < 0;
      $class = $negative ? 'negative' : 'positive';
      $row = [];
      $row[] = $negative ? 'Кредит' : 'Дебет';
      $row[] = !empty($vote['uid']) ? user_load($vote['uid'])->name : t('аноним');
      $row[] = $vote['value'];
      $row[] = date($date_format, $vote['timestamp']);
      $row[] = t('отсутствует');

      foreach ($row as &$data) {
        $data = '<span class="' . $class . "\">$data</span";
      }

      $rows[] = $row;
    }

    $crystalls_debet_log = theme('table', [
      'attributes' => ['class' => ['crystalls-log']],
      'header' => [
        'Событие',
        'Источник',
        'Количество',
        'Дата',
        'Сообщение',
      ],
      'rows' => $rows
    ]);

    $rows = [];
    foreach (['Кредит' => 'crystalls', 'Дебет' => 'crystalls_debet'] as $row_name => $vote_type) {
      $row = [];
      $row [] = $row_name;
      $suffix = $row_name == 'Дебет' ? '-debet' : '';

      $row [] = theme('image_style',
        array(
          'style_name' => 'thumbnail',
          'path' => "crystalls$suffix.png",
          'title' => $account->name,
          'alt' => $account->name,
        )
      ) . '<span class="crystalls-count">' .somi_get_user_crystalls($account->uid, $vote_type) . '</span>';
      $rows[] = $row;
    }

    $crystalls_total = theme('table', [
      'header' => [
        'Счет',
        'Остаток',
      ],
      'rows' => $rows
    ]);

    $block->content = theme(
      'somi_user_crystall_log',
      array(
        'crystalls_total' => $crystalls_total,
        'crystalls_log' => $crystalls_log,
        'title' => $title,
        'crystalls_debet_log' => $crystalls_debet_log,
      )
    );
  }

  return $block;
}

/**
 * CCT hook_theme.
 */
function somi_user_crystalls_log_content_type_theme(&$theme, $plugin) {
  $theme['somi_user_crystall_log'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'somi-user-crystall-log',
  );
}
