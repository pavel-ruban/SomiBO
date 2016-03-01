<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi header'),
  'description' => t('Provides site main header pane'),
  'content_types' => 'somi_header',
  'single' => TRUE,
  'render callback' => 'somi_header_content_type_render',
  'category' => t('Somi'),
  'hook theme' => 'somi_header_content_type_theme',
);

/**
 * Output function for the content type.
 */
function somi_header_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  if (!empty($items)) {
//    $articles = theme('item_list', array('items' => $items));
  }

  $main_menu_tree = menu_tree_all_data('main-menu');
  $main_menu_expanded = menu_tree_output($main_menu_tree);

  $menu =  render($main_menu_expanded);

  $block->content = theme('somi_header', array('menu' => $menu));
  return $block;
}

/**
 * CCT hook_theme.
 */
function somi_header_content_type_theme(&$theme, $plugin) {
  $theme['somi_header'] = array(
    'variables' => array(
    ),
    'path' => $plugin['path'],
    'template' => 'somi_header',
  );
}
