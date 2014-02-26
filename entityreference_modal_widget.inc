<?php

/**
 * @file
 * Code for the abstract class that entityreference_modal_widget modal plugins
 * are derived from.
 */

abstract class entityreference_modal_widget {
  function __construct() { }

  /**
   * Renders the content of the modal dialog.
   *
   * @param $settings
   */
  public function render($settings) { }

  /**
   * Returns a config for for the plugin that will be displayed
   * in the field form.
   *
   * @param $settings
   * @return array
   */
  public function options_form($settings) { return array(); }


  /**
   * Converts the ajax post string into an array of entity_ids.
   *
   * @param $post string
   *  The content of the $_POST received in the ajax request.
   * @return array
   *  List of entity_ids as they will be included in the reference field.
   */
  public function get_entity_ids($post) { return array(); }

}
