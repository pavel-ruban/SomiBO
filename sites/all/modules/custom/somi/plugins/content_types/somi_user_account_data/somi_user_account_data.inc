<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi User Account Data'),
  'description' => t('Provides user account data details'),
  'content_types' => 'somi_user_account_data',
  'single' => TRUE,
  'render callback' => 'somi_user_account_data_content_type_render',
  'category' => t('Somi'),
  'hook theme' => 'somi_user_account_data_content_type_theme',
);

function somi_account_operations_form($form, &$form_state) {
  $form = [
    'fieldset' => [
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => 'collapsed',
      '#title' => t('Операции по счету'),
      'value' => [
        '#type' => 'textfield',
        '#title' => t('Сумма'),
        '#description' => t('Количество валюты которое будет учтено при проведении операции'),
      ],
      'uid' => [
        '#type' => 'hidden',
        '#title' => t('uid'),
        '#value' => $form_state['build_info']['args'][0]['target_uid'],
      ],
      'currency' => [
        '#type' => 'hidden',
        '#title' => t('currency'),
        '#value' => $form_state['build_info']['args'][0]['currency'],
      ],
      'message' => [
        '#type' => 'textarea',
        '#title' => t('Сообщение'),
        '#description' => t('Основание для проведения операции или любая другая полезная информация'),
      ],
      'submit' => [
        '#type' => 'submit',
        '#value' => t('Провести операцию'),
      ],
    ],
  ];

  return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function somi_account_operations_form_validate($form, &$form_state) {
  if (empty($form_state['values']['value'])) {
    form_set_error('value', t('Сумма не может быть равной нулю.'));
  }

  if (empty($form_state['values']['message']) || strlen($form_state['values']['message']) < 10) {
    form_set_error('message', t('Введите сообщение, оно не может быть слишком коротким.'));
  }
}

/**
 * @param $form
 * @param $form_state
 */
function somi_account_operations_form_submit($form, &$form_state) {
  global $user;

  $currency_tid = somi_get_currency_tid($form_state['values']['currency']);

  somi_add_user_account_balance(
    $form_state['values']['uid'],
    $form_state['values']['value'],
    $currency_tid,
    $form_state['values']['message'],
    $user->uid
  );

  drupal_set_message(
    t(
      '%qty единицы валюты %currency было зачтено пользователю %user',
      [
        '%qty' => $form_state['values']['value'],
        '%currency' => $form_state['values']['currency'],
        '%user' => user_load($form_state['values']['uid'])->uid,
      ]
    )
  );
}

/**
 * Output function for the content type.
 */
function somi_user_account_data_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  if ($account = user_load($panel_args[0])) {
    $date_format = 'd-m-Y H:i:s';

    $rows = [];

    if (!empty($panel_args[1])) {
      $title = t('Детали счёта пользователя "%u"', ['%u' => $account->name]);

      $currency_term = taxonomy_term_load($panel_args[1]);

      if ($currency_term->vocabulary_machine_name != SOMI_VOCABULARY_CURRENCIES) return;

      $currency = $currency_term->name;

      $row = [];
      $row [] = $currency;
      $row [] = somi_get_account_data_by_currencry($currency, $account->uid);

      $rows[] = $row;

      $account_details = TRUE;
    }
    else {
      $title = t('Детали счетов пользователя "%u"', ['%u' => $account->name]);

      $currencies = somi_get_currencies();

      foreach ($currencies as $currency) {
        $row = [];
        $row [] = $currency;
        $row [] = somi_get_account_data_by_currencry($currency, $account->uid);

        $rows[] = $row;
      }
    }

    $accounts_total = theme('table', [
      'header' => [
        'Счет',
        'Остаток',
      ],
      'rows' => $rows
    ]);

    if (!empty($account_details)) {
      // Provide form to change account.
      if (user_access('perform manual account operations')) {
        $account_form = drupal_get_form(
          'somi_account_operations_form',
          ['target_uid' => $account->uid, 'currency' => $currency]
        );
      }

      // Get account history.
      $account_operations = votingapi_select_votes(
        array(
          'entity_id' => $account->uid,
          'entity_type' => 'user',
          'value_type' => $currency_term->tid,
        )
      );

      $rows = [];

      foreach (array_reverse($account_operations) as $operation) {
        $negative = (int) $operation['value'] < 0;
        $class = $negative ? 'negative' : 'positive';

        $row = [];
        $row[] = $negative ? 'Кредит' : 'Дебет';

        $row[] = !empty($operation['uid'])
          ? user_load($operation['uid'])->name
          : t('аноним');

        $row[] = $operation['value'];

        $row[] = date($date_format, $operation['timestamp']);

        $row[] = $operation['message'];

        foreach ($row as &$data) {
          $data = '<span class="' . $class . "\">$data</span";
        }

        $rows[] = ['data' => $row, 'class' => [$class]];
      }

      $accounts_history = theme('table', [
        'attributes' => ['class' => ['account-details']],
        'header' => [
          'Событие',
          'Источник',
          'Количество',
          'Дата',
          'Сообщение',
        ],
        'rows' => $rows
      ]);
    }
    else {
      $accounts_history = '';
      $account_form = '';
    }

    $block->content = theme(
      'somi_user_account_data',
      array(
        'accounts_total' => $accounts_total,
        'accounts_history' => $accounts_history,
        'account_form' => $account_form,
        'title' => $title,
      )
    );
  }

  return $block;
}

/**
 * CCT hook_theme.
 */
function somi_user_account_data_content_type_theme(&$theme, $plugin) {
  $theme['somi_user_account_data'] = array(
    'variables' => array(),
    'path' => $plugin['path'],
    'template' => 'somi-user-account-data',
  );
}
