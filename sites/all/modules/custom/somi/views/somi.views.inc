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

  $data['notifications']['table']['group'] = t('Notifications');

  $data['notifications']['table']['base'] = array(
    'field' => 'id',
    'title' => t('Notifications'),
    'help' => t('Table for showing all notifications'),
    'weight' => -10,
  );

  $data['notifications']['tid'] = array(
    'title' => t('Notifications taxonomy tid'),
    'relationship' => array(
      'base' => 'taxonomy_term_data',
      'base field' => 'tid',
      'handler' => 'views_handler_relationship',
      'label' => t('Notifications tid'),
      'title' => t('Taxonomy'),
    ),
  );

  $data['notifications']['uid'] = array(
    'title' => t('Users uid'),
    'relationship' => array(
      'base' => 'users',
      'base field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('Users uid'),
      'title' => t('Users'),
    ),
  );

  $data['notifications']['message'] = array(
    'title' => t('Message'),
    'help' => t('Content of the message'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // The Deadline field
  $data['notifications']['date'] = array(
    'title' => t('Date'),
    'help' => t('When message was posted'),
    'field' => array(
      'handler' => 'views_handler_field_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'date_views_filter_handler_simple',
    ),
  );

  return $data;
}
