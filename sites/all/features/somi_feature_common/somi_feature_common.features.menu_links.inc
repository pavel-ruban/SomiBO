<?php
/**
 * @file
 * somi_feature_common.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function somi_feature_common_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-common-admin-menu_-:admin/content/accounts/events.
  $menu_links['menu-common-admin-menu_-:admin/content/accounts/events'] = array(
    'menu_name' => 'menu-common-admin-menu',
    'link_path' => 'admin/content/accounts/events',
    'router_path' => 'admin/content/accounts/events',
    'link_title' => 'Последние события',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-common-admin-menu_-:admin/content/accounts/events',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'menu-common-admin-menu_:admin/content/accounts',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Последние события');

  return $menu_links;
}
