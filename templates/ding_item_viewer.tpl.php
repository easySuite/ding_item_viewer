<?php
/**
 * @file
 *  Template for ding item viewer.
 *
 */
?>

<div id="<?php echo $hash; ?>" class="ding-item-viewer"
     ding-item-viewer-autoplay="<?php echo $autoplay; ?>"
>
  <?php foreach ($searches as $i => $search): ?>
    <div id="tab-<?php echo $i;?>">
      <!-- Render small items. -->
      <div class="carousel-items" ding-item-viewer-hash="<?php echo $hash; ?>" style="display: none;">
        <?php foreach ($search['search_items'] as $item_id => $item): ?>
          <div class="ding-item-viewer-item index-<?php echo $i; ?>" carousel-item="<?php echo $item_id?>">
            <?php echo $item['small']; ?>
          </div>
        <?php endforeach; ?>
      </div>

      <!-- Render big items for each small. -->
      <div class="carousel-items-big" ding-item-viewer-hash="<?php echo $hash; ?>" style="display: none;">
        <?php foreach ($search['search_items'] as $item_id => $item): ?>
          <div class="ding-item-viewer-item index-<?php echo $i; ?>" carousel-item="<?php echo $item_id?>">
            <?php echo $item['big']; ?>
          </div>
        <?php endforeach; ?>
      </div>

      <div class="ding-item-viewer-small"></div>
    </div>
  <?php endforeach; ?>

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
