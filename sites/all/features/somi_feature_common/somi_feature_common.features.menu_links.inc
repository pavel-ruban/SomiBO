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
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-common-admin-menu_content:admin/content/accounts',
  );
  // Exported menu link: menu-common-admin-menu_-:admin/content/taxonomies/add-term.
  $menu_links['menu-common-admin-menu_-:admin/content/taxonomies/add-term'] = array(
    'menu_name' => 'menu-common-admin-menu',
    'link_path' => 'admin/content/taxonomies/add-term',
    'router_path' => 'admin/content/taxonomies/add-term',
    'link_title' => 'Добавить термин',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-common-admin-menu_-:admin/content/taxonomies/add-term',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'menu-common-admin-menu_:admin/content/taxonomies',
  );
  // Exported menu link: menu-common-admin-menu_somi-:admin/somi/chart.
  $menu_links['menu-common-admin-menu_somi-:admin/somi/chart'] = array(
    'menu_name' => 'menu-common-admin-menu',
    'link_path' => 'admin/somi/chart',
    'router_path' => 'admin',
    'link_title' => 'SOMI Графики',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-common-admin-menu_somi-:admin/somi/chart',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-common-admin-menu_:admin/users',
  );
  // Exported menu link: menu-common-admin-menu_somi-availability:admin/somi/availability.
  $menu_links['menu-common-admin-menu_somi-availability:admin/somi/availability'] = array(
    'menu_name' => 'menu-common-admin-menu',
    'link_path' => 'admin/somi/availability',
    'router_path' => 'admin',
    'link_title' => 'SOMI Availability',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-common-admin-menu_somi-availability:admin/somi/availability',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'menu-common-admin-menu_:admin/users',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('SOMI Availability');
  t('SOMI Графики');
  t('Добавить термин');
  t('Последние события');

  return $menu_links;
}
