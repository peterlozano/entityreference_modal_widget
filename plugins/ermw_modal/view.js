(function($) {
  Drupal.behaviors.entityreferenceModalWidget = {
    attach: function(context, settings) {
      $('.ervw-add-items').bind('click',
        function() {
          if (typeof Drupal.settings['views'] != 'undefined') {
            Drupal.settings['views']['ajaxViews'] = null;
          }
        }
      );
      var checkboxes = '#modal-content input[name="entity_ids[]"]';
      $('#entityreference-modal-widget-select-all').unbind('click').text('Select all').data('unselect', 0).click(function(){
        if ($(this).data('unselect')) {
          $(checkboxes).removeAttr('checked');
          $(this).data('unselect', 0).text('Select all');
        }
        else {
          $(checkboxes).attr('checked', 'checked');
          $(this).data('unselect', 1).text('Unselect all');
        }
        return false;
      });
    }
  }
})(jQuery);
