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

  $result = db_query("select * from log ORDER BY access DESC;")->fetchAllAssoc('access');

  $event_ids = array();
  $event_rfids = array();

  foreach ($result as $row) {
    $event_ids[$row->uid] = $row->uid;
    $event_rfids[$row->id] = $row->id;
  }

  $users = user_load_multiple($event_ids);
  $rfids = node_load_multiple($event_rfids);

  foreach ($result as $row) {
    if (!isset($chart_data[$row->uid])) {
      $chart_data[$row->uid] = array(
        'uid' => $row->uid,
        'time' => array(),
        'card' => $rfids[$row->id]->title,
        'name' => $users[$row->uid]->name,
        'access_count' => 0,
      );
    }

    $chart_data[$row->uid]['time'][] = $row->access;
    ++$chart_data[$row->uid]['access_count'];
  }

  // Sort by access count.
  usort($chart_data, function($a, $b) {
    if ($a['access_count'] == $b['access_count']) {
      return 0;
    }
    return ($a['access_count'] < $b['access_count']) ? 1 : -1;
  });

  $result = db_query("select * from log ORDER BY access DESC LIMIT 60;")->fetchAllAssoc('access');

  foreach ($result as $row) {
    if (($account = $users[$row->uid]) && ($rfid = $rfids[$row->id])) {
      $events_data[] = array(
        'uid' => $account->uid,
        'time' => $row->access,
        'card' => $rfid->title,
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

/**
 * @param $v
 * @return string
 */
function chart_list_user_link($v) {
  $link = sprintf('<span>count</span>: <span class=\"count\">%s</span> <span>id</span>: %s <span>card</span>: "%s" %s',
    $v['access_count'],
    $v['uid'],
    $v['card'],
    l("{$v['name']}", "/admin/somi/chart/{$v['uid']}", ['attributes' => ['title' => 'Открыть детальный график по пользователю ' . $v['name']]])
  );

  return $link;
}

/**
 * @param $event
 * @return string
 */
function event_list_user_link($event) {

  $link = sprintf('%s<div class="wrapper"><div><span>uid</span>: %s | <span class="time">%s</span></div><div><span>card</span>: "%s"</div><div>%s</div></div>',
    !empty($event['mail'])
      ? ("<img class=\"avatar\" src=\"http://www.gravatar.com/avatar/" . md5($event['mail']) . "\" />")
      : "<img src=\"http://www.gravatar.com/avatar\" />",
    $event['uid'],
    date('H:i:s d.m.y', $event['time']),
    $event['card'],
    "{$event['name']}"
  );
  return $link;
}