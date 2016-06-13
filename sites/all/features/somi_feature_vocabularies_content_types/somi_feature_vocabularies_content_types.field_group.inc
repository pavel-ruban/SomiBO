<?php
/**
 * @file
 * somi_feature_vocabularies_content_types.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function somi_feature_vocabularies_content_types_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_cases_declensions|field_collection_item|field_currencies|form';
  $field_group->group_name = 'group_cases_declensions';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_currencies';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_translations';
  $field_group->data = array(
    'label' => 'Падежи и склонения',
    'weight' => '6',
    'children' => array(
      0 => 'field_cases_declensions',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Падежи и склонения',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_cases_declensions|field_collection_item|field_currencies|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_currencies|config_pages|somi_settings|form';
  $field_group->group_name = 'group_currencies';
  $field_group->entity_type = 'config_pages';
  $field_group->bundle = 'somi_settings';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Валюты',
    'weight' => '1',
    'children' => array(
      0 => 'field_currencies',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Валюты',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-currencies field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_currencies|config_pages|somi_settings|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_limits|config_pages|somi_settings|form';
  $field_group->group_name = 'group_limits';
  $field_group->entity_type = 'config_pages';
  $field_group->bundle = 'somi_settings';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Лимиты',
    'weight' => '0',
    'children' => array(
      0 => 'field_limit',
      1 => 'field_cron_accounts',
      2 => 'group_operation_limit',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Лимиты',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-limits field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_limits|config_pages|somi_settings|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_notifications|config_pages|somi_settings|form';
  $field_group->group_name = 'group_notifications';
  $field_group->entity_type = 'config_pages';
  $field_group->bundle = 'somi_settings';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Notifications',
    'weight' => '2',
    'children' => array(
      0 => 'field_notifications',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-notifications field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_notifications|config_pages|somi_settings|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_operation_limit|config_pages|somi_settings|form';
  $field_group->group_name = 'group_operation_limit';
  $field_group->entity_type = 'config_pages';
  $field_group->bundle = 'somi_settings';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_limits';
  $field_group->data = array(
    'label' => 'Лимиты операции',
    'weight' => '4',
    'children' => array(
      0 => 'field_op_limit',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Лимиты операции',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-operation-limit field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_operation_limit|config_pages|somi_settings|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_slack_translates|field_collection_item|field_currencies|form';
  $field_group->group_name = 'group_slack_translates';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_currencies';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_translations';
  $field_group->data = array(
    'label' => 'Переводы Slack\'a',
    'weight' => '7',
    'children' => array(
      0 => 'field_slack_op',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Переводы Slack\'a',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-slack-translates field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_slack_translates|field_collection_item|field_currencies|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_translations|field_collection_item|field_currencies|form';
  $field_group->group_name = 'group_translations';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_currencies';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'translations',
    'weight' => '3',
    'children' => array(
      0 => 'group_cases_declensions',
      1 => 'group_slack_translates',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'translations',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-translations field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_translations|field_collection_item|field_currencies|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Notifications');
  t('translations');
  t('Валюты');
  t('Лимиты');
  t('Лимиты операции');
  t('Падежи и склонения');
  t('Переводы Slack\'a');

  return $field_groups;
}
