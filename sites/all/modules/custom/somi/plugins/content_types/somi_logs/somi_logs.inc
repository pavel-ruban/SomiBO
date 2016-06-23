<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi Logs'),
  'description' => t('Provides SOMI logs'),
  'content_types' => 'somi_logs',
  'single' => TRUE,
  'render callback' => 'somi_logs_content_type_render',
  'category' => t('Somi'),
  'hook theme' => 'somi_logs_content_type_theme',
);

/**
 * Output function for the content type.
 */
function somi_logs_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  $chart_data = array();
  $events_data = array();

  $result = db_query("select l.* from log l INNER JOIN users u ON u.uid = l.uid WHERE u.status = 1 ORDER BY l.access DESC;")->fetchAllAssoc('access');

  $event_ids = array();
  $event_rfids = array();

  foreach ($result as $row) {
    $event_ids[$row->uid] = $row->uid;
    $event_rfids[$row->id] = $row->id;
  }

  $users = user_load_multiple($event_ids);
  $rfids = node_load_multiple($event_rfids);

  foreach ($result as $row) {
    if (!empty($users[$row->uid]) && !empty($rfids[$row->id])) {
      if (!isset($chart_data[$row->uid])) {
        $chart_data[$row->uid] = array(
          'uid' => $row->uid,
          'time' => array(),
          'card' => $rfids[$row->id]->title,
          'name' => $users[$row->uid]->name,
          'access_count' => 0,
        );
      }

      ++$chart_data[$row->uid]['access_count'];
      $chart_data[$row->uid]['time'][] = $row->access;
    }
  }

  // Sort by access count.
  usort($chart_data, function($a, $b) {
    if ($a['access_count'] == $b['access_count']) {
      return 0;
    }
    return ($a['access_count'] < $b['access_count']) ? 1 : -1;
  });

  $result = db_query("select l.* from log l INNER JOIN users u ON u.uid = l.uid WHERE u.status = 1 ORDER BY l.access DESC LIMIT 60;")->fetchAllAssoc('access');

  foreach ($result as $row) {
    if (($account = $users[$row->uid]) && !empty($rfids[$row->id])) {
      $events_data[$account->uid] = array(
        'uid' => $account->uid,
        'time' => $row->access,
        'id' => $row->id,
        'card' => $rfids[$row->id]->title,
        'rfid_node' => $row->node_id,
        'name' => $account->name,
        'mail' => $account->mail,
      );
    }
  }

  drupal_add_library('somi', 'chartjs');
  drupal_add_js(['chartData' => $chart_data], ['type' => 'setting']);
  drupal_add_js(SOMI_MODULE_PATH . '/plugins/content_types/somi_logs/chart.js');
  drupal_add_css(SOMI_MODULE_PATH . '/plugins/content_types/somi_logs/chart.css');

  $block->content = theme('somi_logs', array('events_data' => $events_data, 'chart_data' => $chart_data));
  return $block;
}

/**
 * CCT hook_theme.
 */
function somi_logs_content_type_theme(&$theme, $plugin) {
  $theme['somi_logs'] = array(
    'variables' => array(),
    'path' => $plugin['path'],
    'template' => 'somi_logs',
  );
}