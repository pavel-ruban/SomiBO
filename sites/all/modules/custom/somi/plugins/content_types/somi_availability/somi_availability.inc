<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi Availability'),
  'description' => t('Provides SOMI personal availability'),
  'content_types' => 'somi_availability',
  'single' => TRUE,
  'render callback' => 'somi_availability_content_type_render',
  'category' => t('Somi'),
  'hook theme' => 'somi_availability_content_type_theme',
);

/**
 * Output function for the content type.
 */
function somi_availability_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  $uids = array();

  $query = "select * from log WHERE access >= " . strtotime(date('d M y 05:00')) . " AND access <"  . strtotime(date('Y-m-d 05:00:00') . ' + 1 day') . ";";

  $availability_data = array();

  $result = db_query($query)->fetchAllAssoc('access');

  foreach ($result as $row) {
    $access = (!empty($availability_data[$row->uid]['access']) && $availability_data[$row->uid]['access'] > $row->access)
      ? $availability_data[$row->id]['access']:
      $row->access;

    $availability_data[$row->uid] = array(
      'uid' => $row->uid,
      'access' => $access,
      'sort' => (int) $access,
      'image_url' => '',
      'image_class' => 'active',
    );

  }

  $uids = db_query('select uid from users')->fetchCol();
  $users = user_load_multiple($uids);

  foreach ($users as $uid => $account) {
    if (!isset($availability_data[$account->uid])) {
      $availability_data[$account->uid] = array(
        'uid' => $account->uid,
        'access' => 0,
        'sort' => 0,
        'image_url' => "http://www.gravatar.com/avatar/" . md5($account->mail),
        'image_class' => 'grayscale',
      );
    }
    else {
      $availability_data[$account->uid]['image_url'] = "http://www.gravatar.com/avatar/" . md5($account->mail);
    }
  }

  drupal_add_css(SOMI_MODULE_PATH . '/plugins/content_types/somi_availability/availability.css');

  $block->content = theme('somi_availability', array('availability_data' => $availability_data));
  return $block;
}

/**
 * CCT hook_theme.
 */
function somi_availability_content_type_theme(&$theme, $plugin) {
  $theme['somi_availability'] = array(
    'variables' => array(),
    'path' => $plugin['path'],
    'template' => 'somi-availability',
  );
}
