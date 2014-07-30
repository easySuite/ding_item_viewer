<?php
/**
 * @file
 * ding_item_viewer_default_layout.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ding_item_viewer_default_layout_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'more_info'
  $field_bases['more_info'] = array(
    'active' => 1,
    'cardinality' => 1,
    'default_widget' => 'hidden',
    'deleted' => 0,
    'entity_types' => array(
      0 => 'ting_object',
    ),
    'field_name' => 'more_info',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ding_item_viewer',
    'no_ui' => TRUE,
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_object_more_info',
  );

  return $field_bases;
}
