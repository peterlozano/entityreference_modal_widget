(function($) {
  /**
   * Provide an ajax command that rebuilds the tabledrag in a table that
   * has rows added via ajax.
   *
   * See: entityreference_modal_widget_ajax().
   */
  Drupal.ajax.prototype.commands.ermw_redrag = function (ajax, response, status) {
    table_id = response.table_id;
    $('#' + table_id + ' tbody tr').each(function() {
      var el = $(this);
      Drupal.tableDrag[table_id].makeDraggable(el.get(0));
      el.find('td:last').addClass('tabledrag-hide');
      if ($.cookie('Drupal.tableDrag.showWeight') == 1) {
        el.find('.tabledrag-handle').hide();
      }
      else {
        el.find('td:last').hide();
      }
    });
  };
})(jQuery);