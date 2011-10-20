<?php

/**
 * @file
 * Renders administrative pages for the Responsive Images module
 */

function responsive_images_admin_settings() {
  $form = array();
  $image_styles = image_style_options(FALSE);

  $form['responsive_images_widthBreakPoint'] = array(
    '#type' => 'textfield',
    '#title' => t('widthBreakPoint'),
    '#description' => t('Specify a width breadpoint if you want to use a different one than the 480px default') . '<br />' . t('Leave blank to use the default settings.'),
    '#required' => FALSE,
    '#default_value' => variable_get('responsive_images_widthBreakPoint', ''),
    '#field_suffix' => ' ' . t('pixels'),
    '#size' => 6,
  );

  return system_settings_form($form);
}

/**
 * Instructions page, assisting the user in configuring the .htaccess file
 */
function responsive_images_admin_instructions() {
  $form = array();
  $styles = responsive_images_get_used_styles();

  $form['config_instructions_title'] = array(
    '#type' => 'item',
    '#markup' => '<h2>' . t('Configuration instructions') . '</h2>',
  );

  $library_path = responsive_images_get_library_file();
  if (!file_exists($library_path)) {
    $error = drupal_strtoupper(t('Warning')) . ': ' . t('Library is not correctly installed');
    $error .= '<br />' . t('Please follow the installation instructions in the responsive_images module README.txt file');
    $form['library'] = array(
      '#type' => 'item',
      '#title' => t('Responsive Images library'),
      '#markup' => $error,
    );
  }
  else {
    $form['library'] = array(
      '#type' => 'item',
      '#title' => t('Responsive Images library'),
      '#markup' => t('Library is installed.'),
    );

    $form['instructions'] = array(
      '#type' => 'item',
      '#title' => t('Follow these instructions to correctly update your .htaccess file'),
      '#markup' => 'Put the following code in your .htaccess file right after the "# RewriteBase /" directive.',
    );

    $form['htaccess_file'] = array(
      '#type' => 'fieldset',
      '#title' => t('.htaccess file example'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $suffix_code = <<<SUFFIX
  # Pass all requests not referring directly to files in the filesystem to<br />
  # index.php. Clean URLs are handled in drupal_environment_initialize().<br />
  RewriteCond %{REQUEST_FILENAME} !-f<br />
  RewriteCond %{REQUEST_FILENAME} !-d<br />
  RewriteCond %{REQUEST_URI} !=/favicon.ico<br />
  RewriteRule ^ index.php [L]
SUFFIX;
    $form['htaccess_file']['htaccess_code'] = array(
      '#type' => 'textarea',
      '#required' => FALSE,
      '#rows' => 15,
      '#default_value' => responsive_images_admin_htaccess_code($styles),
      '#prefix' => '# RewriteBase /',
      '#suffix' => $suffix_code,
    );
  }

  return $form;
}

/**
 * Renders the .htaccess code to be used
 */
function responsive_images_admin_htaccess_code($styles) {
  if ($styles) {

    $code = "
      # ----------------------------------------------------------------------
      # Responsive Images
      # ----------------------------------------------------------------------" . PHP_EOL;

    foreach ($styles as $small => $large) {
      $code .= "      RewriteCond %{HTTP_COOKIE} rwdimgsize=large" . PHP_EOL;
      $code .= "      RewriteRule (.*)\/{$small}\/(.*)\.r(\.(jpe?g|png|gif))$ $1/{$large}/$2$3" . PHP_EOL;
    }

    $code .= "
      # remove .r from all requests
      RewriteRule (.*)\.r(\.(jpe?g|png|gif))$ $1$2
      # ----------------------------------------------------------------------
      # END Responsive Images
      # ----------------------------------------------------------------------";
    return $code;

  }
  return FALSE;
}
