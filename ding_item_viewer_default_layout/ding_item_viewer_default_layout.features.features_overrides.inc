<?php
/**
 * @file
 * ding_item_viewer_default_layout.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function ding_item_viewer_default_layout_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_group
  $overrides["field_group.group_data|ting_object|ting_object|ding_item_viewer_big.data|children|0"] = 'ting_abstract';
  $overrides["field_group.group_data|ting_object|ting_object|ding_item_viewer_big.data|children|1"] = 'ting_author';
  $overrides["field_group.group_data|ting_object|ting_object|ding_item_viewer_big.data|children|2"] = 'ting_subjects';
  $overrides["field_group.group_data|ting_object|ting_object|ding_item_viewer_big.data|children|3"] = 'ding_entity_buttons';
  $overrides["field_group.group_data|ting_object|ting_object|ding_item_viewer_big.data|children|4"] = 'more_info';

  // Exported overrides for: field_instance
  $overrides["field_instance.ting_object-ting_object-ding_entity_buttons.display|ding_item_viewer_big"] = array(
    'label' => 'hidden',
    'module' => 'ding_entity',
    'settings' => array(),
    'type' => 'ding_entity_buttons_ajax',
    'weight' => 6,
  );
  $overrides["field_instance.ting_object-ting_object-ting_abstract.display|ding_item_viewer_big"] = array(
    'label' => 'hidden',
    'module' => 'ding_item_viewer',
    'settings' => array(
      'trim_length' => 100,
    ),
    'type' => 'ting_abstract_ding_item_viewer',
    'weight' => 3,
  );
  $overrides["field_instance.ting_object-ting_object-ting_author.display|ding_item_viewer_big"] = array(
    'label' => 'hidden',
    'module' => 'ding_item_viewer',
    'settings' => array(),
    'type' => 'ting_author_ding_item_viewer',
    'weight' => 4,
  );
  $overrides["field_instance.ting_object-ting_object-ting_author.display|ding_item_viewer_small"] = array(
    'label' => 'hidden',
    'module' => 'ding_item_viewer',
    'settings' => array(),
    'type' => 'ting_author_ding_item_viewer',
    'weight' => 2,
  );
  $overrides["field_instance.ting_object-ting_object-ting_cover.display|ding_item_viewer_big"] = array(
    'label' => 'hidden',
    'module' => 'ding_item_viewer',
    'settings' => array(
      'image_style' => 'ding_item_viewer_image_big',
    ),
    'type' => 'ting_cover_ding_item_viewer',
    'weight' => 1,
  );
  $overrides["field_instance.ting_object-ting_object-ting_cover.display|ding_item_viewer_small"] = array(
    'label' => 'hidden',
    'module' => 'ding_item_viewer',
    'settings' => array(
      'image_style' => 'ding_item_viewer_image_small',
    ),
    'type' => 'ting_cover_ding_item_viewer',
    'weight' => 0,
  );
  $overrides["field_instance.ting_object-ting_object-ting_subjects.display|ding_item_viewer_big"] = array(
    'label' => 'inline',
    'module' => 'ding_item_viewer',
    'settings' => array(),
    'type' => 'ting_subjects_ding_item_viewer',
    'weight' => 5,
  );
  $overrides["field_instance.ting_object-ting_object-ting_title.display|ding_item_viewer_big"] = array(
    'label' => 'hidden',
    'module' => 'ding_item_viewer',
    'settings' => array(
      'link_type' => 'collection',
    ),
    'type' => 'ting_title_ding_item_viewer',
    'weight' => 0,
  );
  $overrides["field_instance.ting_object-ting_object-ting_title.display|ding_item_viewer_small"] = array(
    'label' => 'hidden',
    'module' => 'ding_item_viewer',
    'settings' => array(
      'link_type' => 'none',
    ),
    'type' => 'ting_title_ding_item_viewer',
    'weight' => 1,
  );

 return $overrides;
}
