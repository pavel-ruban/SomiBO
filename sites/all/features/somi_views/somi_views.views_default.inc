<?php
/**
 * @file
 * somi_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function somi_views_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'notifications';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'notifications';
  $view->human_name = 'Объявления';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Notifications';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    4 => '4',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Notifications: Taxonomy */
  $handler->display->display_options['relationships']['tid']['id'] = 'tid';
  $handler->display->display_options['relationships']['tid']['table'] = 'notifications';
  $handler->display->display_options['relationships']['tid']['field'] = 'tid';
  $handler->display->display_options['relationships']['tid']['label'] = 'Taxonomy tid';
  /* Relationship: Notifications: Users */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'notifications';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Имя пользователя';
  /* Field: Notifications: Message */
  $handler->display->display_options['fields']['message']['id'] = 'message';
  $handler->display->display_options['fields']['message']['table'] = 'notifications';
  $handler->display->display_options['fields']['message']['field'] = 'message';
  $handler->display->display_options['fields']['message']['label'] = 'Сообщение';
  /* Field: Notifications: Date */
  $handler->display->display_options['fields']['date']['id'] = 'date';
  $handler->display->display_options['fields']['date']['table'] = 'notifications';
  $handler->display->display_options['fields']['date']['field'] = 'date';
  $handler->display->display_options['fields']['date']['label'] = 'Дата';
  $handler->display->display_options['fields']['date']['date_format'] = 'short';
  $handler->display->display_options['fields']['date']['second_date_format'] = 'long';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['relationship'] = 'tid';
  $handler->display->display_options['fields']['name_1']['label'] = 'Таксономия';
  /* Field: Field: Color */
  $handler->display->display_options['fields']['field_color']['id'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['table'] = 'field_data_field_color';
  $handler->display->display_options['fields']['field_color']['field'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['relationship'] = 'tid';
  $handler->display->display_options['fields']['field_color']['label'] = 'Цвет';
  /* Field: Taxonomy term: Icon */
  $handler->display->display_options['fields']['field_icon']['id'] = 'field_icon';
  $handler->display->display_options['fields']['field_icon']['table'] = 'field_data_field_icon';
  $handler->display->display_options['fields']['field_icon']['field'] = 'field_icon';
  $handler->display->display_options['fields']['field_icon']['relationship'] = 'tid';
  $handler->display->display_options['fields']['field_icon']['label'] = 'Иконка';
  $handler->display->display_options['fields']['field_icon']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_icon']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => '',
  );
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['group'] = 1;
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Имя пользователя';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Taxonomy term: Name */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['relationship'] = 'tid';
  $handler->display->display_options['filters']['name']['group'] = 1;
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Таксономия';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Field: Color (field_color) */
  $handler->display->display_options['filters']['field_color_tid']['id'] = 'field_color_tid';
  $handler->display->display_options['filters']['field_color_tid']['table'] = 'field_data_field_color';
  $handler->display->display_options['filters']['field_color_tid']['field'] = 'field_color_tid';
  $handler->display->display_options['filters']['field_color_tid']['relationship'] = 'tid';
  $handler->display->display_options['filters']['field_color_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_color_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_color_tid']['expose']['operator_id'] = 'field_color_tid_op';
  $handler->display->display_options['filters']['field_color_tid']['expose']['label'] = 'Цвет';
  $handler->display->display_options['filters']['field_color_tid']['expose']['operator'] = 'field_color_tid_op';
  $handler->display->display_options['filters']['field_color_tid']['expose']['identifier'] = 'field_color_tid';
  $handler->display->display_options['filters']['field_color_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['field_color_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_color_tid']['vocabulary'] = 'color';
  /* Filter criterion: Notifications: Date */
  $handler->display->display_options['filters']['date']['id'] = 'date';
  $handler->display->display_options['filters']['date']['table'] = 'notifications';
  $handler->display->display_options['filters']['date']['field'] = 'date';
  $handler->display->display_options['filters']['date']['operator'] = 'between';
  $handler->display->display_options['filters']['date']['group'] = 1;
  $handler->display->display_options['filters']['date']['exposed'] = TRUE;
  $handler->display->display_options['filters']['date']['expose']['operator_id'] = 'date_op';
  $handler->display->display_options['filters']['date']['expose']['label'] = 'Дата';
  $handler->display->display_options['filters']['date']['expose']['operator'] = 'date_op';
  $handler->display->display_options['filters']['date']['expose']['identifier'] = 'date';
  $handler->display->display_options['filters']['date']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['date']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['date']['year_range'] = '-1:+1';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'notifications';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Объявления';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'menu-common-admin-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['notifications'] = $view;

  $view = new view();
  $view->name = 'rfid_nodes';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Узлы';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Узлы';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_type' => 'field_type',
    'device_image' => 'device_image',
    'status' => 'status',
    'field_color_picker' => 'field_color_picker',
    'field_i20_property' => 'field_i20_property',
    'changed' => 'changed',
    'field_granting_date' => 'field_granting_date',
    'edit_node' => 'edit_node',
    'delete_node' => 'delete_node',
    'publish_node' => 'publish_node',
    'unpublish_node' => 'unpublish_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'device_image' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_color_picker' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_i20_property' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_granting_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'delete_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'publish_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'unpublish_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Узел';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Rfid ID */
  $handler->display->display_options['fields']['field_rfid_node_id']['id'] = 'field_rfid_node_id';
  $handler->display->display_options['fields']['field_rfid_node_id']['table'] = 'field_data_field_rfid_node_id';
  $handler->display->display_options['fields']['field_rfid_node_id']['field'] = 'field_rfid_node_id';
  $handler->display->display_options['fields']['field_rfid_node_id']['label'] = 'ID';
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_type']['id'] = 'field_type';
  $handler->display->display_options['fields']['field_type']['table'] = 'field_data_field_type';
  $handler->display->display_options['fields']['field_type']['field'] = 'field_type';
  $handler->display->display_options['fields']['field_type']['label'] = 'Тип';
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Статус';
  $handler->display->display_options['fields']['status']['type'] = 'on-off';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Дата изменения';
  $handler->display->display_options['fields']['changed']['date_format'] = 'long';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'long';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Изменить';
  $handler->display->display_options['fields']['edit_node']['text'] = 'изменить';
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = 'Удалить';
  $handler->display->display_options['fields']['delete_node']['text'] = 'удалить';
  /* Field: Content: Publish link */
  $handler->display->display_options['fields']['publish_node']['id'] = 'publish_node';
  $handler->display->display_options['fields']['publish_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['publish_node']['field'] = 'publish_node';
  $handler->display->display_options['fields']['publish_node']['label'] = 'Изменить статус';
  $handler->display->display_options['fields']['publish_node']['text'] = 'активировать';
  /* Field: Content: Unpublish link */
  $handler->display->display_options['fields']['unpublish_node']['id'] = 'unpublish_node';
  $handler->display->display_options['fields']['unpublish_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['unpublish_node']['field'] = 'unpublish_node';
  $handler->display->display_options['fields']['unpublish_node']['label'] = 'Изменить статус';
  $handler->display->display_options['fields']['unpublish_node']['text'] = 'деактивировать';
  /* Field: Global: Reference button */
  $handler->display->display_options['fields']['ref_dialog_button']['id'] = 'ref_dialog_button';
  $handler->display->display_options['fields']['ref_dialog_button']['table'] = 'views';
  $handler->display->display_options['fields']['ref_dialog_button']['field'] = 'ref_dialog_button';
  $handler->display->display_options['fields']['ref_dialog_button']['label'] = 'Выбрать';
  $handler->display->display_options['fields']['ref_dialog_button']['text'] = 'ок';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'node' => 'node',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Узел';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Content: Rfid ID (field_rfid_node_id) */
  $handler->display->display_options['filters']['field_rfid_node_id_value']['id'] = 'field_rfid_node_id_value';
  $handler->display->display_options['filters']['field_rfid_node_id_value']['table'] = 'field_data_field_rfid_node_id';
  $handler->display->display_options['filters']['field_rfid_node_id_value']['field'] = 'field_rfid_node_id_value';
  $handler->display->display_options['filters']['field_rfid_node_id_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_rfid_node_id_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_rfid_node_id_value']['expose']['operator_id'] = 'field_rfid_node_id_value_op';
  $handler->display->display_options['filters']['field_rfid_node_id_value']['expose']['label'] = 'ID';
  $handler->display->display_options['filters']['field_rfid_node_id_value']['expose']['operator'] = 'field_rfid_node_id_value_op';
  $handler->display->display_options['filters']['field_rfid_node_id_value']['expose']['identifier'] = 'field_rfid_node_id_value';
  $handler->display->display_options['filters']['field_rfid_node_id_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );

  /* Display: Reference dialog Search */
  $handler = $view->new_display('references_dialog', 'Reference dialog Search', 'references_dialog_1');
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['attach'] = array(
    0 => 'node:field_rfid_nodes:rfid_tag',
  );

  /* Display: rfid_nodes */
  $handler = $view->new_display('page', 'rfid_nodes', 'rfid_nodes');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Узел';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Rfid ID */
  $handler->display->display_options['fields']['field_rfid_node_id']['id'] = 'field_rfid_node_id';
  $handler->display->display_options['fields']['field_rfid_node_id']['table'] = 'field_data_field_rfid_node_id';
  $handler->display->display_options['fields']['field_rfid_node_id']['field'] = 'field_rfid_node_id';
  $handler->display->display_options['fields']['field_rfid_node_id']['label'] = 'ID';
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_type']['id'] = 'field_type';
  $handler->display->display_options['fields']['field_type']['table'] = 'field_data_field_type';
  $handler->display->display_options['fields']['field_type']['field'] = 'field_type';
  $handler->display->display_options['fields']['field_type']['label'] = 'Тип';
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Статус';
  $handler->display->display_options['fields']['status']['type'] = 'unicode-yes-no';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Дата изменения';
  $handler->display->display_options['fields']['changed']['date_format'] = 'long';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'long';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Изменить';
  $handler->display->display_options['fields']['edit_node']['text'] = 'изменить';
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = 'Удалить';
  $handler->display->display_options['fields']['delete_node']['text'] = 'удалить';
  /* Field: Content: Publish link */
  $handler->display->display_options['fields']['publish_node']['id'] = 'publish_node';
  $handler->display->display_options['fields']['publish_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['publish_node']['field'] = 'publish_node';
  $handler->display->display_options['fields']['publish_node']['label'] = 'Изменить статус';
  $handler->display->display_options['fields']['publish_node']['text'] = 'активировать';
  /* Field: Content: Unpublish link */
  $handler->display->display_options['fields']['unpublish_node']['id'] = 'unpublish_node';
  $handler->display->display_options['fields']['unpublish_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['unpublish_node']['field'] = 'unpublish_node';
  $handler->display->display_options['fields']['unpublish_node']['label'] = 'Изменить статус';
  $handler->display->display_options['fields']['unpublish_node']['text'] = 'деактивировать';
  $handler->display->display_options['path'] = 'admin/rfid-nodes';
  $export['rfid_nodes'] = $view;

  return $export;
}
