<?php
/**
 * @file
 * Template file for viewer layout.
 *
 * Variables:
 *   $data - Array containing array of items to show. Has key as tab number.
 *   $tabs - HTML of tabs. See ding_item_viewer.tabs.tpl.php.
 */
?>
<div class="browsebar-inner"><div class="browsebar-items-wrapper"></div></div>
<?php
  /*
    $i = 0;
    $last = 5; // Fixed number of items to show (starting from 0).
    foreach ($data[0] as $item) {
      if ($i > $last) {
        break;
      }
      $row_class = ($i % 2 == 0) ? 'even' : 'odd';
      if ($i == 0) {
        $row_class .= ' first';
      }
      elseif ($i == $last) {
        $row_class .= ' last';
      }

      if ($i == 3) {
        echo theme('ding_item_viewer_item_active', array('item' => $item, 'item_class' => $row_class));
      }
      else {
        echo theme('ding_item_viewer_item', array('item' => $item, 'item_class' => $row_class));
      }

      $i++;
    }
  */
  ?>
