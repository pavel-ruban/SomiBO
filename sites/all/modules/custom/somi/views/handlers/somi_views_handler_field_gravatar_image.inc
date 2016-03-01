<?php
/**
 * @file
 * Field handler to present a link node unpublish.
 */
class somi_views_handler_field_gravatar_image extends views_handler_field {

  /**
   * Render
   * @param $values
   * @return mixed
   */
  function render($values) {
    if ($value = $this->get_value($values)) {
      $mail_hash = md5($value);

      return $image = theme(
        'image',
        array(
          'path' => "http://www.gravatar.com/avatar/$mail_hash",
          'title' => $values->users_name,
          'alt' => $values->users_name,
        )
      );
    }

    return '';
  }
}
