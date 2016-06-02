<?php
/**
 * @file
 * Provides logic to highlight specified menu items by path mask.
 */

/**
 * Hardcoded menu position rules.
 */
function somi_menu_position_rules() {
  // Rules represent as array with several keys: paths of menu items to be highlighted & pages paths where this
  // items will be highlight. Also related properties such as entity type, bundle.
  $rules = array(
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/content/accounts',
      ),
      'page_mask' => array(
        'admin/user/*/account',
        'admin/user/*/account/*',
      ),
      // Optional.
      'type' => array(
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/content/taxonomies',
      ),
      'page_mask' => array(
        'taxonomy/term/*/edit',
        'taxonomy/term/*/delete',
        'admin/taxonomy/term/*/delete',
        'admin/structure/taxonomy/*/add',
        'admin/structure/taxonomy',
        'admin/structure/taxonomy/*',
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/promotions/orders',
      ),
      'page_mask' => array(
        'admin/commerce/config/product-pricing/rules/*',
        'admin/config/workflow/rules/reaction/manage/*',
      ),
      // Optional.
      'query' => array(
        'promotion_type' => 'order',
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/promotions/transport',
      ),
      'page_mask' => array(
        'admin/commerce/config/product-pricing/rules/*',
        'admin/config/workflow/rules/reaction/manage/*',
      ),
      // Optional.
      'query' => array(
        'promotion_type' => 'transport',
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/skimium/config',
      ),
      'page_mask' => array(
        'admin/skimium/config/*',
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/promotions/codes',
      ),
      'page_mask' => array(
        'admin/commerce/coupons*',
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/promotions/transport',
      ),
      'page_mask' => array(
        'admin/config/workflow/rules/components/manage*',
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/devices',
      ),
      'page_mask' => array(
        'node/*/delete',
        'node/*/edit',
        'node/*/publish',
        'node/*/unpublish',
      ),
      // Optional.
      'type' => array(
        'entity_types' => array(
          'node',
        ),
        'bundles' => array(
          'device',
        ),
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/content/models',
      ),
      'page_mask' => array(
        'admin/commerce/products/*/edit',
      ),
      // Optional.
      'type' => array(
        'entity_types' => array(
          'commerce_product',
        ),
        'bundles' => array(
          'article',
        ),
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/content/catalogs',
      ),
      'page_mask' => array(
        'node/*/delete',
        'node/*/edit',
        'node/*/publish',
        'node/*/unpublish',
      ),
      // Optional.
      'type' => array(
        'entity_types' => array(
          'node',
        ),
        'bundles' => array(
          'catalog',
        ),
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/content/catalogs',
        'admin/structure/nodequeue/1/view/',
        'admin/structure/nodequeue/1/view',
      ),
      'page_mask' => array(
        'admin/structure/nodequeue/1/view',
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/content/models',
      ),
      'page_mask' => array(
        'node/*/delete',
        'node/*/edit',
        'node/*/publish',
        'node/*/unpublish',
      ),
      // Optional.
      'type' => array(
        'entity_types' => array(
          'node',
        ),
        'bundles' => array(
          'model',
        ),
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/structure/taxonomy_manager/voc/category',
      ),
      'page_mask' => array(
        'admin/structure/taxonomy_manager/double-tree/*',
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/structure/taxonomy/category',
      ),
      'page_mask' => array(
        'admin/taxonomy/term/*/delete',
        'taxonomy/term/*/edit',
      ),
      // Optional.
      'type' => array(
        'entity_types' => array(
          'taxonomy_term',
        ),
        'bundles' => array(
          'category',
        ),
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/content/brands',
      ),
      'page_mask' => array(
        'admin/taxonomy/term/*/delete',
        'taxonomy/term/*/edit',
      ),
      // Optional.
      'type' => array(
        'entity_types' => array(
          'taxonomy_term',
        ),
        'bundles' => array(
          'brand',
        ),
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/content/attributes',
      ),
      'page_mask' => array(
        'admin/taxonomy/term/*/delete',
        'taxonomy/term/*/edit',
      ),
      // Optional.
      'type' => array(
        'entity_types' => array(
          'taxonomy_term',
        ),
        'bundles' => array(
          'attribute',
        ),
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/users',
      ),
      'page_mask' => array(
        'user/*/cancel',
        'user/*/edit',
      ),
      // Optional.
      'type' => array(
        'entity_types' => array(
          'user',
        ),
        'bundles' => array(
          'user',
        ),
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/users',
      ),
      'page_mask' => array(
        'admin/somi/score-board/*',
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/somi/chart',
      ),
      'page_mask' => array(
        'admin/somi/chart/*',
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/commerce/orders',
      ),
      'page_mask' => array(
        'admin/commerce/orders/add',
        'admin/commerce/orders/*/edit',
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/skimium/config/mail',
      ),
      'page_mask' => array(
        'admin/skimium/config/mail',
        'admin/config/system/mail-edit',
        'admin/config/system/mail-edit/*',
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/somi/score-board/7',
      ),
      'page_mask' => array(
        'admin/somi/score-board/7/*',
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/somi/score-board/12',
      ),
      'page_mask' => array(
        'admin/somi/score-board/12/*',
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/somi/score-board/16',
      ),
      'page_mask' => array(
        'admin/somi/score-board/16/*',
      ),
    ),
    array(
      // This gives opportunity to apply mask rule for several menu items.
      'menu_item_to_highlight' => array(
        'admin/dashboard/car',
      ),
      'page_mask' => array(
        'node/*/edit',
        'node/add/car',
      ),
      // Optional.
      'type' => array(
        'entity_types' => array(
          'node',
        ),
        'bundles' => array(
          'car',
        ),
      ),
    ),
  );

  return $rules;
}

/**
 * Triggered from delivery callback alter to check & execute validated rules.
 */
function somi_menu_position_execute_rules() {
  if ($rules = somi_menu_position_rules()) {
    $context = somi_build_menu_position_context();
    foreach ($rules as $rule) {
      foreach ($rule['menu_item_to_highlight'] as $menu_item_path_to_highlight) {
        // Search link within admin menu, if it isn't exist check across all menus.
        $item = menu_link_get_preferred($menu_item_path_to_highlight, 'menu-admin-menu');
        if (empty($item['mlid'])) {
          $item = menu_link_get_preferred($menu_item_path_to_highlight);
        }
        if (!empty($item['mlid']) && !empty($rule['page_mask'])) {
          // Check is type settings are filled & check are they valid.
          if (!empty($rule['type'])) {
            $valid_type = somi_menu_position_check_types($rule['type'], $context);
          }
          // Check $_GET parameters.
          if (!empty($rule['query'])) {
            $valid_type = somi_menu_position_check_query($rule['query'], $context);
          }
          else {
            $valid_type = TRUE;
          }

          if ($valid_type) {
            // Check if current path ($_GET['q']) belongs to some rule mask.
            foreach ($rule['page_mask'] as $path) {
              if (somi_menu_position_check_page_conditions($path)) {
                // Set rule menu mode to highlight.
                somi_menu_position_activate_rule($item, $context);
                break;
              }
            }
          }
        }
      }
    }
  }
}

/**
 * Context callback.
 */
function somi_build_menu_position_context() {
  // Build a small context.
  $context = array(
    'path' => $_GET['q'],
    'entity_type' => NULL,
    'bundle_name' => NULL,
  );

  // Determine what kind of entity page this is.
  list($arg0, $arg1) = explode('/', $_GET['q'] . '//');
  if ($arg0 == 'node' && is_numeric($arg1)) {
    $context['node'] = node_load($arg1);
    // Don't evaluate the rules on a 404 page.
    if (!$context['node']) {
      return;
    }
    $context['entity_type'] = 'node';
    $context['bundle_name'] = $context['node']->type;
  }
  elseif ($arg0 == 'user' && is_numeric($arg1)) {
    $context['user'] = user_load($arg1);
    // Don't evaluate the rules on a 404 page.
    if (!$context['user']) {
      return;
    }
    $context['entity_type'] = 'user';
    $context['bundle_name'] = 'user';
  }
  elseif (preg_match('/taxonomy\/term\/([0-9]+)/i', $_GET['q'], $matches)) {
    $context['taxonomy_term'] = taxonomy_term_load($matches[1]);
    // Don't evaluate the rules on a 404 page.
    if (!$context['taxonomy_term']) {
      return;
    }
    $context['entity_type'] = 'taxonomy_term';
    $context['bundle_name'] = $context['taxonomy_term']->vocabulary_machine_name;
  }
  elseif (preg_match('/admin\/commerce\/products\/([0-9]+)/i', $_GET['q'], $matches)) {
    $context['commerce_product'] = commerce_product_load($matches[1]);
    // Don't evaluate the rules on a 404 page.
    if (!$context['commerce_product']) {
      return;
    }
    $context['entity_type'] = 'commerce_product';
    $context['bundle_name'] = $context['commerce_product']->type;
  }
  return $context;
}

/**
 * Menu position module fork - check are there some valid menu rules to activate it.
 */
function somi_menu_position_check_page_conditions($pages) {
  // Convert the Drupal path to lowercase.
  $path = drupal_strtolower(drupal_get_path_alias($_GET['q']));
  // Compare the lowercase internal and lowercase path alias (if any).
  $page_match = drupal_match_path($path, $pages);
  if (!$page_match && $path != $_GET['q']) {
    $page_match = drupal_match_path($_GET['q'], $pages);
  }

  return $page_match;
}

/**
 * Entity type & bundle check callback.
 */
function somi_menu_position_check_types($type_settings, $context) {
  if (!empty($context['entity_type']) && !empty($type_settings['entity_types'])
    && in_array($context['entity_type'], $type_settings['entity_types'], TRUE)
  ) {
    $entity_type = TRUE;
  }
  if (!empty($context['bundle_name']) && !empty($type_settings['bundles'])
    && in_array($context['bundle_name'], $type_settings['bundles'], TRUE)
  ) {
    $bundle = TRUE;
  }
  return !empty($entity_type) && !empty($bundle);
}

/**
 * Quert check callback.
 */
function somi_menu_position_check_query($query_settings, $context) {
  $result = TRUE;

  if (!empty($query_settings) && !empty($_GET)) {
    foreach ($query_settings as $key => $value) {
      if (!(!empty($_GET[$key]) && $_GET[$key] == $value)) {
        $result = FALSE;
        break;
      }
    }
  }

  return $result;
}

/**
 * Menu position module fork - activate rule's link if it matched to page rules.
 */
function somi_menu_position_activate_rule($item, $context = NULL, $set_breadcrumb = TRUE) {
  // Retrieve menu item specified in the rule.
  $menu_item = menu_link_load($item['mlid']);

  // Sanity check: if the menu link doesn't exist abort processing the rule.
  if (!$menu_item) {
    return FALSE;
  }

  // Reset the menu trail that views may have set.
  $original_router_item = menu_get_item();
  if ($original_router_item['page_callback'] == 'views_page') {
    $preferred = & drupal_static('menu_link_get_preferred');
    unset($preferred[$context['path']]);
  }

  // Set the active path for the rule's menu.
  menu_tree_set_path($menu_item['menu_name'], $menu_item['link_path']);

  // Allow the rule's parent menu item to show "expanded" status.
  somi_menu_position_expand_parent_link($item['plid']);

  // Alter the active trail if breadcrumbs still need to be set.
  if ($set_breadcrumb) {
    // Manually set the preferred link for this path so that
    // menu_get_active_trail() returns the proper trail.
    $preferred_links = & drupal_static('menu_link_get_preferred');
    $preferred_links[$_GET['q']][MENU_PREFERRED_LINK] = menu_link_get_preferred($menu_item['link_path']);

    // Remove the menu position router from the end of the trail.
    $active_trail = menu_set_active_trail();
    list($last, $pre_last) = array_reverse($active_trail);
    if ($last && $pre_last && isset($last['link_path']) && $last['link_path'] == $pre_last['link_path']) {
      array_pop($active_trail);
      menu_set_active_trail($active_trail);
    }
  }

  return TRUE;
}

/**
 * Menu position fork.
 * Dynamically expands the parent menu item for a rule.
 *
 * @param $plid
 *   The parent menu item's mlid.
 */
function somi_menu_position_expand_parent_link($plid = NULL) {
  $link_id = & drupal_static(__FUNCTION__, NULL);

  if (isset($plid)) {
    $link_id = $plid;
  }
  return $link_id;
}
