<?php

/**
 * Provides the checkbox field to tick the view rows and set them as field values.
 */
class ermw_view_handler_field_checkbox extends views_handler_field {
  var $revision = FALSE;

  function render($values) {
    // search_api has the entity id in entity property
    if ($this->view->base_field == 'search_api_id') {
      $values->{$this->view->base_field} = $values->entity;
    }
    $entity_id = $values->{$this->view->base_field};
    if (empty($entity_id)) {
      return;
    }
    return '<input name="entity_ids[]" type="checkbox" value="' . $entity_id . '" />';
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['ervw'] = array(
      'contains' => array(
        'force_single' => array('default' => FALSE),
      ),
    );
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['ermw'] = array(
      '#type' => 'fieldset',
      '#title' => t('Entity Reference Modal Widget'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['ermw']['force_single'] = array(
      '#type' => 'checkbox',
      '#title' => t('Force single'),
      '#default_value' => $this->options['ervw']['force_single'],
      '#description' => t('Check this box to restrict selection to a single value.'),
    );
  }

  /**
   * Overridden to avoid that views_handler_field invokes query method that
   * invokes query->add_field that is not defined for SearchApiViewsQuery when
   * the handler is used in a search_api_views table.
   */
  function query($use_groupby = FALSE) {
    if ($this->real_field == 'search_api_id') {
      return;
    }
    parent::query();
  }
}
