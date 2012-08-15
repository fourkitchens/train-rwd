/**
 * @file
 *   Main JavaScript file for Dismiss module
 */

(function ($) {

  Drupal.behaviors.dismiss = {
    attach: function(context) {

      // Append the Dismiss button to each message box.
      $('.messages').each(function(){
        $(this).prepend('<a class="dismiss">X</a>');
      });

      // When the Dismiss button is clicked hide this set of messages.
      $('.dismiss').click(function(){
        $(this).parent().hide('fast');
      });

    }
  }

})(jQuery);
