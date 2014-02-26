<?php
/**
 * @file
 * Implements a View type of entityreference_modal_widget.
 *
 * This plugin mimics the functionality of the entityreference_view_widget
 * using the plugin system of entityreference_modal_widget.
 */

$plugin = array(
  'label' => t('View'),
  'handler' => array(
    'class' => 'entityreference_modal_widget_view',
  ),
);

class entityreference_modal_widget_view extends entityreference_modal_widget {
  public function render($settings) {
    $target_view = explode('|', $settings['view']);
    $view = views_get_view($target_view[0]);
    $view->set_display($target_view[1]);
    $view->display_handler->set_option('use_ajax', TRUE);

    $output = $view->preview();

    return $output;
  }

  public function options_form($settings) {
    $form = array();

    // Get a list of all views that contain a "Entityreference View Widget" display.
    $options = array();
    $displays = views_get_applicable_views('entityreference view display');
    foreach ($displays as $data) {
      list($view, $display_id) = $data;
      $view_name = !empty($view->human_name) ? $view->human_name : $view->name;
      $options[$view->name . '|' . $display_id] = check_plain($view_name . ' | ' . $view->display_handler->display->display_title);
    }

    $form['view'] = array(
      '#type' => 'select',
      '#title' => t('View'),
      '#description' => t('Specify the View to use for selecting items. Only views that have an "Entityreference View Widget" display are shown.'),
      '#options' => $options,
      '#default_value' => isset($settings['view']) ? $settings['view'] : '',
      '#required' => TRUE,
    );
    $form['pass_argument'] = array(
      '#type' => 'checkbox',
      '#title' => t('Pass selected entity ids to View'),
      '#description' => t('If enabled, the View will get all selected entity ids as the first argument. Useful for excluding already selected items.'),
      '#default_value' => isset($settings['pass_argument']) ? $settings['pass_argument'] : '',
    );
    $form['close_modal'] = array(
      '#type' => 'checkbox',
      '#title' => t('Close modal window after submitting the items'),
      '#description' => t('If enabled, the modal window will close after you had selected the entities from the view and submitted your selection.'),
      '#default_value' => isset($settings['close_modal']) ? $settings['close_modal'] : '',
    );

    return $form;
  }

  public function get_entity_ids($post) {
    $entity_ids = array();
    foreach ($post_entity_ids as $entity_id) {
      $entity_ids[] = $entity_id;
    }
    $entity_ids = array_unique($entity_ids);

    return $entity_ids;
  }
}
