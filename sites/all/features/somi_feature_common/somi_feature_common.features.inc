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
