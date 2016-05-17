<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi Bugs Winner'),
  'description' => t('Provides SOMI Bugs Winner Info'),
  'content_types' => 'somi_bugs_winner',
  'single' => TRUE,
  'render callback' => 'somi_bugs_winner_content_type_render',
  'category' => t('Somi'),
  'hook theme' => 'somi_bugs_winner_content_type_theme',
);

/**
 * Output function for the content type.
 */
function somi_bugs_winner_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  $bugs_data = array();

  $uids = db_query('select uid from users WHERE status = 1')->fetchCol();
  $users = user_load_multiple($uids);

  foreach ($users as $uid => $account) {
    $bugs = somi_get_user_account_balance($account->uid, SOMI_BUGS_CURRENCY_TID);

    $bugs_data[$account->uid] = array(
      'uid' => $account->uid,
      'name' => $account->name,
      'bugs' => $bugs,
      'sort' => $bugs,
      'image_url' => "http://www.gravatar.com/avatar/" . md5($account->mail),
      'image_class' => $bugs ? 'active' : 'grayscale',
    );
  }

  uasort($bugs_data, function($a, $b) {
    if ($a['bugs'] == $b['bugs']) return 0;

    return $a['bugs'] > $b['bugs']
      ? -1
      : 1;
  });

  foreach ($bugs_data as $key => &$item) {
    $class = $item['bugs'] ? 'active' : 'grayscale';

    $item = [
      'uid' => $item['uid'],
      'bugs' => $item['bugs'],
      'class' => $class,
      'l' => l(
        theme('image', ['path' => $item['image_url'],
          'attributes' => [
            'title' => $item['name'] . ($item['bugs'] ? (PHP_EOL . 'Жуков: ' . $item['bugs']) : ''),
            'class' => [$class]
          ]
        ]),
        '/admin/user/' . $item['uid'] . '/account/' . SOMI_BUGS_CURRENCY_TID,
        ['html' => TRUE]
      )
    ];
  }

  drupal_add_css(SOMI_MODULE_PATH . '/plugins/content_types/somi_bugs_winner/table-board.css');

  $block->content = theme('somi_bugs_winner', array('bugs_data' => $bugs_data));
  return $block;
}

/**
 * CCT hook_theme.
 */
function somi_bugs_winner_content_type_theme(&$theme, $plugin) {
  $theme['somi_bugs_winner'] = array(
    'variables' => array(),
    'path' => $plugin['path'],
    'template' => 'somi-bugs-winner',
  );
}
