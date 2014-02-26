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
  public function render($settings) {
    $element = array(
      '#type' => 'textarea',
      '#title' => t('Nid list'),
      '#description' => t('Write a list of nids, one in each line.'),
      '#attached' => array(
        'js' => array(drupal_get_path('module', 'entityreference_modal_widget') . '/plugins/ermw_modal/nidlist.js'),
      )
    );

    return drupal_render($element);
  }

  public function get_entity_ids($post) {
    $entity_ids = explode("\n", $post['textarea']);

    return $entity_ids;
  }
}

