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

  return $data;
}
