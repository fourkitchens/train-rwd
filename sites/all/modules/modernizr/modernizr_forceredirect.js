
(function($) {
  $(function() {
    Drupal.Modernizr.hooks.cookieSet.forceredirect = function() {
      if (Drupal.settings.modernizrForceredirect) {
        window.location.reload();
      }
    };
  });
})(jQuery);
