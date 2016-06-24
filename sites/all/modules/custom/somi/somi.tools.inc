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

  $node = "ресепшен";
  $rfid_node = somi_get_rfid_pcd_node_by_id($event['rfid_node']);
  if (!empty($rfid_node->title)) {
    $node = $rfid_node->title;
  }

  $link = sprintf('%s<div class="wrapper"><div>%s</div><div><span>uid</span>: %s | <span class="time">%s</span></div><div><span>card</span>: "%s" <span>node</span>: "%s"</div><div class="type-icon"><span>type</span>: %s <span>color</span>: %s</div></div>',
    l($img, '/admin/somi/chart/' . $event['uid'], ['html' => TRUE]),
    "{$event['name']}",
    $event['uid'],
    date('H:i:s d.m.y', $event['time']),
    $event['card'],
    $node,
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
function somi_get_default_currency_config_array_template() {
  return [
    // Падежи и склонения.
    'nominative' => [
      1 => 'Кристалл',
      2 => 'Кристалла',
      3 => 'Кристаллов'
    ],
    'prepositional' => [
      1 => 'Кристалле',
      2 => 'Кристаллах',
      3 => 'Кристаллах'
    ],
    'accusative' => [
      1 => 'Кристалл',
      2 => 'Кристалла',
      3 => 'Кристаллов'
    ],
    'instrumental' => [
      1 => 'Кристаллом',
      2 => 'Кристаллами',
      3 => 'Кристаллами'
    ],

    // Op translations.
    'error_status' => [
      'msg' => '*Сделка на %qty% %goods% не удалась!* =>no_entry_sign=>\n\n*Отправитель*',
      'case' => 'accusative'
    ],

    'op_header' => 'Награждение кристаллами',

    'event_error' => '_Произошла ошибка при награждении_',
    'event_remind' => '_Напоминание_',
    'event_private' => [
      'msg' => '_Вам подарили %qty% %goods% от %usr%_',
      'case' => 'nominative'
    ],
    'event_owner' => [
      'msg' => '_Вы подарили %qty% %goods% %users%_',
      'case' => 'nominative'
    ],
    'event_channel' => [
      'alt' => '_Был(а) награжден(а) %users%_',
      'msg' => '_Были награждены %users%_',
      'case' => 'nominative'
    ],

    'op_status' => [
      'msg' => '*Сделка на %qty% %goods% прошла успешно!* =>white_check_mark=>\n\n*От кого*',
      'case' => 'nominative'
    ],
    'op_status_private' => [
      'msg' => '*Вы получили %qty% %goods%!* %currencies%\n\n*От кого*',
      'case' => 'accusative'
    ],
    'op_status_remind' => [
      'msg' => '=>bell=> *Вы хотели подарить %qty% %currency%*',
      'case' => 'accusative'
    ],

    'attach_balance_remind_title' => 'Кристаллов на вашем счете',
    'attach_balance_private_title' => 'Кристаллов в наличии',
    'attach_balance_owner_title' => 'Кристаллов осталось',
    'attach_balance_needed_title' => 'Не хватает кристаллов',
    'op_color' => 'good',
    'op_remind' => 'Подарить'
  ];
}

/**
 * @return array
 */
function somi_api_account_currencies_mapping() {
  $storage = &drupal_static(__FUNCTION__, NULL);

  if (!isset($storage)) {
    $storage = array();

    $cp = config_pages_load_entity('somi_settings');
    $cpw = entity_metadata_wrapper('config_pages', $cp);

    foreach ($cpw->field_currencies as $fcw) {
      if ($fcw->value()) {
        $storage[$fcw->field_emoticon->value()] = array(
          'active' => $fcw->field_active_account->getIdentifier(),
          'passive' => $fcw->field_passive_account->getIdentifier(),
        );
      }
    }
  }

  return $storage;
}

/**
 * @return array
 */
function somi_api_get_somi_config($force = FALSE, $time = NULL) {
  $storage = &drupal_static(__FUNCTION__, NULL);

  if (!isset($storage) || $force) {
    if (!$time) $time = time();

    $cp = config_pages_load_entity('somi_settings');
    $cpw = entity_metadata_wrapper('config_pages', $cp);

    if ($force || $cp->changed > $time) {
      $storage = [];
      foreach ($cpw->field_currencies as $fcw) {
        if ($fcw->value()) {

          $raw_emoticon = preg_replace('/:/', '', $fcw->field_emoticon->value());

          //default config.
          $storage['config'][$raw_emoticon] = somi_get_default_currency_config_array_template();

          // fill array according settings if it's not empty.
          foreach ($fcw->field_cases_declensions as $fcdw) {
            if ($case = $fcdw->field_case->value()) {
              $case = $case->name;
              if ($declension = $fcdw->field_1_declension->value()) {
                $storage['config'][$raw_emoticon][$case][1] = $declension;
              }
              if ($declension = $fcdw->field_2_declension->value()) {
                $storage['config'][$raw_emoticon][$case][2] = $declension;
              }
              if ($declension = $fcdw->field_3_declension->value()) {
                $storage['config'][$raw_emoticon][$case][3] = $declension;
              }
            }
          }

          // fill array according settings if it's not empty.
          foreach ($fcw->field_slack_op as $fsow) {
            if (($op = $fsow->field_op_id->value()) && ($msg = $fsow->field_op_msg->value())) {
              if ($case = $fsow->field_case->value()) {
                $case = $case->name;
                $storage['config'][$raw_emoticon][$op] = [
                  'msg' => $msg,
                  'case' => $case
                ];

                if ($alt = $fsow->field_op_alt->value()) {
                  $storage['config'][$raw_emoticon][$op]['alt'] = $alt;
                }
              }
              else {
                $storage['config'][$raw_emoticon][$op] = $msg;
              }
            }
          }
        }
      }

      foreach ($cpw->field_notifications->value() as $notification) {
        $term = taxonomy_term_load($notification->field_notifications_term[LANGUAGE_NONE][0]['tid']);
        $tid = $term->tid;
        $term_wrapper = entity_metadata_wrapper('taxonomy_term', $term);
        $storage['warnings'][$tid]['color'] = $term_wrapper->field_color->field_color_picker->rgb->value();
        $storage['warnings'][$tid]['op_header'] = $term_wrapper->field_op_msg->value();
        $storage['warnings'][$tid]['icon'] = str_replace('api/', '', file_create_url($term_wrapper->field_icon->value()['uri']));
        foreach ($notification->field_react_on[LANGUAGE_NONE] as $react) {
          $storage['warnings'][$tid]['react_on'][] = $react['value'];
        }
        foreach ($term_wrapper->field_webhooks->value() as $webhook) {
          $storage['warnings'][$tid]['webhooks'][] = $webhook->field_webhook_url[LANGUAGE_NONE][0]['value'];
        }
      }

      $storage['timestamp'] = $cp->changed;
    }
  }

  return $storage;
}

/**
 * @return array
 */
function somi_currencies_translations() {
  $storage = &drupal_static(__FUNCTION__, NULL);

  if (!isset($storage)) {
    $storage = array();

    $cp = config_pages_load_entity('somi_settings');
    $cpw = entity_metadata_wrapper('config_pages', $cp);

    if ($nominative_case_tid = taxonomy_get_term_by_name('nominative', 'cases')) {
      $nominative_case_tid = reset($nominative_case_tid)->tid;

      foreach ($cpw->field_currencies as $fcw) {
        if ($fcw->value() && $fcw->field_cases_declensions->value()) {
          foreach ($fcw->field_cases_declensions as $fcdw) {
            if ($fcdw->field_case->getIdentifier() == $nominative_case_tid) {
              $storage[$fcw->field_emoticon->value()] = array(
                1 => drupal_strtolower($fcdw->field_1_declension->value()),
                2 => drupal_strtolower($fcdw->field_2_declension->value()),
                3 => drupal_strtolower($fcdw->field_3_declension->value()),
              );

              break;
            }
          }
        }
      }
    }
  }

  return $storage;
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
function somi_get_availability_data($department_tid = NULL) {
  $storage = &drupal_static(__FUNCTION__);

  if (!isset($storage)) {
    $start_date = strtotime(date('d M y 05:00'));
    $end_date = strtotime(date('Y-m-d 05:00:00') . ' + 1 day');

    if (!empty($department_tid)) {
      $query = <<<QUERY
      SELECT l.* FROM log l
      INNER JOIN users u ON l.uid = u.uid
      INNER JOIN field_data_field_department fd ON fd.entity_id = u.uid AND fd.bundle = 'user' AND fd.deleted = 0
      INNER JOIN taxonomy_term_data td ON fd.field_department_target_id = td.tid
      WHERE u.status = 1 AND fd.field_department_target_id = $department_tid AND l.access >= $start_date AND l.access < $end_date
      ORDER BY access ASC
QUERY;
    } else {
      $query = "select l.* from log l INNER JOIN users u ON u.uid = l.uid WHERE u.status = 1 AND l.access >= " . $start_date . " AND l.access <" . $end_date . ";";
    }

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
        'node_id' => $row->node_id,
        'access' => $access,
        'sort' => (int) $access,
        'image_url' => '',
        'image_class' => 'active',
      );
    }

    $get = $_GET;

    uasort($availability_data, function ($a, $b) use($get) {
      if ($a['access'] == $b['access']) {
        return 0;
      }

      if (!empty($get['sort_order'])) {
        return $a['access'] > $b['access']
          ? 1
          : -1;
      }
      else {
        return $a['access'] > $b['access']
          ? -1
          : 1;
      }
    });


    if (!empty($department_tid)) {
      $query = <<<QUERY
      SELECT uid FROM users u
      INNER JOIN field_data_field_department fd ON fd.entity_id = u.uid AND fd.bundle = 'user' AND fd.deleted = 0
      INNER JOIN taxonomy_term_data td ON fd.field_department_target_id = td.tid
      WHERE u.status = 1 AND fd.field_department_target_id = $department_tid
QUERY;
    } else {
      $query = 'select uid from users WHERE status = 1';
    }

    $uids = db_query($query)->fetchCol();
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


    if (!empty($_GET['groupby'])) {
      switch ($_GET['groupby']) {
        case 1:
          $availability_data_by_dep = [];
          foreach ($availability_data as $uid => $item) {
            $account = user_load($uid);
            $aw = entity_metadata_wrapper('user', $account);

            if ($department_tid = $aw->field_department->getIdentifier()) {
              $availability_data_by_dep[$department_tid][$uid] = $item;
              $availability_data_by_dep[$department_tid][$uid]['group'] = $aw->field_department->value()->name;
            }
          }

          $availability_data = [];
          foreach($availability_data_by_dep as $group) {
            foreach ($group as $uid => $user_data) {
              $availability_data[$uid] = $user_data;
            }
          }
          break;

        case 2;
          $availability_data_by_node = [];
          foreach ($availability_data as $uid => $item) {
            if (isset($item['node_id'])) {
              $availability_data_by_node[$item['node_id']][$uid] = $item;
              $availability_data_by_node[$item['node_id']][$uid]['group'] = somi_get_rfid_pcd_node_by_id($item['node_id'])->title;
            }
            else {
              $availability_data_by_node['misc'][$uid] = $item;
              $availability_data_by_node['misc'][$uid]['group'] = 'misc';
            }
          }

          $availability_data = [];
          foreach($availability_data_by_node as $group) {
            foreach ($group as $uid => $user_data) {
              $availability_data[$uid] = $user_data;
            }
          }
          break;
      }
    }

    foreach ($availability_data as $key => &$item) {
      $class = $item['access'] ? 'active' : 'grayscale';

      $group = !empty($item['group']) ? $item['group'] : NULL;

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
          drupal_valid_path('admin/somi/chart')
            ? ('/admin/somi/chart/' . $item['uid'])
            : ('admin/user/' . $item['uid'] . '/account'),
          ['html' => TRUE]
        )
      ];

      if ($group) $item['group'] = $group;
    }

    $storage = $availability_data;
  }

  return $storage;
}

/**
 * Get availability data.
 * @throws \Exception
 */
function somi_get_time_of_arrival_data($department_tid = NULL) {
  $storage = &drupal_static(__FUNCTION__);

  if (!isset($storage)) {
    if (!empty($_GET['date']['date'])) {
      $morning_limit = strtotime(date($_GET['date']['date'] . ' 05:00'));
      $evening_limit = strtotime(date($_GET['date']['date'] . ' 05:00:00') . ' + 1 day');
    }
    else {
      $morning_limit = strtotime(date('d M y 05:00'));
      $evening_limit = strtotime(date('Y-m-d 05:00:00') . ' + 1 day');
    }

    if (!empty($department_tid)) {
      $query = <<<QUERY
      SELECT l.* FROM log l
      INNER JOIN users u ON l.uid = u.uid
      INNER JOIN field_data_field_department fd ON fd.entity_id = u.uid AND fd.bundle = 'user' AND fd.deleted = 0
      INNER JOIN taxonomy_term_data td ON fd.field_department_target_id = td.tid
      WHERE u.status = 1 AND fd.field_department_target_id = $department_tid AND l.access >= $morning_limit AND l.access < $evening_limit
      ORDER BY access ASC
QUERY;
    } else {
      $query = "SELECT l.* FROM log l INNER JOIN users u ON l.uid = u.uid WHERE l.access >= $morning_limit AND l.access < $evening_limit ORDER BY l.access ASC";
    }

    $availability_data = array();

    $result = db_query($query)->fetchAllAssoc('access');

    foreach ($result as $row) {
      if (empty($availability_data[$row->uid]['access'])) {
        $access = $row->access;

        $availability_data[$row->uid] = array(
          'uid' => $row->uid,
          'name' => '',
          'access' => $access,
          'departament' => 0,
          'last_access' => NULL,
          'sort' => (int) $access,
          'image_url' => '',
          'image_class' => 'active',
        );
      }
    }

    if (!empty($department_tid)) {
      $query = <<<QUERY
      SELECT l.* FROM log l
      INNER JOIN users u ON l.uid = u.uid
      INNER JOIN field_data_field_department fd ON fd.entity_id = u.uid AND fd.bundle = 'user' AND fd.deleted = 0
      INNER JOIN taxonomy_term_data td ON fd.field_department_target_id = td.tid
      WHERE u.status = 1 AND fd.field_department_target_id = $department_tid AND l.access >= $morning_limit AND l.access < $evening_limit
      ORDER BY access DESC
QUERY;
    } else {
      $query = "SELECT l.* FROM log l INNER JOIN users u ON l.uid = u.uid WHERE l.access >= $morning_limit AND l.access < $evening_limit ORDER BY l.access DESC";
    }

    $result = db_query($query)->fetchAllAssoc('access');

    foreach ($result as $row) {
      if (isset($availability_data[$row->uid]) && empty($availability_data[$row->uid]['last_access'])) {
        $availability_data[$row->uid]['last_access'] = $row->access;
        $availability_data[$row->uid]['node_id'] = $row->node_id;
      }
    }

    switch (TRUE) {
      case empty($_GET['sort']):
        $sort = 'access';
        break;

      case $_GET['sort'] == 1:
        $sort = 'last_access';
        break;

      case $_GET['sort'] == 2:
        $sort = 'average';
        break;

      default:
        $sort = 'access';
        break;
    }

    uasort($availability_data, function ($a, $b) use($sort) {
      if ($sort == 'average') {
        $ax = $a['last_access'] - $a['access'];
        $bx = $b['last_access'] - $b['access'];
      }
      else {
        $ax = $a[$sort];
        $bx = $b[$sort];
      }

      if ($ax == $bx) {
        return 0;
      }

      if (!empty($_GET['sort_order'])) {
        return $ax > $bx
          ? 1
          : -1;
      } else {
        return $ax > $bx
          ? -1
          : 1;
      }
    });


    if (!empty($department_tid)) {
      $query = <<<QUERY
      SELECT * FROM users u
      INNER JOIN field_data_field_department fd ON fd.entity_id = u.uid AND fd.bundle = 'user' AND fd.deleted = 0
      INNER JOIN taxonomy_term_data td ON fd.field_department_target_id = td.tid
      WHERE u.status = 1 AND fd.field_department_target_id = $department_tid
QUERY;
    } else {
      $query = "select uid from users WHERE status = 1";
    }
    $uids = db_query($query)->fetchCol();
    $users = user_load_multiple($uids);

    foreach ($users as $uid => $account) {
      if (!isset($availability_data[$account->uid])) {
        $availability_data[$account->uid] = array(
          'uid' => $account->uid,
          'name' => $account->name,
          'access' => 0,
          'departament' => 0,
          'last_access' => 0,
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

    if (!empty($_GET['groupby'])) {
      switch ($_GET['groupby']) {
        case 1:
          $availability_data_by_dep = [];
          foreach ($availability_data as $uid => $item) {
            $account = user_load($uid);
            $aw = entity_metadata_wrapper('user', $account);

            if ($department_tid = $aw->field_department->getIdentifier()) {
              $availability_data_by_dep[$department_tid][$uid] = $item;
              $availability_data_by_dep[$department_tid][$uid]['group'] = $aw->field_department->value()->name;
            }
          }

          $availability_data = [];
          foreach($availability_data_by_dep as $group) {
            foreach ($group as $uid => $user_data) {
              $availability_data[$uid] = $user_data;
            }
          }
          break;

        case 2;
          $availability_data_by_node = [];
          foreach ($availability_data as $uid => $item) {
            if (isset($item['node_id'])) {
              $availability_data_by_node[$item['node_id']][$uid] = $item;
              $availability_data_by_node[$item['node_id']][$uid]['group'] = somi_get_rfid_pcd_node_by_id($item['node_id'])->title;
            }
            else {
              $availability_data_by_node['misc'][$uid] = $item;
              $availability_data_by_node['misc'][$uid]['group'] = 'misc';
            }
          }

          $availability_data = [];
          foreach($availability_data_by_node as $group) {
            foreach ($group as $uid => $user_data) {
              $availability_data[$uid] = $user_data;
            }
          }
          break;
      }
    }

    foreach ($availability_data as $key => &$item) {
      $class = $item['access'] ? 'active' : 'grayscale';

      $in_date = new DateTime(date('Y-m-d H:i:s', $item['access']));
      $work_time = $in_date->diff(new DateTime(date('Y-m-d H:i:s', $item['last_access'])));

      $group = !empty($item['group']) ? $item['group'] : NULL;

      $item = [
        'uid' => $item['uid'],
        'info' => $item['last_access'] ? date('H:i:s', $item['last_access']) : '',
        'sub_info' => $item['access'] ? date('H:i:s', $item['access']) : '',
        'top_info' => str_pad($work_time->h, 2, '0', STR_PAD_LEFT) . ':' . str_pad($work_time->i, 2, '0', STR_PAD_LEFT),
        'class' => $class,
        'l' => l(
          theme('image', ['path' => $item['image_url'],
            'attributes' => [
              'title' => $item['name'] . ($item['access'] ? (PHP_EOL . date('H:i:s', $item['access'])) : ''),
              'class' => [$class]
            ]
          ]),
          drupal_valid_path('admin/somi/chart')
            ? ('/admin/somi/chart/' . $item['uid'])
          : ('admin/user/' . $item['uid'] . '/account'),
          ['html' => TRUE]
        )
      ];

      if ($group) $item['group'] = $group;
    }

    $storage = $availability_data;
  }

  return $storage;
}

/**
 * @return bool
 */
function somi_is_mobile_agent() {
  $mobile_browser = '0';

  if (preg_match('/(up.browser|up.link|mmp|symbian|smartphone|midp|wap|phone|android)/i', strtolower($_SERVER['HTTP_USER_AGENT']))) {
    $mobile_browser++;
  }

  if ((strpos(strtolower($_SERVER['HTTP_ACCEPT']),'application/vnd.wap.xhtml+xml') > 0) or ((isset($_SERVER['HTTP_X_WAP_PROFILE']) or isset($_SERVER['HTTP_PROFILE'])))) {
    $mobile_browser++;
  }

  $mobile_ua = strtolower(substr($_SERVER['HTTP_USER_AGENT'], 0, 4));
  $mobile_agents = array(
    'w3c ','acs-','alav','alca','amoi','audi','avan','benq','bird','blac',
    'blaz','brew','cell','cldc','cmd-','dang','doco','eric','hipt','inno',
    'ipaq','java','jigs','kddi','keji','leno','lg-c','lg-d','lg-g','lge-',
    'maui','maxo','midp','mits','mmef','mobi','mot-','moto','mwbp','nec-',
    'newt','noki','oper','palm','pana','pant','phil','play','port','prox',
    'qwap','sage','sams','sany','sch-','sec-','send','seri','sgh-','shar',
    'sie-','siem','smal','smar','sony','sph-','symb','t-mo','teli','tim-',
    'tosh','tsm-','upg1','upsi','vk-v','voda','wap-','wapa','wapi','wapp',
    'wapr','webc','winw','winw','xda ','xda-');

  if (in_array($mobile_ua,$mobile_agents)) {
    $mobile_browser++;
  }

  if (!empty($_SERVER['ALL_HTTP']) && strpos(strtolower($_SERVER['ALL_HTTP']), 'OperaMini') > 0) {
    $mobile_browser++;
  }

  if (strpos(strtolower($_SERVER['HTTP_USER_AGENT']), 'windows') > 0) {
    $mobile_browser = 0;
  }

  if (preg_match('/iPad/i', $_SERVER['HTTP_USER_AGENT']) || $mobile_browser > 0) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Build departament filter links and sort them by scores of accounts summary.
 *
 * @param $path
 * @param null $dep_scores
 * @return array
 */
function somi_get_departaments_filter($path, $dep_scores = NULL) {
  // Build departament filter links and sort them by scores of accounts summary.
  $voc = taxonomy_vocabulary_machine_name_load('departament');
  $departaments = taxonomy_get_tree($voc->vid);
  $departaments_links = [];

  $get = $_GET;
  unset($get['q']);

  array_walk($departaments, function($dep) use (&$departaments_links, $dep_scores, $path, $get) {
    $score = !empty($dep_scores[$dep->tid]) ? " ({$dep_scores[$dep->tid]})" : '';

    $departaments_links[$dep->tid] = l($dep->name . $score, $path . '/' . $dep->tid, ['query' => $get]);
  });

  uksort($departaments_links, function($a, $b) use ($dep_scores) {
    if (!empty($_GET['sort_order'])) {
      $x = 1; $y = -1;
    }
    else {
      $x = -1; $y = 1;
    }

    if (!empty($dep_scores[$a]) && !empty($dep_scores[$b])) {
      return $dep_scores[$a] > $dep_scores[$b] ? $x : $y;
    }
    elseif (!empty($dep_scores[$a])) {
      return -1;
    }
    elseif (!empty($dep_scores[$b])) {
      return 1;
    }

    return 0;
  });

  return array_merge([l(t('Все отделы'), $path, ['query' => $get])], $departaments_links);
}

/**
 * Get board accoutn data.
 * @throws \Exception
 */
function somi_get_board_account_data($currency_tid, $department_tid = 0, &$departament_scores = []) {
  $storage = &drupal_static(__FUNCTION__, array());

  if (!isset($storage[$currency_tid])) {
    $account_data = array();

    if (!empty($department_tid)) {
      $query = <<<QUERY
SELECT uid FROM users u
INNER JOIN field_data_field_department fd ON fd.entity_id = u.uid AND fd.bundle = 'user' AND fd.deleted = 0
INNER JOIN taxonomy_term_data td ON fd.field_department_target_id = td.tid
WHERE status = 1 AND fd.field_department_target_id = $department_tid;
QUERY;
      $uids = db_query($query)->fetchCol();

      $all_dep_uids = db_query('select uid from users WHERE status = 1')->fetchCol();
    } else {
      $uids = db_query('select uid from users WHERE status = 1')->fetchCol();
    }

    $users = user_load_multiple($uids);

    if (!empty($all_dep_uids)) {
      $all_dep_users = user_load_multiple($all_dep_uids);
      unset($all_dep_uids);
    }
    else {
      $all_dep_users = $users;
    }

    foreach ($all_dep_users as $uid => $account) {
      $balance = somi_get_user_account_balance($account->uid, $currency_tid);

      $uw = entity_metadata_wrapper('user', $account);
      if ($dep = $uw->field_department->value()) {
        if (!isset($departament_scores[$dep->tid])) {
          $departament_scores[$dep->tid] = 0;
        }

        $departament_scores[$dep->tid] += $balance;
      }
    }

    unset($all_dep_users);

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

      if (!$a['balance']) return 1;
      if (!$b['balance']) return -1;
      
      if (!empty($_GET['sort_order'])) {
        return $a['balance'] > $b['balance']
          ? 1
          : -1;
      }
      else {
        return $a['balance'] > $b['balance']
          ? -1
          : 1;
      }
    });

    if (!empty($_GET['groupby'])) {
      $account_data_by_dep = [];
      foreach ($account_data as $uid => $item) {
        $account = user_load($uid);
        $aw = entity_metadata_wrapper('user', $account);

        if ($department_tid = $aw->field_department->getIdentifier()) {
          $account_data_by_dep[$department_tid][$uid] = $item;
          $account_data_by_dep[$department_tid][$uid]['group'] = $aw->field_department->value()->name;
        }
      }

      uksort($account_data_by_dep, function($a, $b) use($departament_scores) {
        if ($departament_scores[$a] == $departament_scores[$b]) {
          return 0;
        }

        if (!$departament_scores[$a]) return 1;
        if (!$departament_scores[$b]) return -1;

        if (!empty($_GET['sort_order'])) {
          return $departament_scores[$a] > $departament_scores[$b]
            ? 1
            : -1;
        }
        else {
          return $departament_scores[$a] > $departament_scores[$b]
            ? -1
            : 1;
        }
      });

      $account_data = [];
      foreach ($account_data_by_dep as $group) {
        foreach ($group as $uid => $user_data) {
          $account_data[$uid] = $user_data;
        }
      }
    }
    
    foreach ($account_data as $key => &$item) {
      $class = $item['balance'] ? 'active' : 'grayscale';

      $group = !empty($item['group']) ? $item['group'] : NULL;

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

      if ($group) $item['group'] = $group;

    }

    $storage[$currency_tid] = $account_data;
  }

  return $storage[$currency_tid];
}

/**
 * @param $role
 * @return mixed
 */
function somi_get_role_account_month_limit($role) {
  $month_limits = &drupal_static(__FUNCTION__, NULL);

  if (!isset($month_limits[$role])) {
    $month_limits[$role] = 0;

    $cp = config_pages_load_entity('somi_settings');
    $cpw = entity_metadata_wrapper('config_pages', $cp);

      if ($cpw->field_limit->value()) {
        switch ($role) {
          case 'top':
          case 'core':
          case 'active':
            $month_limits[$role] = $cpw->field_limit->{"field_{$role}_limit"}->value();
            break;

        default:
          $month_limits['default'] = $month_limits[$role] = $cpw->field_limit->{"field_regular_limit"}->value();

      }
    }
  }

  return isset($month_limits[$role]) ? $month_limits[$role] : $month_limits['default'];
}

/**
 * @return array
 */
function somi_get_cron_account_balance_tids() {
  $cron_account_tids = &drupal_static(__FUNCTION__, NULL);

  if (!isset($cron_account_tids)) {
    $cron_account_tids = array();

    $cp = config_pages_load_entity('somi_settings');
    $cpw = entity_metadata_wrapper('config_pages', $cp);

    if ($cpw->field_cron_accounts->value()) {
      foreach ($cpw->field_cron_accounts as $caw) {
        if ($account_tid = $caw->getIdentifier()) {
          $cron_account_tids[$account_tid] = $account_tid;
        }
      }
    }
  }

  return $cron_account_tids;
}

/**
 * @param $args
 * @return null
 */
function somi_get_departament_tid_from_panel_args($args) {
  foreach ($args as $arg) {
    if (is_numeric($arg)) {
      if ($department_term = taxonomy_term_load($arg)) {
        if ($department_term->vocabulary_machine_name == 'departament') {
          return $department_term->tid;
        }
      }
    }
  }

  return NULL;
}

function somi_get_rfid_pcd_node_by_id($id) {
  $storage = &drupal_static(__FUNCTION__, []);

  if (!isset($storage[$id])) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'node');
    $query->fieldCondition('field_rfid_node_id', 'value', $id, '=')
      ->range(0, 1);

    $result = $query->execute();

    if (isset($result['node'])) {
      $storage[$id] = node_load(reset($result['node'])->nid);
    }
    else {
      $storage[$id] = FALSE;
    }
  }

  return $storage[$id];
}

/**
 * Form callback.
 */
function somi_group_order_board_form($form, &$form_state) {
  $form = [
    '#method' => 'GET',
    'groupby' => [
      '#title' => 'Группировка',
      '#description' => 'По департаменту',
      '#single' => TRUE,
      '#type' => 'radios',
      '#options' => ['отсутствует', 'департамен', 'нода'],
      '#default_value' => !empty($_GET['groupby']) ? $_GET['groupby'] : 0,
    ],
    'sort_order' => [
      '#title' => 'Порядок',
      '#type' => 'select',
      '#options' => ['DESC', 'ASC'],
      '#default_value' => !empty($_GET['sort_order']) ? $_GET['sort_order'] : 0,
    ],
    'submit' => [
      '#type' => 'submit',
      '#value' => t('ok'),
    ]
  ];

  return $form;
}

/**
 * Form callback.
 */
function somi_group_order_score_board_form($form, &$form_state) {
  $form = [
    '#method' => 'GET',
    'groupby' => [
      '#title' => 'Группировка',
      '#description' => 'По департаменту',
      '#single' => TRUE,
      '#type' => 'radios',
      '#options' => ['отсутствует', 'департамен'],
      '#default_value' => !empty($_GET['groupby']) ? $_GET['groupby'] : 0,
    ],
    'sort_order' => [
      '#title' => 'Порядок',
      '#type' => 'select',
      '#options' => ['DESC', 'ASC'],
      '#default_value' => !empty($_GET['sort_order']) ? $_GET['sort_order'] : 0,
    ],
    'submit' => [
      '#type' => 'submit',
      '#value' => t('ok'),
    ]
  ];

  return $form;
}