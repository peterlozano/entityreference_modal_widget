<?php
/**
 * @file
 * Example plugin which allows you to write the nid list in a textarea.
 */

$plugin = array(
  'label' => t('Nidlist textarea'),
  'handler' => array(
    'class' => 'entityreference_modal_widget_nidlist',
  ),
);

class entityreference_modal_widget_nidlist extends entityreference_modal_widget {
  public function modal_elements($settings) {
    $element = array(
      '#type' => 'textarea',
      '#title' => t('Nid list'),
      '#description' => t('Write a list of nids, one in each line.'),
      '#name' => 'nid_textarea',
    );

    return $element;
  }

  public function get_entity_ids($post) {
    $entity_ids = explode("\n", $post['nid_textarea']);

    return $entity_ids;
  }

  /**
   * Returns the text used in the add more items.
   *
   * This is optional. By default 'Add items' is used.
   */
  public function add_items_text() {
    return t('Add items using a textarea');
  }

  /**
   * Returns extra ajax commands to be executed.
   *
   * See entityreference_modal_widget.js for an example on how to
   * create custom commands.
   *
   * @param $post
   * @return array
   */
  public function closed_commands($post) {
    $commands = array();

    $commands[] = ajax_command_alert(t('Nids added'));

    return $commands;
  }
}

