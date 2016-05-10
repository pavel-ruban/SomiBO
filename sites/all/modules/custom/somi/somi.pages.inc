<?php

/**
 * @file
 */

function somi_get_user_by_rfid($id) {
  $storage = &drupal_static(__FUNCTION__);

  if (!isset($storage[$id])) {
    $query = db_select('node', 'i');
    $query->addField('rt', 'entity_id', 'uid');

    $query->innerJoin(
      'field_data_field_rfid_tags',
      'rt',
      "rt.field_rfid_tags_target_id = i.nid
     AND rt.entity_type = 'user'
     AND rt.deleted = 0
     AND rt.bundle = 'user'"
    );

    $query->condition('i.type', 'rfid_tag');
    $query->condition('i.title', trim($id));

    if ($uids = $query->execute()->fetchCol()) {
      $uid = array_shift($uids);
      if ($account = user_load($uid)) {
        $storage[$id] = $account;
      }
    }

    if (!isset($storage[$id])) {
      $storage[$id] = FALSE;
    }
  }

  return $storage[$id];
}

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

function somi_get_rfid_by_id($id) {
  $storage = &drupal_static(__FUNCTION__);

  if (!isset($storage[$id])) {
    $query = db_select('node', 'i');
    $query->addField('i', 'nid', 'id');

    $query->condition('i.type', 'rfid_tag');
    $query->condition('i.title', trim($id));

    if ($nids = $query->execute()->fetchCol()) {
      $nid = array_shift($nids);

      if ($rfid = node_load($nid)) {
        $storage[$id] = $rfid;
      }
    }

    if (!isset($storage[$id])) {
      $storage[$id] = FALSE;
    }
  }

  return $storage[$id];
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