<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi Drupal Winner'),
  'description' => t('Provides SOMI Drupal Winner Info'),
  'content_types' => 'somi_drupal_winner',
  'single' => TRUE,
  'render callback' => 'somi_drupal_winner_content_type_render',
  'category' => t('Somi'),
  'hook theme' => 'somi_drupal_winner_content_type_theme',
);

/**
 * Output function for the content type.
 */
function somi_drupal_winner_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  $drupal_data = array();

  $uids = db_query('select uid from users WHERE status = 1')->fetchCol();
  $users = user_load_multiple($uids);

  foreach ($users as $uid => $account) {
    $drupal = somi_get_user_account_balance($account->uid, SOMI_DRUPAL_CURRENCY_TID);

    $drupal_data[$account->uid] = array(
      'uid' => $account->uid,
      'name' => $account->name,
      'drupal' => $drupal,
      'sort' => $drupal,
      'image_url' => "http://www.gravatar.com/avatar/" . md5($account->mail),
      'image_class' => $drupal ? 'active' : 'grayscale',
    );
  }

  uasort($drupal_data, function($a, $b) {
    if ($a['drupal'] == $b['drupal']) return 0;

    return $a['drupal'] > $b['drupal']
      ? -1
      : 1;
  });

  foreach ($drupal_data as $key => &$item) {
    $class = $item['drupal'] ? 'active' : 'grayscale';

    $item = [
      'uid' => $item['uid'],
      'drupal' => $item['drupal'],
      'class' => $class,
      'l' => l(
        theme('image', ['path' => $item['image_url'],
          'attributes' => [
            'title' => $item['name'] . ($item['drupal'] ? (PHP_EOL . 'Друпликонов: ' . $item['drupal']) : ''),
            'class' => [$class]
          ]
        ]),
        '/admin/user/' . $item['uid'] . '/account/' . SOMI_DRUPAL_CURRENCY_TID,
        ['html' => TRUE]
      )
    ];
  }

  drupal_add_css(SOMI_MODULE_PATH . '/plugins/content_types/somi_drupal_winner/table-board.css');

  $block->content = theme('somi_drupal_winner', array('drupal_data' => $drupal_data));
  return $block;
}

/**
 * CCT hook_theme.
 */
function somi_drupal_winner_content_type_theme(&$theme, $plugin) {
  $theme['somi_drupal_winner'] = array(
    'variables' => array(),
    'path' => $plugin['path'],
    'template' => 'somi-drupal-winner',
  );
}
