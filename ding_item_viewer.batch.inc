<?php
/**
 * @file
 * Batch operations file.
 */

/**
 * Batch job.
 *
 * Fetch items with covers.
 */
function ding_item_viewer_batch_process_items($title, $query, $limit, $sort, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['search_page'] = 1;
    $context['sandbox']['items'] = array();
    $context['sandbox']['debug'] = variable_get('ding_item_viewer_debug', FALSE);
  }

  $search_result = ding_item_viewer_search_ting($query, $context['sandbox']['search_page'], 50, $sort);

  if ($search_result->numTotalCollections > 0) {
    $collection_ids = array_keys($search_result->collections);
    $cover_exists = ding_item_viewer_check_covers($collection_ids);


    $context['sandbox']['items'] = array_merge($context['sandbox']['items'], array_keys($cover_exists));
    $key = ding_item_viewer_generate_cache_id($title . $query);
    $context['results'][$key] = $context['sandbox']['items'];
    $context['sandbox']['progress'] += count($cover_exists);
    $context['message'] = t('Now processing theme %title.<br />Items found: %num / %max', array('%title' => $title, '%num' => $context['sandbox']['progress'], '%max' => $limit));

    if ($context['sandbox']['debug']) {
      $t = array(
        '@n' => count($cover_exists),
        '@q' => $query,
        '@p' => $context['sandbox']['search_page'],
        '@c' => $search_result->numTotalCollections,
      );
      watchdog('item_viewer', 'Found @n items with covers. Query: @q. Page: @p. Collections: @c.', $t, WATCHDOG_DEBUG);
    }

    if ($context['sandbox']['progress'] < $limit) {
      $context['finished'] = $context['sandbox']['progress'] / $limit;
    }
    else {
      $context['results'][$key] = array_slice($context['results'][$key], 0, $limit);
    }

    $context['sandbox']['search_page']++;
  }
}

/**
 * Batch job.
 *
 * Load items and create markup.
 */
function ding_item_viewer_batch_generate_content(&$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 1;
    $context['sandbox']['themes'] = count($context['results']);
    $context['sandbox']['cache_ttl'] = variable_get('ding_item_viewer_cache_ttl', 0) * 3600;
  }

  $t = array(
    '%num' => $context['sandbox']['progress'],
    '%max' => $context['sandbox']['themes'],
  );
  $context['message'] = t('Building themes content: %num / %max', $t);

  $ids = current($context['results']);
  $cid = key($context['results']);

  $objects = ding_entity_load_multiple($ids);

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
  cache_set($cid, $items, 'cache_ding_item', REQUEST_TIME + $context['sandbox']['cache_ttl']);

  if ($context['sandbox']['progress'] < $context['sandbox']['themes']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['themes'];
  }

  $context['sandbox']['progress']++;
  next($context['results']);
}

/**
 * Batch finished callback.
 */
function ding_item_viewer_batch_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('Completed fetching items.'));
  }
  else {
    drupal_set_message(t('Failed to load items. Restart the job with <em>Debug</em> enabled and consult the logs.'), 'error');
  }
}
