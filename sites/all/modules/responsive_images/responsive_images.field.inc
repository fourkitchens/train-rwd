<?php

/**
 * @file
 *
 * Implements a Responsive Images field, similar to the core image field
 */

/**
 * Implements hook_field_formatter_info().
 */
function responsive_images_field_formatter_info() {
  return array(
    'responsive_image' => array(
      'label' => 'Responsive image',
      'description' => t('A responsive image'),
      'field types' => array('image'),
      'settings' => array('responsive_images_set' => '', 'image_link' => ''),
    ),
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 *
 * Based on image_field_formatter_settings_form, but with responsive images set instead
 */
function responsive_images_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $responsive_image_sets = responsive_images_set_load_all_options();
  $element['responsive_images_set'] = array(
    '#title' => t('Responsive images set'),
    '#type' => 'select',
    '#default_value' => $settings['responsive_images_set'],
    '#options' => $responsive_image_sets,
  );

  $link_types = array(
    'content' => t('Content'),
    'file' => t('File'),
  );
  $element['image_link'] = array(
    '#title' => t('Link image to'),
    '#type' => 'select',
    '#default_value' => $settings['image_link'],
    '#empty_option' => t('Nothing'),
    '#options' => $link_types,
  );

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 *
 * Based on image_field_formatter_settings_form, but with responsive images set instead
 */
function responsive_images_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = array();
  $responsive_image_sets = responsive_images_set_load_all_options();
  if (isset($responsive_image_sets[$settings['responsive_images_set']])) {
    $summary[] = $responsive_image_sets[$settings['responsive_images_set']];
  }
  else {
    $summary[] = t('No responsive images set selected');
  }


  $link_types = array(
    'content' => t('Linked to content'),
    'file' => t('Linked to file'),
  );
  // Display this setting only if image is linked.
  if (isset($link_types[$settings['image_link']])) {
    $summary[] = $link_types[$settings['image_link']];
  }

  return implode('<br />', $summary);
}

/**
 * Implements hook_field_formatter_view().
 *
 * Based on image_field_formatter_settings_form, but with responsive images set instead
 */
function responsive_images_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();

  // Check if the formatter involves a link.
  if ($display['settings']['image_link'] == 'content') {
    $uri = entity_uri($entity_type, $entity);
  }
  elseif ($display['settings']['image_link'] == 'file') {
    $link_file = TRUE;
  }

  foreach ($items as $delta => $item) {
    if (isset($link_file)) {
      $uri = array(
        'path' => file_create_url($item['uri']),
        'options' => array(),
      );
    }

    $set = responsive_images_set_load($display['settings']['responsive_images_set']);
    $image_style = isset($set->small_style) ? $set->small_style : 'medium';

    /* Workaround to fix broken images on first load
     * @TODO: find out if there's a better way. This will only be run the first time,
     * when the small_style & large_style image style files aren't rendered yet,
     * so only the content creator could feel the impact of 2 extra HTTP requests.
     * Still, this should be improved if possible in any way.
     */
    $small_style_url = image_style_url($set->small_style, $item['uri']);
    $small_style_path = image_style_path($set->small_style, $item['uri']);
    $large_style_url = image_style_url($set->large_style, $item['uri']);
    $large_style_path = image_style_path($set->large_style, $item['uri']);
    if (!file_exists($small_style_path)) {
      drupal_http_request($small_style_url);
    }
    if (!file_exists($large_style_path)) {
      drupal_http_request($large_style_url);
    }
    /* End workaround */


    $element[$delta] = array(
      '#theme' => 'responsive_images_formatter',
      '#item' => $item,
      '#image_style' => $image_style,
      '#responsive_images_set' => $set,
      '#path' => isset($uri) ? $uri : '',
    );
  }

  return $element;
}