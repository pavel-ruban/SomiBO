<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi Crystal Winner'),
  'description' => t('Provides SOMI Crystal Winner Info'),
  'content_types' => 'somi_crystal_winner',
  'single' => TRUE,
  'render callback' => 'somi_crystal_winner_content_type_render',
  'category' => t('Somi'),
  'hook theme' => 'somi_crystal_winner_content_type_theme',
);

/**
 * Output function for the content type.
 */
function somi_crystal_winner_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  $crystal_data = array();

  $uids = db_query('select uid from users WHERE status = 1')->fetchCol();
  $users = user_load_multiple($uids);

  foreach ($users as $uid => $account) {
    $crystals = somi_get_user_account_balance($account->uid, SOMI_CRYSTALLS_CURRENCY_TID);

    $crystal_data[$account->uid] = array(
      'uid' => $account->uid,
      'name' => $account->name,
      'crystals' => $crystals,
      'sort' => $crystals,
      'image_url' => "http://www.gravatar.com/avatar/" . md5($account->mail),
      'image_class' => $crystals ? 'active' : 'grayscale',
    );
  }

  uasort($crystal_data, function($a, $b) {
    if ($a['crystals'] == $b['crystals']) return 0;

    return $a['crystals'] > $b['crystals']
      ? -1
      : 1;
  });

  foreach ($crystal_data as $key => &$item) {
    $class = $item['crystals'] ? 'active' : 'grayscale';

    $item = [
      'uid' => $item['uid'],
      'crystals' => $item['crystals'],
      'class' => $class,
      'l' => l(
        theme('image', ['path' => $item['image_url'],
          'attributes' => [
            'title' => $item['name'] . ($item['crystals'] ? (PHP_EOL . 'Кристаллов: ' . $item['crystals']) : ''),
            'class' => [$class]
          ]
        ]),
        '/admin/user/' . $item['uid'] . '/account/' . SOMI_BUGS_CURRENCY_TID,
        ['html' => TRUE]
      )
    ];
  }

  drupal_add_css(SOMI_MODULE_PATH . '/plugins/content_types/somi_crystal_winner/table-board.css');

  $block->content = theme('somi_crystal_winner', array('crystal_data' => $crystal_data));
  return $block;
}

/**
 * CCT hook_theme.
 */
function somi_crystal_winner_content_type_theme(&$theme, $plugin) {
  $theme['somi_crystal_winner'] = array(
    'variables' => array(),
    'path' => $plugin['path'],
    'template' => 'somi-crystal-winner',
  );
}
