<?php
/**
 * @file
 * somi_feature_vocabularies_content_types.features.inc
 */

/**
 * Implements hook_default_config_pages_type().
 */
function somi_feature_vocabularies_content_types_default_config_pages_type() {
  $items = array();
  $items['somi_settings'] = entity_import('config_pages_type', '{
    "type" : "somi_settings",
    "label" : "Somi Settings",
    "weight" : "0",
    "data" : {
      "menu" : { "path" : "admin\\/somi\\/settings", "type" : "6" },
      "context" : { "group" : {
          "config_pages:language" : 0,
          "config_pages:host" : 0,
          "config_pages:domain" : 0
        }
      }
    },
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_ctools_plugin_api().
 */
function somi_feature_vocabularies_content_types_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function somi_feature_vocabularies_content_types_node_info() {
  $items = array(
    'article' => array(
      'name' => t('Article'),
      'base' => 'node_content',
      'description' => t('Use <em>articles</em> for time-sensitive content like news, press releases or blog posts.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'page' => array(
      'name' => t('Basic page'),
      'base' => 'node_content',
      'description' => t('Use <em>basic pages</em> for your static content, such as an \'About us\' page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'rfid_tag' => array(
      'name' => t('rfid_tag'),
      'base' => 'node_content',
      'description' => t('This is device that provides rfid tag for a person'),
      'has_title' => '1',
      'title_label' => t('RFID TAG ID'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
