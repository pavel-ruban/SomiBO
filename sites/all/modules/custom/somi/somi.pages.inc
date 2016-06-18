<?php

/**
 * @file
 */

/**
 * Page callback: Displays add taxonomy links for available content types.
 */
function somi_taxonomy_add_page($check = FALSE) {
  static $items;

  if (empty($items)) {
    $vocs = taxonomy_vocabulary_get_names();
    $items = array();
    foreach ($vocs as $machine_name => $voc) {
      if (user_access("edit terms in $machine_name")) {
        $items[] = array(
          'localized_options  ' => [],
          'description' => '',
          'href' => "admin/structure/taxonomy/{$machine_name}/add",
          'title' => "Add {$voc->name}",
        );
      }
    }
  }

  if (!empty($check)) {
    return count($items);
  }
  else {
    if (count($items) == 1) {
      drupal_goto("admin/structure/taxonomy/{$machine_name}/add");
    } else {
      return theme('node_add_list', array('content' => $items));
    }
  }
}

/**
 * Opens Somi Door.
 */
function somi_open_node($node_id) {
  global $user;
  $server_ip   = gethostbyname(SOMI_SERVER_HOST);;
  $server_port = SOMI_SERVER_PORT;

  // @todo make dynamic node_id open.
  switch ($node_id) {
    case 255:
      $message = "command: admin academ open $node_id";
      break;

    default:
      $message = "command: admin open $node_id";
      break;
  }

  ob_clean();

  header('content-type: application:json');

  if ($socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP)) {
    socket_sendto($socket, $message, strlen($message), 0, $server_ip, $server_port);
    echo drupal_json_encode(['status' => "OK"]);
  } else {
    echo drupal_json_encode(['status' => "can't create socket"]);
  }

  if ($rfid = somi_get_web_rfid_by_user($user)) {
    $context = array(
      'uid' => $user->uid,
      'rfid' => $rfid->nid,
      'rfid_node' => 0,
      'name' => $user->name,
      'time' => time(),
      'mail' => $user->mail,
      'card' => $rfid->title,
    );

    module_load_include('inc', 'somi', 'somi.drush');
    somi_log_event($context, 1);
  }
  drupal_exit();
}

function somi_access_handler($id = FALSE) {
  if (($device = somi_get_rfid_by_id($id)) && ($account = somi_get_user_by_rfid($id))) {
    $w = entity_metadata_wrapper('user', $account);

    // If user active.
    if ($w->status->value() && !empty($device->status)) {
      return TRUE;
    }
  }

  return FALSE;
}

/**
 * Used to display content on Android Board.
 */
function somi_realtime_board() {
  drupal_add_css(SOMI_MODULE_PATH . '/theme/css/availability.css');

  drupal_add_css(SOMI_MODULE_PATH . '/theme/css/realtime_board.css');
  drupal_add_js(SOMI_MODULE_PATH . '/theme/js/realtime_board.js');

  // Realtime data update.
  drupal_add_library('somi', 'jquery-color');
  drupal_add_library('somi', 'socket-io');
  $title = "Активность сотрудников I20";

  return theme('somi_board', array('title' => $title, 'class' => 'availability', 'data' => somi_get_availability_data()));
}