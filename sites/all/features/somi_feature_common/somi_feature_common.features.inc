<?php
/**
 * @file
 * somi_feature_common.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function somi_feature_common_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function somi_feature_common_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function somi_feature_common_image_default_styles() {
  $styles = array();

  // Exported image style: icon.
  $styles['icon'] = array(
    'label' => 'Icon',
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 20,
          'height' => 15,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
