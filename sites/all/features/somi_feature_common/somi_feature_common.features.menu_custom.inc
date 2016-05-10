<?php
/**
 * @file
 * somi_feature_common.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function somi_feature_common_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: main-menu.
  $menus['main-menu'] = array(
    'menu_name' => 'main-menu',
    'title' => 'Main menu',
    'description' => 'The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.',
  );
  // Exported menu: menu-common-admin-menu.
  $menus['menu-common-admin-menu'] = array(
    'menu_name' => 'menu-common-admin-menu',
    'title' => 'Common Admin Menu',
    'description' => 'Admin menu primary links',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Admin menu primary links');
  t('Common Admin Menu');
  t('Main menu');
  t('The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.');

  return $menus;
}
