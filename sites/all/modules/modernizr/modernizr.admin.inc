<?php

/**
 * Form callback for 'admin/config/development/modernizr'.
 */
function modernizr_admin_form() {
  $f = array();
  
  $serverside = variable_get('modernizr_serverside', MODERNIZR_SERVER_SIDE_DEFAULT);
  
  $f['modernizr_serverside'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable server side support'),
    '#description' => $serverside > 1 ?
      t('Serverside can\'t be disabled, ' .
        'because one or more module requires it to be turned on.'):
      t('Note, that by enabling this option, a big cookie will be made, ' .
        'which can cause problems on certain browsers.'),
    '#disabled' => $serverside > 1,
    '#default_value' => $serverside,
  );
  
  return system_settings_form($f);
}


/**
 * Generates new Modernizr URL for admin interface
 */
function modernizr_generate_url() {
  $tests = modernizr_api_list(TRUE);
  $output = '';

  $link = 'http://www.modernizr.com/download/#-';
  $list = '<h2>Current Modernizr Tests</h2>';
  $list .= '<p>Your other Drupal modues and themes have registered the following Modernizr tests:</p><ul>';

  $prevModule = '';
  foreach ($tests as $test) {
    // print out module name as heading
    if ($prevModule != $test['module']) {
      $list .= '</ul><h3>'. $test['module'] .'</h3><ul>';
    }
    // Add link frag
    $link .= $test['test'] .'-';
    // Add admin output
    $list .= '<li>'. $test['test'] .'</li>';
    // TODO: $list .= $test['desc'];

    $prevModule = $test['module'];
  }

  // finish list(s)
  $list .= '</ul>';

  // truncate last hyphen
  $link = substr($link, 0, -1);

  // Assemble output
  $output .= $list;
  $output .= '<br><p><a style="font-size: 2em; " href="'. $link .'" target="_blank">Download your Modernizr production build</a>.<br> '.
    'Move it to sites/all/libraries or equivalent and <a href="/admin/config/development/performance">clear your cache</a>.</p>';

  return $output;
}
