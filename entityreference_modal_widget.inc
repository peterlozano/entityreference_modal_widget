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
   * @returns string
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

  /**
   * Returns extra ajax commands to be executed.
   *
   * See entityreference_modal_widget.js for an example on how to
   * create custom commands.
   *
   * @param $post
   * @return array
   */
  public function closed_commands($post) { return array(); }

  /**
   * Returns the text used in the add more items.
   *
   * This is optional. By default 'Add items' is used.
   *
   * public function add_items_text() {
   *  return t('Add items');
   * }
   */

  /**
   * This function merges the existing rows with the new selected ones.
   *
   * If this method doesn't exist the default method is used.
   *
   * By default, new selected nodes are appended.
   *
   * @param $old_rows
   * @param $new_rows
   * @param $post
   *  The $_POST content received from the modal dialog form.
   * @return array
   */
  // public function merge_rows($old_rows, $new_rows, $post) { };
}
