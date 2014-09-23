<?php
/**
 * @file
 * ding_item_viewer_default_layout.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_item_viewer_default_layout_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_field_group_info_alter().
 */
function ding_item_viewer_default_layout_field_group_info_alter(&$data) {
  if (isset($data['group_data|ting_object|ting_object|ding_item_viewer_big'])) {
    $data['group_data|ting_object|ting_object|ding_item_viewer_big']->data['children']['0'] = 'ting_abstract';
    $data['group_data|ting_object|ting_object|ding_item_viewer_big']->data['children']['1'] = 'ting_author';
    $data['group_data|ting_object|ting_object|ding_item_viewer_big']->data['children']['2'] = 'ting_subjects';
    $data['group_data|ting_object|ting_object|ding_item_viewer_big']->data['children']['3'] = 'ding_entity_buttons';
    $data['group_data|ting_object|ting_object|ding_item_viewer_big']->data['children']['4'] = 'more_info';
  }
}

/**
 * Implements hook_field_default_field_instances_alter().
 */
function ding_item_viewer_default_layout_field_default_field_instances_alter(&$data) {
  if (isset($data['ting_object-ting_object-ding_entity_buttons'])) {
    $data['ting_object-ting_object-ding_entity_buttons']['display']['ding_item_viewer_big'] = array(
      'label' => 'hidden',
      'module' => 'ding_entity',
      'settings' => array(),
      'type' => 'ding_entity_buttons_ajax',
      'weight' => 6,
    ); /* WAS: '' */
  }
  if (isset($data['ting_object-ting_object-ting_abstract'])) {
    $data['ting_object-ting_object-ting_abstract']['display']['ding_item_viewer_big'] = array(
      'label' => 'hidden',
      'module' => 'ding_item_viewer',
      'settings' => array(
        'trim_length' => 100,
      ),
      'type' => 'ting_abstract_ding_item_viewer',
      'weight' => 3,
    ); /* WAS: '' */
  }
  if (isset($data['ting_object-ting_object-ting_author'])) {
    $data['ting_object-ting_object-ting_author']['display']['ding_item_viewer_big'] = array(
      'label' => 'hidden',
      'module' => 'ding_item_viewer',
      'settings' => array(),
      'type' => 'ting_author_ding_item_viewer',
      'weight' => 4,
    ); /* WAS: '' */
    $data['ting_object-ting_object-ting_author']['display']['ding_item_viewer_small'] = array(
      'label' => 'hidden',
      'module' => 'ding_item_viewer',
      'settings' => array(),
      'type' => 'ting_author_ding_item_viewer',
      'weight' => 2,
    ); /* WAS: '' */
  }
  if (isset($data['ting_object-ting_object-ting_cover'])) {
    $data['ting_object-ting_object-ting_cover']['display']['ding_item_viewer_big'] = array(
      'label' => 'hidden',
      'module' => 'ding_item_viewer',
      'settings' => array(
        'image_style' => 'ding_item_viewer_image_big',
      ),
      'type' => 'ting_cover_ding_item_viewer',
      'weight' => 1,
    ); /* WAS: '' */
    $data['ting_object-ting_object-ting_cover']['display']['ding_item_viewer_small'] = array(
      'label' => 'hidden',
      'module' => 'ding_item_viewer',
      'settings' => array(
        'image_style' => 'ding_item_viewer_image_small',
      ),
      'type' => 'ting_cover_ding_item_viewer',
      'weight' => 0,
    ); /* WAS: '' */
  }
  if (isset($data['ting_object-ting_object-ting_subjects'])) {
    $data['ting_object-ting_object-ting_subjects']['display']['ding_item_viewer_big'] = array(
      'label' => 'inline',
      'module' => 'ding_item_viewer',
      'settings' => array(),
      'type' => 'ting_subjects_ding_item_viewer',
      'weight' => 5,
    ); /* WAS: '' */
  }
  if (isset($data['ting_object-ting_object-ting_title'])) {
    $data['ting_object-ting_object-ting_title']['display']['ding_item_viewer_big'] = array(
      'label' => 'hidden',
      'module' => 'ding_item_viewer',
      'settings' => array(
        'link_type' => 'collection',
      ),
      'type' => 'ting_title_ding_item_viewer',
      'weight' => 0,
    ); /* WAS: '' */
    $data['ting_object-ting_object-ting_title']['display']['ding_item_viewer_small'] = array(
      'label' => 'hidden',
      'module' => 'ding_item_viewer',
      'settings' => array(
        'link_type' => 'none',
      ),
      'type' => 'ting_title_ding_item_viewer',
      'weight' => 1,
    ); /* WAS: '' */
  }
}
