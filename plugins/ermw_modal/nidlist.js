(function($) {
  Drupal.behaviors.entityreferenceModalWidget = {
    attach: function(context, settings) {
      $('#entityreference-modal-widget-modal-submit .button').click(function(){
        var settings_selector = '#' + $('#entityreference-modal-widget-settings-selector').val();
        var widget_settings = JSON.parse($(settings_selector).val());

        // Generate a list of entity_ids.
        // If the only information you have to transmit to the node form is a list of nids
        // then this is the only code that you have to modify.
        entity_ids = 'textarea=' + $('#modalContent textarea').val();

        // Generate the ajax callback query string.
        var query_string = entity_ids +
          '&element=' + widget_settings.element +
          '&langcode=' + widget_settings.langcode +
          '&target_type=' + widget_settings.target_type +
          '&cardinality=' + widget_settings.cardinality +
          '&field_name=' + widget_settings.field_name +
          '&entity_type=' + widget_settings.entity_type +
          '&bundle=' + widget_settings.bundle;

        $.ajax({
          url: Drupal.settings.basePath + '?q=entityreference_modal_widget/ajax',
          type: 'POST',
          dataType: 'html',
          data: query_string,
          success: function(data) {
            // The new html for the reference field will be rendered in the php callback.
            // Place received html into the widget table.
            data && $('#' + widget_settings.table_id + ' tbody').html(data);

            $('#' + widget_settings.table_id + ' tbody tr').each(function(){
              var el = $(this);
              if (widget_settings.cardinality !== '1') {
                Drupal.tableDrag[widget_settings.table_id].makeDraggable(el.get(0));
                el.find('td:last').addClass('tabledrag-hide');
                if ($.cookie('Drupal.tableDrag.showWeight') == 1) {
                  el.find('.tabledrag-handle').hide();
                }
                else {
                  el.find('td:last').hide();
                }
              }
            });

            // Close the modal dialog.
            widget_settings.close_modal && Drupal.CTools.Modal.dismiss();
          }
        });
      });
    }
  };

})(jQuery);
