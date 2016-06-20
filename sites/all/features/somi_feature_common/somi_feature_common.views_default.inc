<?php
/**
 * @file
 * somi_feature_common.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function somi_feature_common_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'Taxonomies';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Taxonomy listing';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Brands';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Reset filters';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '40';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'name' => 'name',
    'field_color_picker' => 'field_color_picker',
    'field_image' => 'field_color_picker',
    'machine_name' => 'machine_name',
    'name_1' => 'name_1',
    'delete_term' => 'delete_term',
    'edit_term' => 'edit_term',
    'field_related_color' => 'field_color_picker',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'name' => array(
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
    'field_image' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'machine_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'name_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'delete_term' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'edit_term' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_related_color' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Bulk operations: Taxonomy term */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::dior_site_views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Field: Taxonomy vocabulary: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['label'] = 'Таксономия';
  /* Field: Taxonomy term: Term edit link */
  $handler->display->display_options['fields']['edit_term']['id'] = 'edit_term';
  $handler->display->display_options['fields']['edit_term']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['edit_term']['field'] = 'edit_term';
  $handler->display->display_options['fields']['edit_term']['label'] = 'Edit';
  /* Field: Taxonomy term: Term delete link */
  $handler->display->display_options['fields']['delete_term']['id'] = 'delete_term';
  $handler->display->display_options['fields']['delete_term']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['delete_term']['field'] = 'delete_term';
  $handler->display->display_options['fields']['delete_term']['label'] = 'Delete';
  /* Filter criterion: Taxonomy term: Name */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['operator'] = 'contains';
  $handler->display->display_options['filters']['name']['group'] = 1;
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );

  /* Display: Таксономии */
  $handler = $view->new_display('page', 'Таксономии', 'taxonomies');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Taxonomies';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    5 => '5',
    4 => '4',
  );
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Bulk operations: Taxonomy term */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['row_clickable'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
  );
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'Название';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Field: Taxonomy term: Color */
  $handler->display->display_options['fields']['field_color_picker']['id'] = 'field_color_picker';
  $handler->display->display_options['fields']['field_color_picker']['table'] = 'field_data_field_color_picker';
  $handler->display->display_options['fields']['field_color_picker']['field'] = 'field_color_picker';
  $handler->display->display_options['fields']['field_color_picker']['label'] = '';
  $handler->display->display_options['fields']['field_color_picker']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_color_picker']['type'] = 'color_field_swatch';
  $handler->display->display_options['fields']['field_color_picker']['settings'] = array(
    'width' => '15',
    'height' => '15',
  );
  /* Field: Field: Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'slack_thumb',
    'image_link' => '',
  );
  /* Field: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['fields']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['fields']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['fields']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['fields']['machine_name']['exclude'] = TRUE;
  /* Field: Taxonomy vocabulary: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['label'] = 'Таксономия';
  $handler->display->display_options['fields']['name_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name_1']['alter']['path'] = 'admin/structure/taxonomy/[machine_name]';
  /* Field: Taxonomy term: Term delete link */
  $handler->display->display_options['fields']['delete_term']['id'] = 'delete_term';
  $handler->display->display_options['fields']['delete_term']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['delete_term']['field'] = 'delete_term';
  $handler->display->display_options['fields']['delete_term']['label'] = 'Удалить';
  $handler->display->display_options['fields']['delete_term']['text'] = 'удалить';
  /* Field: Taxonomy term: Term edit link */
  $handler->display->display_options['fields']['edit_term']['id'] = 'edit_term';
  $handler->display->display_options['fields']['edit_term']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['edit_term']['field'] = 'edit_term';
  $handler->display->display_options['fields']['edit_term']['label'] = 'Изменить';
  $handler->display->display_options['fields']['edit_term']['text'] = 'изменить';
  /* Field: Taxonomy term: Color */
  $handler->display->display_options['fields']['field_related_color']['id'] = 'field_related_color';
  $handler->display->display_options['fields']['field_related_color']['table'] = 'field_data_field_related_color';
  $handler->display->display_options['fields']['field_related_color']['field'] = 'field_related_color';
  $handler->display->display_options['fields']['field_related_color']['label'] = '';
  $handler->display->display_options['fields']['field_related_color']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_related_color']['type'] = 'entityreference_entity_view';
  $handler->display->display_options['fields']['field_related_color']['settings'] = array(
    'view_mode' => 'icon',
    'links' => 1,
  );
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Taxonomy term: Name */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['operator'] = 'contains';
  $handler->display->display_options['filters']['name']['group'] = 1;
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['group'] = 1;
  $handler->display->display_options['filters']['machine_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['machine_name']['expose']['operator_id'] = 'machine_name_op';
  $handler->display->display_options['filters']['machine_name']['expose']['label'] = 'Vocabulary';
  $handler->display->display_options['filters']['machine_name']['expose']['operator'] = 'machine_name_op';
  $handler->display->display_options['filters']['machine_name']['expose']['identifier'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['machine_name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );
  $handler->display->display_options['path'] = 'admin/content/taxonomies';

  /* Display: Currenices Search */
  $handler = $view->new_display('references_dialog', 'Currenices Search', 'references_dialog_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Валюты';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'perform manual account operations';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = 'ID';
  $handler->display->display_options['fields']['tid']['separator'] = '';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Field: Field: Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = 'Изображение';
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'slack_thumb',
    'image_link' => '',
  );
  /* Field: Taxonomy vocabulary: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['label'] = 'Таксономия';
  /* Field: Global: Reference button */
  $handler->display->display_options['fields']['ref_dialog_button']['id'] = 'ref_dialog_button';
  $handler->display->display_options['fields']['ref_dialog_button']['table'] = 'views';
  $handler->display->display_options['fields']['ref_dialog_button']['field'] = 'ref_dialog_button';
  $handler->display->display_options['fields']['ref_dialog_button']['label'] = 'Выбрать';
  $handler->display->display_options['fields']['ref_dialog_button']['text'] = 'ok';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Taxonomy term: Name */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['operator'] = 'contains';
  $handler->display->display_options['filters']['name']['group'] = 1;
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );
  /* Filter criterion: Taxonomy term: Vocabulary */
  $handler->display->display_options['filters']['vid']['id'] = 'vid';
  $handler->display->display_options['filters']['vid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['vid']['field'] = 'vid';
  $handler->display->display_options['filters']['vid']['value'] = array(
    4 => '4',
  );
  $handler->display->display_options['attach'] = array(
    0 => 'config_pages:field_cron_accounts:somi_settings',
    1 => 'field_collection_item:field_active_account:field_currencies',
    2 => 'field_collection_item:field_passive_account:field_currencies',
    3 => 'field_collection_item:field_passive_account:field_op_limit',
  );

  /* Display: Cases Search */
  $handler = $view->new_display('references_dialog', 'Cases Search', 'references_dialog_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Падежи';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'perform manual account operations';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = 'ID';
  $handler->display->display_options['fields']['tid']['separator'] = '';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Field: Taxonomy term: Term description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = 'Описание';
  /* Field: Taxonomy vocabulary: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['label'] = 'Таксономия';
  /* Field: Global: Reference button */
  $handler->display->display_options['fields']['ref_dialog_button']['id'] = 'ref_dialog_button';
  $handler->display->display_options['fields']['ref_dialog_button']['table'] = 'views';
  $handler->display->display_options['fields']['ref_dialog_button']['field'] = 'ref_dialog_button';
  $handler->display->display_options['fields']['ref_dialog_button']['label'] = 'Выбрать';
  $handler->display->display_options['fields']['ref_dialog_button']['text'] = 'ok';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Taxonomy term: Name */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['operator'] = 'contains';
  $handler->display->display_options['filters']['name']['group'] = 1;
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );
  /* Filter criterion: Taxonomy term: Vocabulary */
  $handler->display->display_options['filters']['vid']['id'] = 'vid';
  $handler->display->display_options['filters']['vid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['vid']['field'] = 'vid';
  $handler->display->display_options['filters']['vid']['value'] = array(
    5 => '5',
  );
  $handler->display->display_options['attach'] = array(
    0 => 'field_collection_item:field_case:field_cases_declensions',
    1 => 'field_collection_item:field_case:field_slack_op',
  );

  /* Display: Color Search */
  $handler = $view->new_display('references_dialog', 'Color Search', 'references_dialog_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Цвета';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'perform manual account operations';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = 'ID';
  $handler->display->display_options['fields']['tid']['separator'] = '';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Field: Taxonomy term: Color */
  $handler->display->display_options['fields']['field_color_picker']['id'] = 'field_color_picker';
  $handler->display->display_options['fields']['field_color_picker']['table'] = 'field_data_field_color_picker';
  $handler->display->display_options['fields']['field_color_picker']['field'] = 'field_color_picker';
  $handler->display->display_options['fields']['field_color_picker']['type'] = 'color_field_swatch';
  $handler->display->display_options['fields']['field_color_picker']['settings'] = array(
    'width' => '25',
    'height' => '25',
  );
  /* Field: Taxonomy vocabulary: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['label'] = 'Таксономия';
  /* Field: Global: Reference button */
  $handler->display->display_options['fields']['ref_dialog_button']['id'] = 'ref_dialog_button';
  $handler->display->display_options['fields']['ref_dialog_button']['table'] = 'views';
  $handler->display->display_options['fields']['ref_dialog_button']['field'] = 'ref_dialog_button';
  $handler->display->display_options['fields']['ref_dialog_button']['label'] = 'Выбрать';
  $handler->display->display_options['fields']['ref_dialog_button']['text'] = 'ok';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Taxonomy term: Name */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['operator'] = 'contains';
  $handler->display->display_options['filters']['name']['group'] = 1;
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );
  /* Filter criterion: Taxonomy term: Vocabulary */
  $handler->display->display_options['filters']['vid']['id'] = 'vid';
  $handler->display->display_options['filters']['vid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['vid']['field'] = 'vid';
  $handler->display->display_options['filters']['vid']['value'] = array(
    3 => '3',
  );
  $handler->display->display_options['attach'] = array(
    0 => 'taxonomy_term:field_related_color:departament',
  );

  /* Display: Department Search */
  $handler = $view->new_display('references_dialog', 'Department Search', 'references_dialog_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Департаменты';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'perform manual account operations';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = 'ID';
  $handler->display->display_options['fields']['tid']['separator'] = '';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Field: Taxonomy term: Color */
  $handler->display->display_options['fields']['field_related_color']['id'] = 'field_related_color';
  $handler->display->display_options['fields']['field_related_color']['table'] = 'field_data_field_related_color';
  $handler->display->display_options['fields']['field_related_color']['field'] = 'field_related_color';
  $handler->display->display_options['fields']['field_related_color']['type'] = 'entityreference_entity_view';
  $handler->display->display_options['fields']['field_related_color']['settings'] = array(
    'view_mode' => 'icon',
    'links' => 1,
  );
  /* Field: Taxonomy vocabulary: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['label'] = 'Таксономия';
  /* Field: Global: Reference button */
  $handler->display->display_options['fields']['ref_dialog_button']['id'] = 'ref_dialog_button';
  $handler->display->display_options['fields']['ref_dialog_button']['table'] = 'views';
  $handler->display->display_options['fields']['ref_dialog_button']['field'] = 'ref_dialog_button';
  $handler->display->display_options['fields']['ref_dialog_button']['label'] = 'Выбрать';
  $handler->display->display_options['fields']['ref_dialog_button']['text'] = 'ok';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Taxonomy term: Name */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['operator'] = 'contains';
  $handler->display->display_options['filters']['name']['group'] = 1;
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );
  /* Filter criterion: Taxonomy term: Vocabulary */
  $handler->display->display_options['filters']['vid']['id'] = 'vid';
  $handler->display->display_options['filters']['vid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['vid']['field'] = 'vid';
  $handler->display->display_options['filters']['vid']['value'] = array(
    6 => '6',
  );
  $handler->display->display_options['attach'] = array(
    0 => 'user:field_department:user',
  );
  $export['Taxonomies'] = $view;

  $view = new view();
  $view->name = 'devices';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Устройства';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Устройства';
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
  /* Relationship: Field: Color (field_color) */
  $handler->display->display_options['relationships']['field_color_tid']['id'] = 'field_color_tid';
  $handler->display->display_options['relationships']['field_color_tid']['table'] = 'field_data_field_color';
  $handler->display->display_options['relationships']['field_color_tid']['field'] = 'field_color_tid';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Хэш карты';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_type']['id'] = 'field_type';
  $handler->display->display_options['fields']['field_type']['table'] = 'field_data_field_type';
  $handler->display->display_options['fields']['field_type']['field'] = 'field_type';
  $handler->display->display_options['fields']['field_type']['label'] = 'Тип';
  /* Field: somi: Device Image */
  $handler->display->display_options['fields']['device_image']['id'] = 'device_image';
  $handler->display->display_options['fields']['device_image']['table'] = 'node';
  $handler->display->display_options['fields']['device_image']['field'] = 'device_image';
  $handler->display->display_options['fields']['device_image']['label'] = 'Изображение';
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Статус';
  $handler->display->display_options['fields']['status']['type'] = 'on-off';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Taxonomy term: Color */
  $handler->display->display_options['fields']['field_color_picker']['id'] = 'field_color_picker';
  $handler->display->display_options['fields']['field_color_picker']['table'] = 'field_data_field_color_picker';
  $handler->display->display_options['fields']['field_color_picker']['field'] = 'field_color_picker';
  $handler->display->display_options['fields']['field_color_picker']['relationship'] = 'field_color_tid';
  $handler->display->display_options['fields']['field_color_picker']['label'] = 'Цвет';
  $handler->display->display_options['fields']['field_color_picker']['type'] = 'color_field_swatch';
  $handler->display->display_options['fields']['field_color_picker']['settings'] = array(
    'width' => '15',
    'height' => '15',
  );
  /* Field: Content: Собственность i20 */
  $handler->display->display_options['fields']['field_i20_property']['id'] = 'field_i20_property';
  $handler->display->display_options['fields']['field_i20_property']['table'] = 'field_data_field_i20_property';
  $handler->display->display_options['fields']['field_i20_property']['field'] = 'field_i20_property';
  $handler->display->display_options['fields']['field_i20_property']['type'] = 'list_key';
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Дата изменения';
  $handler->display->display_options['fields']['changed']['date_format'] = 'long';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'long';
  /* Field: Content: Дата выдачи устройства */
  $handler->display->display_options['fields']['field_granting_date']['id'] = 'field_granting_date';
  $handler->display->display_options['fields']['field_granting_date']['table'] = 'field_data_field_granting_date';
  $handler->display->display_options['fields']['field_granting_date']['field'] = 'field_granting_date';
  $handler->display->display_options['fields']['field_granting_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
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
    'rfid_tag' => 'rfid_tag',
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Хэш карты';
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
  /* Filter criterion: Content: Type (field_type) */
  $handler->display->display_options['filters']['field_type_tid']['id'] = 'field_type_tid';
  $handler->display->display_options['filters']['field_type_tid']['table'] = 'field_data_field_type';
  $handler->display->display_options['filters']['field_type_tid']['field'] = 'field_type_tid';
  $handler->display->display_options['filters']['field_type_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_type_tid']['expose']['operator_id'] = 'field_type_tid_op';
  $handler->display->display_options['filters']['field_type_tid']['expose']['label'] = 'Тип';
  $handler->display->display_options['filters']['field_type_tid']['expose']['operator'] = 'field_type_tid_op';
  $handler->display->display_options['filters']['field_type_tid']['expose']['identifier'] = 'field_type_tid';
  $handler->display->display_options['filters']['field_type_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_type_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['field_type_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_type_tid']['vocabulary'] = 'rfid_type';
  $handler->display->display_options['filters']['field_type_tid']['hierarchy'] = 1;
  /* Filter criterion: Field: Color (field_color) */
  $handler->display->display_options['filters']['field_color_tid']['id'] = 'field_color_tid';
  $handler->display->display_options['filters']['field_color_tid']['table'] = 'field_data_field_color';
  $handler->display->display_options['filters']['field_color_tid']['field'] = 'field_color_tid';
  $handler->display->display_options['filters']['field_color_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_color_tid']['expose']['operator_id'] = 'field_color_tid_op';
  $handler->display->display_options['filters']['field_color_tid']['expose']['label'] = 'Цвет';
  $handler->display->display_options['filters']['field_color_tid']['expose']['operator'] = 'field_color_tid_op';
  $handler->display->display_options['filters']['field_color_tid']['expose']['identifier'] = 'field_color_tid';
  $handler->display->display_options['filters']['field_color_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_color_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['field_color_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_color_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_color_tid']['vocabulary'] = 'color';
  $handler->display->display_options['filters']['field_color_tid']['hierarchy'] = 1;

  /* Display: Reference dialog Search */
  $handler = $view->new_display('references_dialog', 'Reference dialog Search', 'references_dialog_1');
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['attach'] = array(
    0 => 'user:field_rfid_tags:user',
  );

  /* Display: devices */
  $handler = $view->new_display('page', 'devices', 'devices');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Хэш карты';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_type']['id'] = 'field_type';
  $handler->display->display_options['fields']['field_type']['table'] = 'field_data_field_type';
  $handler->display->display_options['fields']['field_type']['field'] = 'field_type';
  $handler->display->display_options['fields']['field_type']['label'] = 'Тип';
  /* Field: somi: Device Image */
  $handler->display->display_options['fields']['device_image']['id'] = 'device_image';
  $handler->display->display_options['fields']['device_image']['table'] = 'node';
  $handler->display->display_options['fields']['device_image']['field'] = 'device_image';
  $handler->display->display_options['fields']['device_image']['label'] = 'Изображение';
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Статус';
  $handler->display->display_options['fields']['status']['type'] = 'on-off';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Taxonomy term: Color */
  $handler->display->display_options['fields']['field_color_picker']['id'] = 'field_color_picker';
  $handler->display->display_options['fields']['field_color_picker']['table'] = 'field_data_field_color_picker';
  $handler->display->display_options['fields']['field_color_picker']['field'] = 'field_color_picker';
  $handler->display->display_options['fields']['field_color_picker']['relationship'] = 'field_color_tid';
  $handler->display->display_options['fields']['field_color_picker']['label'] = 'Цвет';
  $handler->display->display_options['fields']['field_color_picker']['type'] = 'color_field_swatch';
  $handler->display->display_options['fields']['field_color_picker']['settings'] = array(
    'width' => '15',
    'height' => '15',
  );
  /* Field: Content: Собственность i20 */
  $handler->display->display_options['fields']['field_i20_property']['id'] = 'field_i20_property';
  $handler->display->display_options['fields']['field_i20_property']['table'] = 'field_data_field_i20_property';
  $handler->display->display_options['fields']['field_i20_property']['field'] = 'field_i20_property';
  $handler->display->display_options['fields']['field_i20_property']['type'] = 'list_key';
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Дата изменения';
  $handler->display->display_options['fields']['changed']['date_format'] = 'long';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'long';
  /* Field: Content: Дата выдачи устройства */
  $handler->display->display_options['fields']['field_granting_date']['id'] = 'field_granting_date';
  $handler->display->display_options['fields']['field_granting_date']['table'] = 'field_data_field_granting_date';
  $handler->display->display_options['fields']['field_granting_date']['field'] = 'field_granting_date';
  $handler->display->display_options['fields']['field_granting_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
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
  $handler->display->display_options['path'] = 'devices';

  /* Display: devices_admin */
  $handler = $view->new_display('page', 'devices_admin', 'admin_devices');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Хэш карты';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_type']['id'] = 'field_type';
  $handler->display->display_options['fields']['field_type']['table'] = 'field_data_field_type';
  $handler->display->display_options['fields']['field_type']['field'] = 'field_type';
  $handler->display->display_options['fields']['field_type']['label'] = 'Тип';
  /* Field: somi: Device Image */
  $handler->display->display_options['fields']['device_image']['id'] = 'device_image';
  $handler->display->display_options['fields']['device_image']['table'] = 'node';
  $handler->display->display_options['fields']['device_image']['field'] = 'device_image';
  $handler->display->display_options['fields']['device_image']['label'] = 'Изображение';
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Статус';
  $handler->display->display_options['fields']['status']['type'] = 'unicode-yes-no';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Taxonomy term: Color */
  $handler->display->display_options['fields']['field_color_picker']['id'] = 'field_color_picker';
  $handler->display->display_options['fields']['field_color_picker']['table'] = 'field_data_field_color_picker';
  $handler->display->display_options['fields']['field_color_picker']['field'] = 'field_color_picker';
  $handler->display->display_options['fields']['field_color_picker']['relationship'] = 'field_color_tid';
  $handler->display->display_options['fields']['field_color_picker']['label'] = 'Цвет';
  $handler->display->display_options['fields']['field_color_picker']['type'] = 'color_field_swatch';
  $handler->display->display_options['fields']['field_color_picker']['settings'] = array(
    'width' => '15',
    'height' => '15',
  );
  /* Field: Content: Собственность i20 */
  $handler->display->display_options['fields']['field_i20_property']['id'] = 'field_i20_property';
  $handler->display->display_options['fields']['field_i20_property']['table'] = 'field_data_field_i20_property';
  $handler->display->display_options['fields']['field_i20_property']['field'] = 'field_i20_property';
  $handler->display->display_options['fields']['field_i20_property']['label'] = 'I20 Собственность';
  $handler->display->display_options['fields']['field_i20_property']['type'] = 'checkboxes';
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Дата изменения';
  $handler->display->display_options['fields']['changed']['date_format'] = 'long';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'long';
  /* Field: Content: Дата выдачи устройства */
  $handler->display->display_options['fields']['field_granting_date']['id'] = 'field_granting_date';
  $handler->display->display_options['fields']['field_granting_date']['table'] = 'field_data_field_granting_date';
  $handler->display->display_options['fields']['field_granting_date']['field'] = 'field_granting_date';
  $handler->display->display_options['fields']['field_granting_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
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
  $handler->display->display_options['path'] = 'admin/devices';
  $export['devices'] = $view;

  $view = new view();
  $view->name = 'users';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Users';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Сотрудники';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access user profiles';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'uid' => 'uid',
    'gravatar_image' => 'gravatar_image',
    'name' => 'name',
    'mail' => 'mail',
    'field_department' => 'field_department',
    'field_rfid_tags' => 'field_rfid_tags',
    'status' => 'status',
    'rid' => 'rid',
    'created' => 'created',
    'login' => 'login',
    'edit_node' => 'edit_node',
    'activate_user' => 'activate_user',
    'block_user' => 'block_user',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'uid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'gravatar_image' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'mail' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_department' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_rfid_tags' => array(
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
    'rid' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'login' => array(
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
    'activate_user' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'block_user' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  /* Field: somi: Gravatar Image */
  $handler->display->display_options['fields']['gravatar_image']['id'] = 'gravatar_image';
  $handler->display->display_options['fields']['gravatar_image']['table'] = 'users';
  $handler->display->display_options['fields']['gravatar_image']['field'] = 'gravatar_image';
  $handler->display->display_options['fields']['gravatar_image']['label'] = 'Изображение';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'Имя';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['label'] = 'Электронная почта';
  /* Field: User: rfid_tags */
  $handler->display->display_options['fields']['field_rfid_tags']['id'] = 'field_rfid_tags';
  $handler->display->display_options['fields']['field_rfid_tags']['table'] = 'field_data_field_rfid_tags';
  $handler->display->display_options['fields']['field_rfid_tags']['field'] = 'field_rfid_tags';
  $handler->display->display_options['fields']['field_rfid_tags']['label'] = 'Устройства';
  $handler->display->display_options['fields']['field_rfid_tags']['type'] = 'somi_devices';
  $handler->display->display_options['fields']['field_rfid_tags']['settings'] = array(
    'view_mode' => 'teaser',
    'links' => 1,
  );
  $handler->display->display_options['fields']['field_rfid_tags']['delta_offset'] = '0';
  /* Field: User: Active */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'users';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Статус';
  $handler->display->display_options['fields']['status']['type'] = 'unicode-yes-no';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: User: Roles */
  $handler->display->display_options['fields']['rid']['id'] = 'rid';
  $handler->display->display_options['fields']['rid']['table'] = 'users_roles';
  $handler->display->display_options['fields']['rid']['field'] = 'rid';
  $handler->display->display_options['fields']['rid']['label'] = 'Роль';
  /* Field: User: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'users';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Дата создания';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: User: Last login */
  $handler->display->display_options['fields']['login']['id'] = 'login';
  $handler->display->display_options['fields']['login']['table'] = 'users';
  $handler->display->display_options['fields']['login']['field'] = 'login';
  $handler->display->display_options['fields']['login']['label'] = 'Дата последнего посещения';
  $handler->display->display_options['fields']['login']['date_format'] = 'long';
  $handler->display->display_options['fields']['login']['second_date_format'] = 'long';
  /* Field: User: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'users';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Изменить';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['text'] = 'изменить';
  /* Field: User: Activate link */
  $handler->display->display_options['fields']['activate_user']['id'] = 'activate_user';
  $handler->display->display_options['fields']['activate_user']['table'] = 'users';
  $handler->display->display_options['fields']['activate_user']['field'] = 'activate_user';
  $handler->display->display_options['fields']['activate_user']['label'] = 'Активировать';
  $handler->display->display_options['fields']['activate_user']['text'] = 'активировать';
  /* Field: User: Block link */
  $handler->display->display_options['fields']['block_user']['id'] = 'block_user';
  $handler->display->display_options['fields']['block_user']['table'] = 'users';
  $handler->display->display_options['fields']['block_user']['field'] = 'block_user';
  $handler->display->display_options['fields']['block_user']['label'] = 'Заблокировать';
  $handler->display->display_options['fields']['block_user']['text'] = 'заблокировать';
  /* Sort criterion: User: Created date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'users';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Имя';
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

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'users');

  /* Display: users */
  $handler = $view->new_display('page', 'users', 'users_admin');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  /* Field: somi: Gravatar Image */
  $handler->display->display_options['fields']['gravatar_image']['id'] = 'gravatar_image';
  $handler->display->display_options['fields']['gravatar_image']['table'] = 'users';
  $handler->display->display_options['fields']['gravatar_image']['field'] = 'gravatar_image';
  $handler->display->display_options['fields']['gravatar_image']['label'] = 'Изображение';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'Имя';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['label'] = 'Электронная почта';
  /* Field: User: Department */
  $handler->display->display_options['fields']['field_department']['id'] = 'field_department';
  $handler->display->display_options['fields']['field_department']['table'] = 'field_data_field_department';
  $handler->display->display_options['fields']['field_department']['field'] = 'field_department';
  $handler->display->display_options['fields']['field_department']['label'] = 'Департамент';
  $handler->display->display_options['fields']['field_department']['type'] = 'entityreference_entity_view';
  $handler->display->display_options['fields']['field_department']['settings'] = array(
    'view_mode' => 'icon',
    'links' => 1,
  );
  /* Field: User: rfid_tags */
  $handler->display->display_options['fields']['field_rfid_tags']['id'] = 'field_rfid_tags';
  $handler->display->display_options['fields']['field_rfid_tags']['table'] = 'field_data_field_rfid_tags';
  $handler->display->display_options['fields']['field_rfid_tags']['field'] = 'field_rfid_tags';
  $handler->display->display_options['fields']['field_rfid_tags']['label'] = 'Устройства';
  $handler->display->display_options['fields']['field_rfid_tags']['type'] = 'somi_devices';
  $handler->display->display_options['fields']['field_rfid_tags']['settings'] = array(
    'view_mode' => 'teaser',
    'links' => 1,
  );
  $handler->display->display_options['fields']['field_rfid_tags']['delta_offset'] = '0';
  /* Field: User: Active */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'users';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Статус';
  $handler->display->display_options['fields']['status']['type'] = 'unicode-yes-no';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: User: Roles */
  $handler->display->display_options['fields']['rid']['id'] = 'rid';
  $handler->display->display_options['fields']['rid']['table'] = 'users_roles';
  $handler->display->display_options['fields']['rid']['field'] = 'rid';
  $handler->display->display_options['fields']['rid']['label'] = 'Роль';
  /* Field: User: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'users';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Дата создания';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: User: Last login */
  $handler->display->display_options['fields']['login']['id'] = 'login';
  $handler->display->display_options['fields']['login']['table'] = 'users';
  $handler->display->display_options['fields']['login']['field'] = 'login';
  $handler->display->display_options['fields']['login']['label'] = 'Дата последнего посещения';
  $handler->display->display_options['fields']['login']['date_format'] = 'long';
  $handler->display->display_options['fields']['login']['second_date_format'] = 'long';
  /* Field: User: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'users';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Изменить';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['text'] = 'изменить';
  /* Field: User: Activate link */
  $handler->display->display_options['fields']['activate_user']['id'] = 'activate_user';
  $handler->display->display_options['fields']['activate_user']['table'] = 'users';
  $handler->display->display_options['fields']['activate_user']['field'] = 'activate_user';
  $handler->display->display_options['fields']['activate_user']['label'] = 'Активировать';
  $handler->display->display_options['fields']['activate_user']['text'] = 'активировать';
  /* Field: User: Block link */
  $handler->display->display_options['fields']['block_user']['id'] = 'block_user';
  $handler->display->display_options['fields']['block_user']['table'] = 'users';
  $handler->display->display_options['fields']['block_user']['field'] = 'block_user';
  $handler->display->display_options['fields']['block_user']['label'] = 'Заблокировать';
  $handler->display->display_options['fields']['block_user']['text'] = 'заблокировать';
  $handler->display->display_options['path'] = 'admin/users';

  /* Display: Crystalls */
  $handler = $view->new_display('page', 'Crystalls', 'crystalls');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Счета';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  /* Field: somi: Gravatar Image */
  $handler->display->display_options['fields']['gravatar_image']['id'] = 'gravatar_image';
  $handler->display->display_options['fields']['gravatar_image']['table'] = 'users';
  $handler->display->display_options['fields']['gravatar_image']['field'] = 'gravatar_image';
  $handler->display->display_options['fields']['gravatar_image']['label'] = 'Image';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'user/[uid]/crystalls';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Field: User: Roles */
  $handler->display->display_options['fields']['rid']['id'] = 'rid';
  $handler->display->display_options['fields']['rid']['table'] = 'users_roles';
  $handler->display->display_options['fields']['rid']['field'] = 'rid';
  /* Field: somi: Crystalls Debet Count */
  $handler->display->display_options['fields']['crystalls_debet']['id'] = 'crystalls_debet';
  $handler->display->display_options['fields']['crystalls_debet']['table'] = 'users';
  $handler->display->display_options['fields']['crystalls_debet']['field'] = 'crystalls_debet';
  $handler->display->display_options['fields']['crystalls_debet']['label'] = 'Кристаллы (I20)';
  /* Field: somi: Crystalls Count */
  $handler->display->display_options['fields']['crystalls']['id'] = 'crystalls';
  $handler->display->display_options['fields']['crystalls']['table'] = 'users';
  $handler->display->display_options['fields']['crystalls']['field'] = 'crystalls';
  $handler->display->display_options['fields']['crystalls']['label'] = 'Crystalls';
  $handler->display->display_options['fields']['crystalls']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'crystalls';

  /* Display: Accounts Admin */
  $handler = $view->new_display('page', 'Accounts Admin', 'accounts');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Счета';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  /* Field: somi: Gravatar Image */
  $handler->display->display_options['fields']['gravatar_image']['id'] = 'gravatar_image';
  $handler->display->display_options['fields']['gravatar_image']['table'] = 'users';
  $handler->display->display_options['fields']['gravatar_image']['field'] = 'gravatar_image';
  $handler->display->display_options['fields']['gravatar_image']['label'] = 'Изображение';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'Имя';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'admin/user/[uid]/account';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Field: User: Department */
  $handler->display->display_options['fields']['field_department']['id'] = 'field_department';
  $handler->display->display_options['fields']['field_department']['table'] = 'field_data_field_department';
  $handler->display->display_options['fields']['field_department']['field'] = 'field_department';
  $handler->display->display_options['fields']['field_department']['label'] = 'Департамент';
  $handler->display->display_options['fields']['field_department']['type'] = 'entityreference_entity_view';
  $handler->display->display_options['fields']['field_department']['settings'] = array(
    'view_mode' => 'icon',
    'links' => 1,
  );
  /* Field: User: Roles */
  $handler->display->display_options['fields']['rid']['id'] = 'rid';
  $handler->display->display_options['fields']['rid']['table'] = 'users_roles';
  $handler->display->display_options['fields']['rid']['field'] = 'rid';
  $handler->display->display_options['fields']['rid']['label'] = 'Роль';
  $handler->display->display_options['fields']['rid']['type'] = 'ol';
  $handler->display->display_options['path'] = 'admin/content/accounts';
  $export['users'] = $view;

  return $export;
}
