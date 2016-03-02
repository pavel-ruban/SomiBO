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

  $query = db_query("select * from log;");


  $query = "select * from log ORDER BY access DESC LIMIT 60;";

  $chart_data = array();
  $event_data = array();

  $result = db_query("select * from log ORDER BY access DESC LIMIT 60;")->fetchAllAssoc('id');

  foreach ($result as $id => $row) {
    if (!isset($chart_data[$row->uid])) {
      $chart_data[$row->uid] = array(
        'id' => $row->uid,
        'time' => array(),
        'card' => '',
        'name' => '',
        'surname' => '',
        'patronymic' => '',
        'access_count' => 0,
      );
    }

    $chart_data[$row->uid]['time'][] = $row->access;
  }

  $event_ids = array();

  foreach ($result as $id => $row) {
    $event_ids[$row->uid] = $row->uid;
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

  $block->content = theme('somi_logs', array());
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

/**
 * @param $v
 * @return string
 */
function chart_list_user_link($v) {
  $link = sprintf('<span>count</span>: <span class=\"count\">%s</span> <span>id</span>: %s <span>card</span>: "%s" %s',
    $v['access_count'],
    $v['id'],
    $v['card'],
    "<a href=\"/chart/{$v['id']}\" title=\"открыть детальный график по пользователю\">"
    . "{$v['surname']} {$v['name']} {$v['patronymic']}" . '</a>'
  );

  return $link;
}

/**
 * @param $event
 * @return string
 */
function event_list_user_link($event) {

  $link = sprintf('%s<div class="wrapper"><div><span>id</span>: %s | <span class="time">%s</span></div><div><span>card</span>: "%s"</div><div>%s</div></div>',
    !empty($event['mail'])
      ? ("<img class=\"avatar\" src=\"http://www.gravatar.com/avatar/" . md5($event['mail']) . "\" />")
      : "<img src=\"http://www.gravatar.com/avatar\" />",
    $event['id'],
    date('H:i:s d.m', $event['time']),
    $event['card'],
    "{$event['surname']} {$event['name']} {$event['patronymic']}"
  );
  return $link;
}