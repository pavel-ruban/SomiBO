<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi Bugs Winner'),
  'description' => t('Provides SOMI personal availability'),
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

  $availability_data = array();

  $uids = db_query('select uid from users WHERE status = 1')->fetchCol();
  $users = user_load_multiple($uids);

  foreach ($users as $uid => $account) {
    $bugs = somi_get_user_account_balance($account->uid, SOMI_BUGS_CURRENCY_TID);

    $availability_data[$account->uid] = array(
      'uid' => $account->uid,
      'name' => $account->name,
      'access' => $bugs,
      'sort' => $bugs,
      'image_url' => "http://www.gravatar.com/avatar/" . md5($account->mail),
      'image_class' => $bugs ? 'active' : 'grayscale',
    );
  }

  uasort($availability_data, function($a, $b) {
    if ($a['access'] == $b['access']) return 0;

    return $a['access'] > $b['access']
      ? -1
      : 1;
  });

  foreach ($availability_data as $key => &$item) {
    $class = $item['access'] ? 'active' : 'grayscale';

    $item = [
      'uid' => $item['uid'],
      'access' => $item['access'],
      'class' => $class,
      'l' => l(
        theme('image', ['path' => $item['image_url'],
          'attributes' => [
            'title' => $item['name'] . ($item['access'] ? (PHP_EOL . 'Жуков: ' . $item['access']) : ''),
            'class' => [$class]
          ]
        ]),
        '/admin/user/' . $account->uid . '/account/' . SOMI_BUGS_CURRENCY_TID,
        ['html' => TRUE]
      )
    ];
  }

  drupal_add_css(SOMI_MODULE_PATH . '/plugins/content_types/somi_bugs_winner/availability.css');

  $block->content = theme('somi_bugs_winner', array('availability_data' => $availability_data));
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
