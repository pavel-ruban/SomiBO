<?php

/**
 * @file
 * Field handler to present a link node unpublish.
 */
class somi_views_handler_field_user_debet_crystalls extends views_handler_field {

  /**
   * Render
   * @param $values
   * @return mixed
   */
  function render($values) {
    if ($value = $this->get_value($values)) {
      $crystalls_count = somi_get_user_crystalls($value, 'crystalls_debet');

      return theme('image_style',
        array(
          'style_name' => 'thumbnail',
          'path' => "crystalls-debet.png",
          'title' => $values->users_name,
          'alt' => $values->users_name,
        )
      ) . '<span class="crystalls-count">' . $crystalls_count . '</span>';
    }
  }
}
