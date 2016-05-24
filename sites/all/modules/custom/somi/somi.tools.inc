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
    if (!empty($rfid->title)) {
      if ($devices) {
        $devices .= ' ';
      }
      $devices .= $rfid->title;
    }
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
function somi_get_web_rfid_by_user($account) {
  $storage = &drupal_static(__FUNCTION__);

  if (!isset($storage[$account->uid])) {
    $web_request_rfid_type_tid = SOMI_WEB_REQUEST_RFID_TYPE_TID;

    $query = <<<START_QUERY
      SELECT n.nid FROM field_data_field_rfid_tags fr

      INNER JOIN users u ON u.uid = fr.entity_id
      INNER JOIN node n ON n.nid = fr.field_rfid_tags_target_id
      INNER JOIN field_data_field_type ft ON ft.entity_type = 'node'
       AND ft.bundle = 'rfid_tag' AND ft.deleted = 0 AND ft.entity_id = n.nid

      WHERE fr.entity_type = 'user' AND fr.bundle = 'user' AND fr.deleted = 0
       AND n.status = 1 AND  u.status = 1
       AND field_type_tid = $web_request_rfid_type_tid AND u.uid = {$account->uid}
START_QUERY;

    if ($nids = db_query($query)->fetchCol()) {
      $nid = array_shift($nids);
      if ($rfid = node_load($nid)) {
        $storage[$account->uid] = $rfid;
      }
    }

    if (!isset($storage[$account->uid])) {
      $storage[$account->uid] = FALSE;
    }
  }

  return $storage[$account->uid];
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
function somi_get_device_type_by_nid($nid, $plain = FALSE) {
  $storage = &drupal_static(__FUNCTION__, []);
  if ($node = node_load($nid)) {
    if (!isset($storage[$nid])) {
      if (!empty($node->field_type[LANGUAGE_NONE][0]['tid']) && ($type = taxonomy_term_load($node->field_type[LANGUAGE_NONE][0]['tid']))) {
        if (!$plain) {
          $type_view = taxonomy_term_view($type, 'icon');
          if (!empty($type_view['field_icon'])) {
            $type_view['field_icon'][0]['#item']['title'] = $device_type = $type->name;
            $device_type = drupal_render($type_view['field_icon']);
          }
          else {
            $device_type = $type->name;
          }
        }
        else {
          $device_type = $type->name;
        }
      }
      else {
        $device_type = 'карта';
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
function
somi_get_device_color_by_nid($nid, $plain = FALSE) {
  $storage = &drupal_static(__FUNCTION__, []);

  if ($node = node_load($nid)) {
    if (!isset($storage[$nid])) {
      if (!empty($node->field_color[LANGUAGE_NONE][0]['tid']) && ($color = taxonomy_term_load($node->field_color[LANGUAGE_NONE][0]['tid']))) {
        if (!$plain) {
          $color_view = taxonomy_term_view($color, 'icon');
          if (!empty($color_view['field_color_picker'])) {
            $color_view['field_color_picker'][0]['#title'] = $color->name;
            $device_color = drupal_render($color_view['field_color_picker']);
          }
          else {
            $device_color = $color->name;
          }
        }
        else {
          $device_color = $color->name;
        }
      }
      else {
        $device_color = '-';
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
    ':drupal:' => [
      'active' => SOMI_DRUPAL_CURRENCY_TID,
      'passive' => SOMI_I20_DRUPAL_CURRENCY_TID
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
    ':drupal:' => [1 => 'друпликон', 2 => 'друпликона', 3 => 'друпликонов'],
  ];
}

/**
 * Service callback to add additional validate for main form level & for all actions.
 */
function somi_set_additional_validate_callback(&$form, $name, $first = FALSE) {
  if (!empty($first)) {
    array_unshift($form['#validate'], $name);
  }
  else {
    $form['#validate'][] = $name;
  }
  if (!empty($form['actions'])) {
    foreach (element_children($form['actions']) as $key) {
      // Add new #validate if any one already exists, is no - main form level validates will be triggered.
      if ($key != 'delete' && !empty($form['actions'][$key]['#validate'])) {
        if (!empty($first)) {
          array_unshift($form['actions'][$key]['#validate'], $name);
        }
        else {
          $form['actions'][$key]['#validate'][] = $name;
        }
      }
    }
  }
}

/**
 * Service callback to add additional submit for main form level & for all actions.
 */
function somi_set_additional_submit_callback(&$form, $name, $first = FALSE) {
  if (!empty($first)) {
    array_unshift($form['#submit'], $name);
  }
  else {
    $form['#submit'][] = $name;
  }
  if (!empty($form['actions'])) {
    foreach (element_children($form['actions']) as $key) {
      // Add new #validate if any one already exists, is no - main form level validates will be triggered.
      if ($key != 'delete' && !empty($form['actions'][$key]['#submit'])) {
        if (!empty($first)) {
          array_unshift($form['actions'][$key]['#submit'], $name);
        }
        else {
          $form['actions'][$key]['#submit'][] = $name;
        }
      }
    }
  }
}

/**
 * Get availability data.
 * @throws \Exception
 */
function somi_get_availability_data() {
  $storage = &drupal_static(__FUNCTION__);

  if (!isset($storage)) {
    $query = "select * from log WHERE access >= " . strtotime(date('d M y 05:00')) . " AND access <" . strtotime(date('Y-m-d 05:00:00') . ' + 1 day') . ";";

    $availability_data = array();

    $result = db_query($query)->fetchAllAssoc('access');

    foreach ($result as $row) {
      if (!empty($availability_data[$row->uid]['access'])) {
        $access = $availability_data[$row->uid]['access'] < $row->access
          ? $row->access
          : $availability_data[$row->uid]['access'];
      }
      else {
        $access = $row->access;
      }

      $availability_data[$row->uid] = array(
        'uid' => $row->uid,
        'name' => '',
        'access' => $access,
        'sort' => (int) $access,
        'image_url' => '',
        'image_class' => 'active',
      );
    }

    uasort($availability_data, function ($a, $b) {
      if ($a['access'] == $b['access']) {
        return 0;
      }

      return $a['access'] > $b['access']
        ? -1
        : 1;
    });

    $uids = db_query('select uid from users WHERE status = 1')->fetchCol();
    $users = user_load_multiple($uids);

    foreach ($users as $uid => $account) {
      if (!isset($availability_data[$account->uid])) {
        $availability_data[$account->uid] = array(
          'uid' => $account->uid,
          'name' => $account->name,
          'access' => 0,
          'sort' => 0,
          'image_url' => "http://www.gravatar.com/avatar/" . md5($account->mail),
          'image_class' => 'grayscale',
        );
      }
      else {
        $availability_data[$account->uid]['image_url'] = "http://www.gravatar.com/avatar/" . md5($account->mail);
        $availability_data[$account->uid]['name'] = $account->name;
      }
    }

    foreach ($availability_data as $key => &$item) {
      $class = $item['access'] ? 'active' : 'grayscale';

      $item = [
        'uid' => $item['uid'],
        'info' => $item['access'] ? date('H:i:s', $item['access']) : '',
        'class' => $class,
        'l' => l(
          theme('image', ['path' => $item['image_url'],
            'attributes' => [
              'title' => $item['name'] . ($item['access'] ? (PHP_EOL . date('H:i:s', $item['access'])) : ''),
              'class' => [$class]
            ]
          ]),
          '/admin/somi/chart/' . $item['uid'],
          ['html' => TRUE]
        )
      ];
    }

    $storage = $availability_data;
  }

  return $storage;
}
/**
 * Get board accoutn data.
 * @throws \Exception
 */
function somi_get_board_account_data($currency_tid) {
  $storage = &drupal_static(__FUNCTION__, array());

  if (!isset($storage[$currency_tid])) {
    $account_data = array();

    $uids = db_query('select uid from users WHERE status = 1')->fetchCol();
    $users = user_load_multiple($uids);

    foreach ($users as $uid => $account) {
      $balance = somi_get_user_account_balance($account->uid, $currency_tid);

      $account_data[$account->uid] = array(
        'uid' => $account->uid,
        'name' => $account->name,
        'balance' => $balance,
        'sort' => $balance,
        'image_url' => "http://www.gravatar.com/avatar/" . md5($account->mail),
        'image_class' => $balance ? 'active' : 'grayscale',
      );
    }

    uasort($account_data, function($a, $b) {
      if ($a['balance'] == $b['balance']) return 0;

      return $a['balance'] > $b['balance']
        ? -1
        : 1;
    });

    foreach ($account_data as $key => &$item) {
      $class = $item['balance'] ? 'active' : 'grayscale';

      $item = [
        'uid' => $item['uid'],
        'balance' => $item['balance'],
        'info' => $item['balance'],
        'class' => $class,
        'l' => l(
          theme('image', ['path' => $item['image_url'],
            'attributes' => [
              'title' => $item['name'] . ($item['balance'] ? (PHP_EOL . 'Баланс: ' . $item['balance']) : ''),
              'class' => [$class]
            ]
          ]),
          '/admin/user/' . $item['uid'] . '/account/' . $currency_tid,
          ['html' => TRUE]
        )
      ];
    }

    $storage[$currency_tid] = $account_data;
  }

  return $storage[$currency_tid];
}