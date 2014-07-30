<?php
/**
 * @file
 * ding_item_viewer_default_layout.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ding_item_viewer_default_layout_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'ting_object-ting_object-more_info'
  $field_instances['ting_object-ting_object-more_info'] = array(
    'bundle' => 'ting_object',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'ding_item_viewer_big' => array(
        'label' => 'hidden',
        'module' => 'ding_item_viewer',
        'settings' => array(),
        'type' => 'ting_object_more_info_default',
        'weight' => 7,
      ),
      'ding_item_viewer_small' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 42,
      ),
    ),
    'entity_type' => 'ting_object',
    'field_name' => 'more_info',
    'formatter' => array(
      'type' => 'ting_object_more_info_default',
    ),
    'label' => 'More info',
    'required' => FALSE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => 41,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('More info');

  return $field_instances;
}
