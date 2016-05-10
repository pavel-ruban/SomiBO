<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi Door Utils.'),
  'description' => t('Provides door utils'),
  'content_types' => 'somi_door_utils',
  'single' => TRUE,
  'render callback' => 'somi_door_utils_content_type_render',
  'category' => t('Somi'),
  'hook theme' => 'somi_door_utils_content_type_theme',
);

/**
 * Output function for the content type.
 */
function somi_door_utils_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  return $block;
}

/**
 * CCT hook_theme.
 */
function somi_door_utils_content_type_theme(&$theme, $plugin) {
  $theme['somi_door_utils'] = array(
    'variables' => array(),
    'path' => $plugin['path'],
    'template' => 'somi-chart',
  );
}
