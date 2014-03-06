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
  public function modal_elements($settings) {
    // Get the view name
    $target_view = explode('|', $settings['view']);
    $view = views_get_view($target_view[0]);
    $view->set_display($target_view[1]);
    $view->display_handler->set_option('use_ajax', TRUE);

    // Generate the html for the view.
    $output = $view->preview();

    $elements = array();
    $elements['view'] = array(
      '#type' => 'markup',
      '#markup' => $output,
      '#attached' => array(
        'js' => array(
          drupal_get_path('module', 'ermw_view') . '/plugins/ermw_modal/view.js',
        ),
      )
    );

    // Element that allows to chose the position of the added items.
    // See method merge_rows() for how this is handled.
    $options = array(
      'bottom' => 'Add to the bottom',
      'top' => 'Add to the top',
    );
    $elements['optposition'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#weight' => 10,
      '#name' => array('entityreference_modal_widget_options'),
    );

    return $elements;
  }

  public function options_form($settings) {
    $form = array();

    // Get a list of all views that contain a "Entityreference View Widget" display.
    $options = array();
    $displays = $this->applicable_views();
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
    foreach ($post['entity_ids'] as $entity_id) {
      $entity_ids[] = $entity_id;
    }
    $entity_ids = array_unique($entity_ids);

    return $entity_ids;
  }

  /**
   * Find the views that have a display with entityreference_modal_widget that
   * could be used as entityreference view input.
   */
  private function applicable_views() {
    $result = array();
    $views = views_get_all_views();
    foreach ($views as $view) {
      foreach (array_keys($view->display) as $id) {
        $v = $view->clone_view();
        if ($v->set_display($id) && $v->display_handler->get_option('enabled')) {
          $view_fields = $v->display_handler->get_option('fields');
          if (isset($view_fields['ermw_view_checkbox'])) {
            $result[] = array($v, $id);
          }
        }
      }
    }
    return $result;
  }

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
  public function merge_rows($old_rows, $new_rows, $post) {
    // Merge the two lists depending on the option to prepend or append.
    switch ((string)$post['entityreference_modal_widget_options']) {
      case 'top':
        $rows = array_merge($new_rows, $old_rows);
        break;
      default:
        // By default new items go to the bottom of the list.
        $rows = array_merge($old_rows, $new_rows);
    }

    return $rows;
  }

  /**
   * Returns the text used in the add more items.
   *
   * This is optional. By default 'Add items' is used.
   */
  public function add_items_text() {
    return t('Add items using a view');
  }
}
