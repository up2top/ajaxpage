/**
 * @file
 * A JavaScript file for the theme.
 *
 * In order for this JavaScript to be loaded on pages, see the instructions in
 * the README.txt next to this file.
 */

// JavaScript should be made compatible with libraries other than jQuery by
// wrapping it with an "anonymous closure". See:
// - https://drupal.org/node/1446420
// - http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth
(function ($, Drupal, window, document) {

  "use strict";

  // To understand behaviors, see https://drupal.org/node/756722#behaviors
  Drupal.behaviors.ajaxPage = {
    attach: function (context, settings) {

      // Watch clicks on ajaxpage menu links
      // Use off() function to avoid multiple ajax-requests
      $(".ajaxpage__ajax").off("click").on("click", ajaxPageRequest);

      function ajaxPageRequest(e) {

        // Prevent default link action
        e.preventDefault();

        // Prepare element settings for ajax request
        var $parentViewsRow = $(this).closest(".views-row"),
            $ajaxPageMenu = $(this).closest(".ajaxpage__menu"),
            href = $(this).attr("href"),
            confirmText = $(this).attr("data-confirm"),
            base = $(this).closest(".ajaxpage__menu").attr("id"),
            element_settings = {
              url: "http://" + window.location.hostname + settings.basePath + settings.pathPrefix + href,
              event: "ajaxPageAction",
              progress: {type: "none"},
              beforeSend: function (xmlhttprequest, options) {

                // Unbind previous ajaxpage action to prevent dublicate AJAX-requests.
                $(".ajaxpage__ajax").unbind("ajaxPageAction");

                // Ask user to confirm selection if menu link contains confirm text
                if (typeof confirmText !== typeof undefined && confirmText !== false) {

                  // If user doesn't confirm selection cancel ajax-request.
                  if (!confirm(confirmText)) {
                    this.ajaxing = false;
                    return false;
                  }
                }

                // Call Drupal parent method 
                Drupal.ajax.prototype.beforeSend.call(this, xmlhttprequest, options);
              }
            };

        // Add unique CSS-class to parent views row
        // to refer to it later from php ajax-commands.
        $parentViewsRow.addClass(base);

        // Create and trigger new AJAX-request.
        Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);
        $(this).trigger("ajaxPageAction");
      };
    }
  };
})(jQuery, Drupal, this, this.document);
