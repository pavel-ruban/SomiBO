<?php
/**
 * @file
 * Views module integration hooks.
 */

/**
 * Implements hook_views_data().
 */
function somi_views_data() {

  $data = array();
  $data['users']['gravatar_image'] = array(
    'field' => array(
      'title' => t('Gravatar Image'),
      'help' => t('Provide a image from gravatar by email hash.'),
      'handler' => 'somi_views_handler_field_gravatar_image',
      'group' => 'somi',
      'real field' => 'mail',
    ),
  );

  $data['users']['crystalls'] = array(
    'field' => array(
      'title' => t('Crystalls Count'),
      'help' => t('Shows crystalls of the user.'),
      'handler' => 'somi_views_handler_field_user_crystalls',
      'group' => 'somi',
      'real field' => 'uid',
    ),
  );

  $data['node']['device_image'] = array(
    'field' => array(
      'title' => t('Device Image'),
      'help' => t('Shows image of device.'),
      'handler' => 'somi_views_handler_field_device_image',
      'group' => 'somi',
      'real field' => 'nid',
    ),
  );

  $data['users']['crystalls_debet'] = array(
    'field' => array(
      'title' => t('Crystalls Debet Count'),
      'help' => t('Shows crystalls debet of the user.'),
      'handler' => 'somi_views_handler_field_user_debet_crystalls',
      'group' => 'somi',
      'real field' => 'uid',
    ),
  );

  return $data;
}
