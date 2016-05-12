<?php
/**
 * @file
 * somi_feature_common.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function somi_feature_common_user_default_roles() {
  $roles = array();

  // Exported role: active.
  $roles['active'] = array(
    'name' => 'active',
    'weight' => 5,
    'machine_name' => '',
  );

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
    'machine_name' => '',
  );

  // Exported role: core.
  $roles['core'] = array(
    'name' => 'core',
    'weight' => 4,
    'machine_name' => '',
  );

  // Exported role: top.
  $roles['top'] = array(
    'name' => 'top',
    'weight' => 3,
    'machine_name' => '',
  );

  return $roles;
}
