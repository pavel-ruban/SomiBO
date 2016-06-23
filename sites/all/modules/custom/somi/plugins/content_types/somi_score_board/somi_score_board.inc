<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi Score Board'),
  'description' => t('Provides SOMI Score Board'),
  'content_types' => 'somi_score_board',
  'single' => TRUE,
  'render callback' => 'somi_score_board_content_type_render',
  'category' => t('Somi'),
);

/**
 * Output function for the content type.
 */
function somi_score_board_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  if (!empty($panel_args[0]) && is_numeric($panel_args[0])) {
    if ($currency_term = taxonomy_term_load($panel_args[0])) {
      if ($currency_term->vocabulary_machine_name == 'currencies') {

        $form = drupal_get_form('somi_group_order_score_board_form');
        $account_data = somi_get_board_account_data($currency_term->tid, somi_get_departament_tid_from_panel_args($panel_args), $departament_scores);
        $departaments_links = somi_get_departaments_filter('admin/somi/score-board/' . $currency_term->tid, $departament_scores);

        if (!empty($currency_term->field_board_name[LANGUAGE_NONE][0]['value'])) {
          $title = $currency_term->field_board_name[LANGUAGE_NONE][0]['value'];
        }
        else {
          $title = $currency_term->name;
        }

        $block->content = theme('somi_board', array('data' => $account_data, 'title' => $title, 'form' => $form, 'departament_links' => $departaments_links));
      }
    }
  }

  return $block;
}
