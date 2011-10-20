<?php

$plugin = array(
  'schema' => 'responsive_images_set',
  'access' => 'administer image styles',
  'menu' => array(
    'menu prefix' => 'admin/config/media',
    'menu item' => 'responsive_images',
    'menu title' => 'Responsive images',
    'menu description' => 'Define sets of responsive images',
  ),
  'title singular' => t('responsive image set'),
  'title singular proper' => t('Responsive image set'),
  'title plural' => t('responsive image sets'),
  'title plural proper' => t('Responsive image sets'),
  'form' => array(
    'settings' => 'responsive_images_set_ctools_export_ui_form',
    'submit' => 'responsive_images_set_ctools_export_ui_form_submit',
  ),

);

/**
 * Responsive images set form
 */
function responsive_images_set_ctools_export_ui_form(&$form, &$form_state) {
  // unset default CTools name field
  unset($form['info']['name']);
  // get object
  $responsive_images_set = $form_state['item'];
  $image_styles = image_style_options(FALSE);
  $used_styles = responsive_images_get_used_styles($responsive_images_set->small_style);
  $image_style_options = array_diff($image_styles, array_keys($used_styles));

  $form['id'] = array(
    '#type' => 'hidden',
    '#value' => isset($responsive_images_set->id) ? $responsive_images_set->id : NULL,
  );

  // Human-readable set label
  $form['label'] = array(
    '#title' => t('Set label'),
    '#type' => 'textfield',
    '#default_value' => isset($responsive_images_set->label) ? $responsive_images_set->label : '',
    '#description' => t('The human-readable description of this responsive images set'),
    '#required' => TRUE,
  );

  // Machine-readable set name.
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($responsive_images_set->name) ? $responsive_images_set->name : '',
    '#disabled' => FALSE,
    '#machine_name' => array(
      'exists' => 'responsive_images_set_load',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this responsive images set. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['small_style'] = array(
    '#type' => 'select',
    '#title' => t('Small image style'),
    '#description' => t('Select the image style to be used for responsive images in a small width context.'),
    '#required' => TRUE,
    '#multiple' => FALSE,
    '#options' => $image_style_options,
    '#default_value' => isset($responsive_images_set->small_style) ? $responsive_images_set->small_style : NULL,
  );

  $form['large_style'] = array(
    '#type' => 'select',
    '#title' => t('Large image style'),
    '#description' => t('Select the image style to be used for responsive images in a large width context.'),
    '#required' => TRUE,
    '#multiple' => FALSE,
    '#options' => $image_styles,
    '#default_value' => isset($responsive_images_set->large_style) ? $responsive_images_set->large_style : NULL,
  );
  return $form;
}

/**
 * Submit handler
 * Adds a notification to warn user about possible change in .htaccess file
 * * and redirects him/her to the instructions page
 */
function responsive_images_set_ctools_export_ui_form_submit($form, &$form_state) {
  $url = url('admin/config/media/responsive_images/instructions');
  drupal_set_message(t('If you have changed the image styles configuration, make sure to <a href="!url">update your .htaccess file</a> to reflect these changes.', array('!url' => $url)), 'warning');
}