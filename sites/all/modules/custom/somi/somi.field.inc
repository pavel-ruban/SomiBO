<?php

/**
 * @file
 */

/**
 * Implements hook_field_formatter_info_alter.
 */
function somi_field_formatter_info() {
  return array(
    'somi_devices' => array(
      'label' => t('SOMI devices'),
      'field types' => array('entityreference'),
    ),
  );
}

/**
 * Implementation of hook_field_formatter_view().
 */
function somi_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $elements = array();

  switch ($display['type']) {
    case 'somi_devices':
      foreach ($items as $delta => $item) {
        if ($node = node_load($item['target_id'])) {
          $device_type = somi_get_device_type_by_nid($node->nid);
          $device_id = $node->title;

          $options = array(
            'html' => TRUE,
            'attributes' => array(
              'class' => array($node->status ? 'green' : 'red', 'device-link'),
            )
          );

          $elements[$delta] = array(
            '#markup' => l("$device_type : $device_id", "/node/{$node->nid}", $options),
          );
        }
      }

      $elements = array_values($elements);
      break;
  }

  return $elements;
}