<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi Bugs Winner'),
  'description' => t('Provides SOMI Bugs Winner Info'),
  'content_types' => 'somi_bugs_winner',
  'single' => TRUE,
  'render callback' => 'somi_bugs_winner_content_type_render',
  'category' => t('Somi'),
);

/**
 * Output function for the content type.
 */
function somi_bugs_winner_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  $account_data = somi_get_board_account_data(SOMI_BUGS_CURRENCY_TID);

  $block->content = theme('somi_board', array('data' => $account_data, 'title' => 'Доска наказаний'));
  return $block;
}
