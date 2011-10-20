Description
===========
This module integrates the Responsive Images library created by Filament Group:
https://github.com/filamentgroup/Responsive-Images/tree/cookie-driven

The purpose of this library is to load images in different sizes based upon
the resolution of the browser loading the page. This allows for mobile-optimized images.

This module provides a "Responsive Images" image field formatter for which you can select
one of the configured responsive images sets.
A responsive images set consists of both a small (mobile-optimized) image style as well as a large (for normal screens) image style.
These sets can be configured and exported through a configuration UI (requires CTools).

Important: this module only works with the cookie-driven branch of the Responsive Images library!

Dependencies
=============
- CTools (http://drupal.org/project/ctools)
- Libraries API (http://drupal.org/project/libraries) (optional)

Installation
=============
1/ Download the Responsive Images library (https://github.com/filamentgroup/Responsive-Images/tree/cookie-driven) to your sites/all/libraries folder
   Make sure to put it in a folder named "responsive_images".
   The folder structure should be like sites/[all or sitename]/libraries/responsive_images/rwd-images/
   Optionally you can use the Libraries API module (http://drupal.org/project/libraries) to install the library in another location and have it auto detected
   Note: You don't need to follow installation instructions provided by the Responsive Images library itself. This will be handled in step 3.
2/ Enable the Responsive Images module
3/ Optionally, create new image styles (admin/config/media/image-styles/add) for small & large screens.
4/ Configure the module at admin/config/media/responsive_images, by defining responsive image sets.
5/ After saving, go to admin/config/media/responsive_images/instructions, where you find instructions on the code that needs to be added to your Drupal .htaccess file
6/ Set the formatter for your images to "Responsive Image" (via 'Manage Displays' on your content type, field settings in Views, ...)

NOTE:
If you add or change responsive image sets, your .htaccess file will have to be updated accordingly!
Demo
=====
A live demo can be viewed at http://svendecabooter.be/drupal-responsive-images
Make sure to test this page with a mobile device as well to see it in action.

Acknowledgements
================
This module has been created by Pure Sign (http://puresign.be).
Author: Sven Decabooter (http://drupal.org/user/35369)
Pure Sign can be contacted for paid customizations of this module as well as Drupal consulting and development.
