<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi Time Of Arrival'),
  'description' => t('Provides SOMI Time of Personal Arrival'),
  'content_types' => 'somi_time_of_arrival',
  'single' => TRUE,
  'render callback' => 'somi_time_of_arrival_content_type_render',
  'category' => t('Somi'),
);

/**
 * Output function for the content type.
 */
function somi_time_of_arrival_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';
  $title = "Время прихода сотрудников I20 на " . date('d.m.y', time()) . ", текущее время " . date('H:i:s', time());

  drupal_add_css(SOMI_MODULE_PATH . '/theme/css/availability.css');

  $departaments_links = somi_get_departaments_filter('admin/somi/time-of-arrival');

  $block->content = theme('somi_board', array(
    'title' => $title,
    'class' => 'availability',
    'data' => somi_get_time_of_arrival_data(somi_get_departament_tid_from_panel_args($panel_args)),
    'departament_links' => $departaments_links
  ));
  return $block;
}