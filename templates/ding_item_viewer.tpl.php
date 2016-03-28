<?php
/**
 * @file
 *  Template for ding item viewer.
 *
 */
?>

<div class="ding-item-viewer">
  <div id="<?php echo $hash; ?>"
       ding-item-viewer-hash="<?php echo $hash; ?>"
       ding-item-viewer-autoplay="<?php echo $autoplay; ?>"
  >
    <?php foreach ($searches as $i => $search): ?>
      <?php foreach ($search['search_items'] as $item_id => $item): ?>
        <div class="ding-item-viewer-item index-<?php echo $i; ?>" carousel-item="<?php echo $item_id?>">
          <?php echo $item['small']; ?>
        </div>
      <?php endforeach; ?>
    <?php endforeach; ?>
  </div>

  <div class="ding-item-viewer-big" style="display: none;">
    <?php foreach ($searches as $i => $search): ?>
      <?php foreach ($search['search_items'] as $item_id => $item): ?>
        <div class="ding-item-viewer-item index-<?php echo $i; ?>" carousel-item="<?php echo $item_id?>">
          <?php echo $item['big']; ?>
        </div>
      <?php endforeach; ?>
    <?php endforeach; ?>
  </div>
  <div class="ding-item-viewer-small"></div>

  <!-- Only print tabs if there is more than 1 -->
  <?php if (count($searches) > 1): ?>
    <div class="ding-item-viewer-tabs">
      <ul class="ding-item-viewer-list-tabs">
        <?php foreach ($searches as $i => $search): ?>
          <li class="ding-item-viewer-item index-<?php echo $i; ?>" tab-index="<?php echo $i; ?>">
            <a href="#"><?php echo $search['title'] ?></a>
          </li>
        <?php endforeach; ?>
      </ul>
    </div>
  <?php endif; ?>
</div>
