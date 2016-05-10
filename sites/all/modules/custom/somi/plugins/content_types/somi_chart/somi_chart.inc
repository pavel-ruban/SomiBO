<?php

/**
 * @file
 * CTools content type for In region, list external links, poll block
 */

$plugin = array(
  'title' => t('Somi Chart.'),
  'description' => t('Provides Somi Charts'),
  'content_types' => 'somi_chart',
  'single' => TRUE,
  'render callback' => 'somi_chart_content_type_render',
  'category' => t('Somi'),
  'hook theme' => 'somi_chart_content_type_theme',
);

/**
 * Output function for the content type.
 */
function somi_chart_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  if (user_access('access somi logs')) {

    $condition = '';
    $start_date = '';
    $end_date = '';

    // Handle date selection query condition.
    if (!empty($_POST['ok']) && empty($_POST['reset'])) {
      if (!empty($_POST['start-date']) && ($start_time = strtotime($_POST['start-date']))) {
        $condition .= (empty($condition) ? 'WHERE ' : ' AND ') . 'access >= ' . $start_time;
      }
      if (!empty($_POST['end-date']) && ($end_time = strtotime($_POST['end-date']))) {
        $condition .= (empty($condition) ? 'WHERE ' : ' AND ') . 'access <= ' . $end_time;
      }

      // Fill default values for date inputs;
      $start_date = $_POST['start-date'];
      $end_date = $_POST['end-date'];
    }

    $query = db_query("select * from log $condition;");

    $chart_data = array();

    $result = $query->fetchAllAssoc();

    $query = db_query("select * from log ORDER BY access DESC LIMIT 150;");

    $event_data = array();

    $event_result = $query->fetchAllAssoc();

    while ($row = $result->fetch_object()) {
      if (!isset($chart_data[$row->id])) {
        $chart_data[$row->id] = array(
          'id' => $row->id,
          'time' => array(),
          'card' => '',
          'name' => '',
          'surname' => '',
          'patronymic' => '',
          'access_count' => 0,
        );
      }

      $chart_data[$row->id]['time'][] = $row->access;
    }

    $event_ids = array();

    foreach ($event_result as $row) {
      $event_ids[$row['id']] = $row['id'];
    }

    $ids = implode(',', array_unique(array_merge(array_keys($chart_data), $event_ids)));

    $user_data = array();
    $user_data_i = array();

    if (!empty($ids)) {
      $query = "select * from rfids where id in ($ids);";
      $user_data = $conn->query($query)->fetch_all(MYSQLI_ASSOC);

      foreach ($user_data as $i => $row) {
        $user_data_i[$row['id']] = $row;

        if (!empty($chart_data[$row['id']])) {
          $chart_data[$row['id']]['card'] = $row['card'];
          $chart_data[$row['id']]['name'] = $row['name'];
          $chart_data[$row['id']]['surname'] = $row['surname'];
          $chart_data[$row['id']]['patronymic'] = $row['patronymic'];
          $chart_data[$row['id']]['access_count'] = count($chart_data[$row['id']]['time']);
        }
      }

      // Sort by access count.
      usort($chart_data, function($a, $b) {
        if ($a['access_count'] == $b['access_count']) {
          return 0;
        }
        return ($a['access_count'] < $b['access_count']) ? 1 : -1;
      });
    }

    unset($user_data);

    foreach ($event_result as $row) {
      if (!empty($user_data_i[$row['id']])) {
        $d = $user_data_i[$row['id']];

        $event_data[] = array(
          'id' => $row['id'],
          'time' => $row['access'],
          'card' => $d['card'],
          'name' => $d['name'],
          'surname' => $d['surname'],
          'patronymic' => $d['patronymic'],
          'mail' => $d['mail'],
        );
      }
    }

    unset($user_data_i);

    $block->content = theme('somi_chart', ['events' => $event_data]);
  }

  return $block;
}
/**
 * CCT hook_theme.
 */
function somi_chart_content_type_theme(&$theme, $plugin) {
  $theme['somi_chart'] = array(
    'variables' => array(),
    'path' => $plugin['path'],
    'template' => 'somi-chart',
  );
}
