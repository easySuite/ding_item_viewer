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
  'admin title' => 'ding_item_viewer_content_type_admin_title',
  'admin info' => 'ding_item_viewer_content_type_admin_info',
  'edit form' => 'ding_item_viewer_content_type_edit_form',
);

/**
 * Search queries admin form.
 */
function ding_item_viewer_content_type_edit_form($form, &$form_state) {
  unset($form['override_title']);
  unset($form['override_title_text']);
  unset($form['override_title_markup']);

  //Form attachments
  $form['#attached']['js'] = array(
    drupal_get_path('module', 'ding_item_viewer') . '/js/ding_item_viewer.admin.js',
  );
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'ding_item_viewer') . '/css/ding_item_viewer.styles.css',
  );

  variable_set('ding_item_viewer_search_queries_hidden', array());
  $searches_num = !empty($form_state['values']['num_searches']) ? $form_state['values']['num_searches'] : 0;
  $clicked_btn = '';
  $remove_btn = '';
  $hidden = variable_get('ding_item_viewer_search_queries_hidden', array());

  if (isset($form_state['clicked_button'])) {
    $clicked_btn = $form_state['clicked_button']['#name'];

    // Get a clicked 'remove' button.
    foreach ($form_state['buttons'] as $k => $v) {
      if ($v['#name'] == $clicked_btn) {
        if (preg_match('/edit-remove/', $v['#id'])) {
          $remove_btn = $k;
          $hidden[] = $remove_btn;
          variable_set('ding_item_viewer_search_queries_hidden', $hidden);
          break;
        }
      }
    }
  }

  // Ajaxified button for new fields.
  $form['new_search_browsebar_button'] = array(
    '#type' => 'button',
    '#value' => t('Add another'),
    '#name' => 'add_query',
    '#ajax' => array(
      'callback' => 'ding_item_viewer_admin_form_ajaxify',
      'wrapper' => 'ting-search-browsebar-queries',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $form['browsebar'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
  );

  // Get current saved queries.
  $searches = $form_state['conf'];

  $i = 0;
  $c = 1;

  // Display saved queries.
  if (isset($searches[0]['title'])) {
    $c = count($searches);
    for (; $i < $c; $i++) {
      $form['browsebar']['ting_searches']['search_' . $i] = ding_item_viewer_query_form($searches[$i], $i);
    }
  }

  // Whether add a new query field.
  if ($clicked_btn == 'add_query') {
    $searches_num++;
  }

  for (; $i < $searches_num + $c; $i++) {
    $unsubmitted = array();
    // Maybe prev field had some data in it...
    if (isset($form_state['input']['title'][$i])) {
      $unsubmitted = array(
        'title' => $form_state['input']['title'][$i],
        'subtitle' => $form_state['input']['subtitle'][$i],
        'query' => $form_state['input']['query'][$i],
      );
    }

    $form['browsebar']['ting_searches']['search_' . $i] = ding_item_viewer_query_form($unsubmitted, $i);
  }

  // Hide removed fields.
  for ($i = 0; $i < $searches_num + $c; $i++) {
    if (in_array($i, $hidden)) {
      // Hide title, used to sort needed queries when saving.
      $form['browsebar']['ting_searches']['search_' . $i]['title[]']['#value'] = '';
      $form['browsebar']['ting_searches']['search_' . $i]['#prefix'] = '<div class="search-query-hidden">';
      $form['browsebar']['ting_searches']['search_' . $i]['#suffix'] = '</div>';
    }
  }

  // Keep track of query fields count.
  $form['browsebar']['num_searches'] = array(
    '#type' => 'hidden',
    '#value' => $searches_num,
  );

  $form['browsebar']['ding_item_viewer_item_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Item limit'),
    '#description' => t('The number of items to be returned in search result.'),
    '#default_value' => variable_get('ding_item_viewer_item_limit', 18),
    '#size' => 3,
    '#element_validate' => array('element_validate_integer_positive'),
  );

  $form['browsebar']['ding_item_viewer_item_sorting'] = array(
    '#type' => 'select',
    '#title' => t('Sorting'),
    '#options' => array(
      '' => t('- None -'),
      'title_ascending' => t('Title (Ascending)'),
      'title_descending' => t('Title (Descending)'),
      'creator_ascending' => t('Creator (Ascending)'),
      'creator_descending' => t('Creator (Descending)'),
      'date_ascending' => t('Date (Ascending)'),
      'date_descending' => t('Date (Descending)'),
      'acquisitionDate_ascending' => t('Acquisition date (Ascending)'),
      'acquisitionDate_descending' => t('Acquisition date (Descending)'),
    ),
    '#default_value' => variable_get('ding_item_viewer_item_sorting', ''),
    '#description' => t('If not set, defaults to Ranking'),
  );

  $form['browsebar']['ding_item_viewer_cache_ttl'] = array(
    '#type' => 'textfield',
    '#title' => t('Cache TTL'),
    '#description' => t('How many hours the cache lives.'),
    '#default_value' => variable_get('ding_item_viewer_cache_ttl', 1),
    '#size' => '3',
    '#element_validate' => array('element_validate_integer_positive'),

  );

  $form['browsebar']['ding_item_viewer_interval'] = array(
    '#type' => 'textfield',
    '#title' => t('Slide interval'),
    '#default_value' => variable_get('ding_item_viewer_interval', 5),
    '#description' => t('The interval between sliding in seconds.'),
    '#size' => '3',
    '#element_validate' => array('element_validate_integer_positive'),
    '#required' => TRUE,
  );

  $form['browsebar']['ding_item_viewer_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Debug'),
    '#default_value' => variable_get('ding_item_viewer_debug', FALSE),
    '#description' => t('Log the search process information.'),
  );

  // Wrap the form, due to draggable items renewal.
  $form['#prefix'] = '<div id="ting-search-browsebar-queries">';
  $form['#suffix'] = '</div>';
  // Custom themer, mainly used for dragable table creation.
  $form['#theme'] = array('ding_item_viewer_admin_form');
  // Custom form submit handler.
  $form['#submit'] = array('ding_item_viewer_content_type_edit_form_submit');

  return $form;
}

/**
 * AJAX responder for field addition/removal fields.
 */
function ding_item_viewer_admin_form_ajaxify($form, &$form_state) {
  return $form;
}

/**
 * Theme the queries form, mainly adding a table drag-n-drop feature.
 */
function theme_ding_item_viewer_admin_form($variables) {
  $form = $variables['form'];
  drupal_add_tabledrag('ting-search-item_viewer-admin-sort', 'order', 'sibling', 'sort');

  $header = array('Searches', '');
  $rows = array();
  foreach (element_children($form['browsebar']['ting_searches']) as $key) {
    // Add class to group weight fields for drag and drop.
    $form['browsebar']['ting_searches'][$key]['sort[]']['#attributes']['class'][] = 'sort';

    // Get sort element.
    $sort = $form['browsebar']['ting_searches'][$key]['sort[]'];
    unset($form['browsebar']['ting_searches'][$key]['sort[]']);

    // Build rows.
    $classes = array('draggable');
    if (isset($form['browsebar']['ting_searches'][$key]['#prefix'])) {
      $classes[] = 'search-query-hidden';
    }

    $rows[] = array(
      'data' => array(
        drupal_render($form['browsebar']['ting_searches'][$key]),
        drupal_render($sort),
      ),
      'class' => $classes,
    );
  }

  $table_vars = array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => 'ting-search-item_viewer-admin-sort'),
    'caption' => '',
    'colgroups' => array(),
    'sticky' => FALSE,
    'empty' => 'EMPTY',
  );
  $output = theme_table($table_vars);

  // Render remaining elements.
  $output .= drupal_render_children($form);

  return $output;
}

/**
 * Form part, describing query fields.
 *
 * @param array $item
 *   Values for existing query.
 *
 * @return array
 *   Fields structure.
 */
function ding_item_viewer_query_form($item = array(), $index = 0) {
  $form = array();

  $form['sort[]'] = array(
    '#type' => 'weight',
    '#delta' => 5,
    '#default_value' => 0,
    '#value' => 0,
    '#attributes' => array(
      'class' => array(
        'sort-hidden',
      ),
    ),
  );

  $form['title[]'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('The title of the search is used for the tab in the browsebar. Keep it short.'),
    '#default_value' => isset($item['title']) ? $item['title'] : '',
    '#prefix' => '<div class="search-item_viewer-query">',
  );

  $form['subtitle[]'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#description' => t('The subtitle displayed next to the search results.'),
    '#default_value' => isset($item['subtitle']) ? $item['subtitle'] : '',
  );

  $form['query[]'] = array(
    '#type' => 'textfield',
    '#title' => t('Query'),
    '#maxlength' => 2048,
    '#description' => t('The query to display search results for.'),
    '#default_value' => isset($item['query']) ? $item['query'] : '',
  );

  $form['remove[]'] = array(
    '#type' => 'button',
    '#value' => t('Remove'),
    '#name' => 'remove_' . $index,
    '#attributes' => array(
      'class' => array(
        'remove',
      ),
    ),
    '#suffix' => '</div><div class="clear"></div>',
    '#ajax' => array(
      'callback' => 'ding_item_viewer_admin_form_ajaxify',
      'wrapper' => 'ting-search-browsebar-queries',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  return $form;
}

/**
 * Submit handler for admin backend queries form.
 */
function ding_item_viewer_content_type_edit_form_submit($form, &$form_state) {
  $values = $form_state['values'];

  variable_set('ding_item_viewer_item_limit', $values['ding_item_viewer_item_limit']);
  variable_set('ding_item_viewer_item_sorting', $values['ding_item_viewer_item_sorting']);
  variable_set('ding_item_viewer_cache_ttl', $values['ding_item_viewer_cache_ttl']);
  variable_set('ding_item_viewer_interval', $values['ding_item_viewer_interval']);
  variable_set('ding_item_viewer_debug', $values['ding_item_viewer_debug']);


  $c = count($form_state['input']['title']);
  $searches = array();

  for ($i = 0; $i < $c; $i++) {
    // Make an array for saving, ignoring queries w/o title.
    $title = trim($form_state['input']['title'][$i]);
    $subtitle = trim($form_state['input']['subtitle'][$i]);
    $query = trim($form_state['input']['query'][$i]);

    if (!empty($title) && !empty($query)) {
      $searches[] = array(
        'title' => $title,
        'subtitle' => $subtitle,
        'query' => $query,
      );
    }
  }

  $form_state['conf'] = $searches;

  // Clear all item list cache.
  module_invoke('ding_item_cache', 'clear_all');

  // Start batch operations if there are some themes.
  if (count($searches) < 1) {
    return;
  }

  $cache_ttl = variable_get('ding_item_viewer_cache_ttl', 0) * 3600;

  foreach ($searches as $search) {
    $search_result = ding_item_viewer_search_ting($search['query'], 1, 50, $values['ding_item_viewer_item_sorting']);

    $count_search_results = $search_result->numTotalCollections;
    if ($count_search_results > 0) {
      $collection_ids = array_keys($search_result->collections);
      $cover_exists = ding_item_viewer_check_covers($collection_ids);
      $cache_id = ding_item_viewer_generate_cache_id($search['title'] . $search['query']);
      $item_ids = array_keys($cover_exists);

      $objects = ding_entity_load_multiple($item_ids);

      $items = array();
      foreach ($objects as $item) {
        $build = ting_object_view($item, 'ding_item_viewer_big');
        $big = drupal_render($build);
        $build = ting_object_view($item, 'ding_item_viewer_small');
        $small = drupal_render($build);

        $items[$item->localId] = array(
          'small' => $small,
          'big' => $big,
        );
      }

      // Cache rendered items.
      cache_set($cache_id, $items, 'cache_ding_item', REQUEST_TIME + $cache_ttl);
    }
  }
}

/**
 * Return the pane contents.
 */
function ding_item_viewer_content_type_render($subtype, $conf, $panel_args, $context) {
  dump($conf);
  $block = new stdClass();

  // Load required JS and CSS files.
  drupal_add_library('system', 'drupal.ajax');
  drupal_add_css(drupal_get_path('module', 'ding_item_viewer') . '/css/ding_item_viewer.css');
  drupal_add_js(drupal_get_path('module', 'ding_item_viewer') . '/js/ding_item_viewer.js');

  if (module_exists('ding_availability')) {
    drupal_add_js(drupal_get_path('module', 'ding_availability') . '/js/ding_availability.js');
  }

  $js_setting = array(
    'ding_item_viewer' => array(
      'visible_items' => 6,
      'big_item_positon' => 3,
      'interval' => variable_get('ding_item_viewer_interval', 5),
    ),
  );
  drupal_add_js($js_setting, 'setting');

  $block->content = theme('ding_item_viewer_container', array('url' => url('ding_item_viewer')));

  return $block;
}
