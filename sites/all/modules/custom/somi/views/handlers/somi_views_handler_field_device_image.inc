<?php
/**
 * @file
 * Field handler to present a link node unpublish.
 */
class somi_views_handler_field_device_image extends views_handler_field {

  /**
   * Render
   * @param $values
   * @return mixed
   */
  function render($values) {
    if ($value = $this->get_value($values)) {
      if ($d = node_load(($value))) {
        $w = entity_metadata_wrapper('node', $d);
        $device_view = node_view($d, 'teaser');

        if (!empty($device_view['field_image'])) {
          return drupal_render($device_view['field_image']);
        }

        $type = $w->field_type->value();

        $type_view = taxonomy_term_view($type, 'teaser');
        if (!empty($type_view['field_image'])) {
          return drupal_render($type_view['field_image']);
        }
      }
    }

    return '';
  }
}
