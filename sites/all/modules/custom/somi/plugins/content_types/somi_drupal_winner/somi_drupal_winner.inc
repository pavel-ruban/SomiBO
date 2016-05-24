<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi Drupal Winner'),
  'description' => t('Provides SOMI Drupal Winner Info'),
  'content_types' => 'somi_drupal_winner',
  'single' => TRUE,
  'render callback' => 'somi_drupal_winner_content_type_render',
  'category' => t('Somi'),
  'hook theme' => 'somi_drupal_winner_content_type_theme',
);

/**
 * Output function for the content type.
 */
function somi_drupal_winner_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';
  $account_data = somi_get_board_account_data(SOMI_DRUPAL_CURRENCY_TID);

  $block->content = theme('somi_board', array('data' => $account_data, 'title' => 'Доска котнрибьюта'));
  return $block;
}

/**
 * CCT hook_theme.
 */
function somi_drupal_winner_content_type_theme(&$theme, $plugin) {
  $theme['somi_drupal_winner'] = array(
    'variables' => array(),
    'path' => $plugin['path'],
    'template' => 'somi-drupal-winner',
  );
}
