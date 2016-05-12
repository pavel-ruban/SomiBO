<?php

/**
 * Used to provide russian plurals without translation subsystem.
 * @param $a
 * @param $str1
 * @param $str2
 * @param $str3
 * @return mixed
 */
function plural_str($a, $str1, $str2, $str3) {
  if ($a == 0) return $str3;
  elseif ($a % 10 == 1 && $a % 100 != 11) return $str1;
  else if (($a % 10 >= 2) && ($a % 10 <= 4) && ($a % 100 < 10 || $a % 100 >= 20)) return $str2;
  else return $str3;
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

  $d = somi_get_rfid_by_id($event['card']);
  $w = entity_metadata_wrapper('node', $d);
  $color = $w->field_color->value();
  $type = $w->field_type->value();

  $device_type = somi_get_device_type_by_nid($d->nid);
  $device_color = somi_get_device_color_by_nid($d->nid);
  $img = !empty($event['mail'])
    ? ("<img class=\"avatar\" src=\"http://www.gravatar.com/avatar/" . md5($event['mail']) . "\" />")
    : "<img src=\"http://www.gravatar.com/avatar\" />";

  $link = sprintf('%s<div class="wrapper"><div>%s</div><div><span>uid</span>: %s | <span class="time">%s</span></div><div><span>card</span>: "%s"</div><div class="type-icon"><span>type</span>: %s <span>color</span>: %s</div></div>',
    l($img, '/admin/somi/chart/' . $event['uid'], ['html' => TRUE]),
    "{$event['name']}",
    $event['uid'],
    date('H:i:s d.m.y', $event['time']),
    $event['card'],
    $device_type,
    $device_color
  );
  return $link;
}

/**
 * @param $uid
 * @return string
 */
function somi_get_user_devices($uid) {
  $account = user_load($uid);
  $w = entity_metadata_wrapper('user', $account);
  $rfids = $w->field_rfid_tags->value();
  $devices = '';
  foreach ($rfids as $rfid) {
    if ($devices) $devices .= ' ';
    $devices .= $rfid->title;
  }

  return $devices;
}

/**
 * @param $v
 * @return string
 */
function chart_user_title($uid) {
  $account = user_load($uid);
  $devices = somi_get_user_devices($uid);

  $link = sprintf('<span>uid</span>: %s <span>devices</span>: "%s" %s',
    $uid,
    $devices,
    $account->name
  );

  return $link;
}

/**
 * @param $id
 * @return mixed
 */
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

/**
 * @param $id
 * @return mixed
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
 * @param $nid
 * @return bool
 */
function somi_get_device_type_by_nid($nid) {
  $storage = &drupal_static(__FUNCTION__, []);

  if ($node = node_load($nid)) {
    if (!isset($storage[$nid])) {
      $wrapper = entity_metadata_wrapper('node', $node);
      if ($type = $wrapper->field_type->value()) {
        $type_view = taxonomy_term_view($type, 'icon');
        if (!empty($type_view['field_icon'])) {
          $device_type = drupal_render($type_view['field_icon']);
        }
        else {
          $device_type = $type->name;
        }
      }
      else {
        $device_type = '';
      }

      $storage[$nid] = $device_type;
    }

    return $storage[$nid];
  }

  return FALSE;
}

/**
 * @param $nid
 * @return bool
 */
function somi_get_device_color_by_nid($nid) {
  $storage = &drupal_static(__FUNCTION__, []);

  if ($node = node_load($nid)) {
    if (!isset($storage[$nid])) {
      $wrapper = entity_metadata_wrapper('node', $node);
      if ($color = $wrapper->field_color->value()) {
        $color_view = taxonomy_term_view($color, 'icon');
        if (!empty($color_view['field_color_picker'])) {
          $device_color = drupal_render($color_view['field_color_picker']);
        }
        else {
          $device_color = $color->name;
        }
      }
      else {
        $device_color = '';
      }

      $storage[$nid] = $device_color;
    }

    return $storage[$nid];
  }

  return FALSE;
}

/**
 * @return array
 */
function somi_api_account_currencies_mapping() {
  return [
    ':gem:' => [
      'active' => SOMI_CRYSTALLS_CURRENCY_TID,
      'passive' => SOMI_I20_CRYSTALLS_CURRENCY_TID
    ],
    ':beetle:' => [
      'active' => SOMI_BUGS_CURRENCY_TID,
      'passive' => SOMI_I20_BUGS_CURRENCY_TID
    ],
  ];
}

/**
 * @return array
 */
function somi_currencies_translations() {
  return [
    ':gem:' => [1 => 'кристалл', 2 => 'кристалла', 3 => 'кристаллов'],
    ':beetle:' => [1 => 'жук', 2 => 'жука', 3 => 'жуков'],
  ];
}