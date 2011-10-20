<?php

/**
 * @file
 * Serves administrative pages for the Responder module
 */

/**
 * Responder administration settings
 */
function responder_admin() {
  $form = array();

  $form['responder_active'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Activate Responder'),
    '#default_value'  => variable_get('responder_active', RESPONDER_ACTIVE_DEFAULT),
  );

  $form['responder_mq'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('@media query settings'),
    '#collapsible'  => TRUE,
    '#collapsed'    => !variable_get('responder_active', RESPONDER_ACTIVE_DEFAULT), // var is inversed: open if TRUE, collapsed if FALSE
  );
  $form['responder_mq']['responder_mq_property'] = array(
    '#type'           => 'select',
    '#title'          => t('Property'),
    '#description'    => t("Select the property you want to test for. <em>&mdash; (<strong>min-width</strong>: 720px)</em>"),
    '#default_value'  => variable_get('responder_mq_property', RESPONDER_MQ_PROPERTY_DEFAULT),
    '#options'        => array(
      'min-width' => 'min-width',
      'max-width' => 'max-width',
    ),
    '#required'       => TRUE,
  );
  $form['responder_mq']['responder_mq_value'] = array(
    '#type'             => 'textfield',
    '#title'            => t('Value'),
    '#description'      => t("Enter the value for your property. <em>&mdash; (min-width: <strong>720</strong>px)</em>"),
    '#default_value'    => variable_get('responder_mq_value', RESPONDER_MQ_VALUE_DEFAULT),
    '#size'             => 2,
    '#maxlength'        => 5,
    '#element_validate' => array('_element_validate_integer_positive'),
    '#required'         => TRUE,
  );
  $form['responder_mq']['responder_mq_units'] = array(
    '#type'           => 'select',
    '#title'          => t('Units'),
    '#description'    => t("Enter the units for your value. <em>&mdash; (min-width: 720<strong>px</strong>)</em>"),
    '#default_value'  => variable_get('responder_mq_units', RESPONDER_MQ_UNITS_DEFAULT),
    '#options'        => array(
      'px' => 'pixels (px)',
      'cm' => 'centimeters (cm)',
      'mm' => 'millimeters (mm)',
      'em' => 'current font size (em)',
      'ex' => 'x-height (ex)',
      'pt' => 'points (pt)',
      'pc' => 'picas (pc)',
      ),
    '#required'       => TRUE,
  );

  return system_settings_form($form);
}
