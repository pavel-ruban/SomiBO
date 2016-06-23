<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi Availability'),
  'description' => t('Provides SOMI personal availability'),
  'content_types' => 'somi_availability',
  'single' => TRUE,
  'render callback' => 'somi_availability_content_type_render',
  'category' => t('Somi'),
);

/**
 * Output function for the content type.
 */
function somi_availability_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';
  $title = "Активность сотрудников I20 за " . date('d.m.y', time()) . ", текущее время " . date('H:i:s', time());

  drupal_add_css(SOMI_MODULE_PATH . '/theme/css/availability.css');

  $departaments_links = somi_get_departaments_filter('admin/somi/availability');

  $form = drupal_get_form('somi_group_order_board_form');
  $block->content = theme('somi_board', array(
    'title' => $title,
    'class' => 'availability',
    'data' => somi_get_availability_data(somi_get_departament_tid_from_panel_args($panel_args)),
    'form' => $form,
    'departament_links' => $departaments_links
  ));
  return $block;
}