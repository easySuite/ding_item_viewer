<?php
/**
 * @file
 * Ctools plugin definition file.
 */

$plugin = array(
  'title' => t('Ding item viewer'),
  'category' => t('Ding!'),
  'description' => t('Display ting objects in a carousel view.'),
  'single' => TRUE,
  'content_types' => 'ding_item_viewer_content_type',
  'render callback' => 'ding_item_viewer_content_type_render',
  'edit form' => 'ding_item_viewer_content_type_edit_form',
);


/**
 * Return the pane contents.
 */
function ding_item_viewer_content_type_render($subtype, $conf, $panel_args, $context) {
  $searches = $conf['searches'];
  unset($conf['searches']);

  $hash_string = '';
  foreach ($searches as $search) {
    $hash_string .= trim($search['query']);
  }
  $ding_item_viewer_hash = md5($hash_string);

  $ding_item_viewer_conf = array(
    $ding_item_viewer_hash => array(
      'hash' => $ding_item_viewer_hash,
      'searches' => $searches,
      'config' => $conf['ding_item_viewer_settings'],
    ),
  );

  $cache_id = DING_ITEM_VIEWER_CONF_CACHE_ID . $ding_item_viewer_hash;
  cache_set($cache_id, $ding_item_viewer_conf, 'cache');

  $block = new stdClass();

  // Load required JS and CSS files.
  drupal_add_library('system', 'drupal.ajax');
  drupal_add_css(DING_ITEM_VIEWER_MODULE_PATH . '/css/ding_item_viewer.css');
  drupal_add_js(DING_ITEM_VIEWER_MODULE_PATH . '/js/ding_item_viewer.js');

  if (module_exists('ding_availability')) {
    drupal_add_js(drupal_get_path('module', 'ding_availability') . '/js/ding_availability.js');
  }

  $js_setting = array(
    'ding_item_viewer' => array(
      'visible_items' => 6,
      'big_item_positon' => 3,
      'interval' => $conf['ding_item_viewer_settings']['ding_item_viewer_interval'],
    ),
  );
  drupal_add_js($js_setting, 'setting');

  $block->content = theme('ding_item_viewer_container', array('hash' => $ding_item_viewer_hash));

  return $block;
}
