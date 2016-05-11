<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi User Logs'),
  'description' => t('Provides SOMI user logs'),
  'content_types' => 'somi_user_logs',
  'single' => TRUE,
  'render callback' => 'somi_user_logs_content_type_render',
  'category' => t('Somi'),
  'hook theme' => 'somi_user_logs_content_type_theme',
);

/**
 * Output function for the content type.
 */
function somi_user_logs_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  $uid = $panel_args[0];

  $account = user_load($uid);

  $chart_data = array();
  $access_data = array();
  $events_data = array();

  $access_count = 0;
  $result = db_query("select * from log WHERE uid = $uid ORDER BY access DESC;")->fetchAllAssoc('access');

  foreach ($result as $row) {
    $month = date('m', $row->access);
    $year = date('Y', $row->access);
    if (!isset($chart_data[$year][$month])) {
      $chart_data[$year][$month] = array(
        'month' => date('M Y', $row->access),
        'access_count' => 0,
      );
    }

    $access_data[] = $row->access;

    ++$chart_data[$year][$month]['access_count'];
    ++$access_count;
  }

  sort($access_data, SORT_ASC | SORT_NUMERIC);

  ksort($chart_data);
  foreach ($chart_data as &$year_data) {
    ksort($year_data);
  }

  if ($access_count < 15) {
    $chart_data = array();

    foreach($access_data as $timestamp) {
      $time = date('H d.m.Y', $timestamp);
      $year = date('Y', $timestamp);

      if (!isset($chart_data[$year][$time])) {
        $chart_data[$year][$time] = array(
          'month' => date('H:00-H:59:59 d.m.Y', $timestamp),
          'access_count' => 0,
        );
      }

      ++$chart_data[$year][$time]['access_count'];
    }
  }
  elseif ($access_count < 60) {

    $chart_data = array();

    foreach($access_data as $timestamp) {
      $day = date('d-m-Y', $timestamp);
      $year = date('Y', $timestamp);
      if (!isset($chart_data[$year][$day])) {
        $chart_data[$year][$day] = array(
          'month' => date('d.m.Y', $timestamp),
          'access_count' => 0,
        );
      }

      ++$chart_data[$year][$day]['access_count'];
    }
  }

  foreach ($result as $row) {
    if ($d = node_load($row->id)) {
      $events_data[] = array(
        'uid' => $uid,
        'time' => $row->access,
        'card' => $d->title,
        'name' => $account->name,
        'mail' => $account->mail,
      );
    }
  }

  drupal_add_library('somi', 'chartjs');
  drupal_add_js(['chartData' => $chart_data], ['type' => 'setting']);
  drupal_add_js(SOMI_MODULE_PATH . '/plugins/content_types/somi_user_logs/chart.js');
  drupal_add_css(SOMI_MODULE_PATH . '/plugins/content_types/somi_user_logs/chart.css');

  $block->content = theme('somi_user_logs', array('events_data' => $events_data, 'chart_data' => $chart_data, 'uid' => $uid, 'access_count' => $access_count));
  return $block;
}

/**
 * CCT hook_theme.
 */
function somi_user_logs_content_type_theme(&$theme, $plugin) {
  $theme['somi_user_logs'] = array(
    'variables' => array(),
    'path' => $plugin['path'],
    'template' => 'somi-user-logs',
  );
}
