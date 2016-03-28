(function ($) {
  /**
   * Start the carousel when the document is ready.
   */
  $(document).ready(function() {
    $('.ding-item-viewer').each(function(i, e) {
      var viewer_wrapper = this;
      var carousel_hash = $(e).find('div[id^="ding_item_viewer-"]').attr('ding-item-viewer-hash');
      var carousel_wrapper = $(e).children('div[id^="ding_item_viewer-"]');
      var carousel_tabs = $(e).find('ul.ding-item-viewer-list-tabs');
      var tabs_index = $(carousel_tabs).children().length - 1;
      var autoplay = $(carousel_wrapper).attr('ding-item-viewer-autoplay') * 1000;
      var copy_holder = $('.ding-item-viewer-small');
      var index = 0;

      // Change small carousel item on big when carousel library init.
      $(carousel_wrapper).on('init', function(event, slick) {
        var current_item_id = $(this).find('[data-slick-index=' + slick.currentSlide + ']').attr('carousel-item');
        var current_item = $('#' + carousel_hash + ' div[carousel-item="' + current_item_id + '" ]');
        var current_item_big = $(viewer_wrapper).find('.ding-item-viewer-big [carousel-item="' + current_item_id + '"]');

        // Copy current carousel item.
        copy_holder.html($(current_item).html());
        $(current_item).empty();
        copy_holder.children().hide();

        $(current_item).html($(current_item_big).html());
      });

      // Init carousel
      $(carousel_wrapper).slick({
        arrows: true,
        centerMode: true,
        centerPadding: '50px',
        slidesToShow: 5,
        slidesToScroll: 1
      });

      // Change small carousel item on big on carousel change.
      $(carousel_wrapper).on('beforeChange', function (event, slick, currentSlide, nextSlide) {
        // Replace big slide with small.
        var current_item_id = $(this).find('[data-slick-index=' + currentSlide + ']').attr('carousel-item');
        var current_item = $('#' + carousel_hash + ' div[carousel-item="' + current_item_id + '"]');
        var current_item_small = copy_holder.html();

        copy_holder.empty();
        $(current_item).html(current_item_small);
        $(current_item).children('div').show();

        //Replace small slide with big.
        var next_item_id = $(this).find('[data-slick-index=' + nextSlide + ']').attr('carousel-item');
        var next_item = $('#' + carousel_hash + ' div[carousel-item="' + next_item_id + '"]');
        var next_item_big = $(viewer_wrapper).find('.ding-item-viewer-big [carousel-item="' + next_item_id + '"]');

        copy_holder.html($(next_item).html());
        $(next_item).empty();
        copy_holder.hide();

        $(next_item).html($(next_item_big).html());
        $(next_item).show();
      });

      update_carousel(false, false);

      // Stop tab switching if mouse enters carousel.
      var is_active = true;
      $(carousel_wrapper).mouseenter(function() {
        is_active = false;
      }).mouseleave(function() {
        is_active = true;
      });

      $("#" + carousel_hash).find("div[data-slick-index=0]").show();

      // Switch tabs by timer.
      setInterval(function() {
        if (is_active) {
          if (index == tabs_index) {
            update_carousel(false, false);
          }
          else {
            update_carousel(true, false);
          }
        }
      }, autoplay);

      // Switch tabs on click by it.
      $(carousel_tabs).find('li').on('click', function(event) {
        event.preventDefault();
        update_carousel(false, $(this).attr('tab-index'));
      });

      /**
       * Function updates carousel on tab switching.
       *
       * @param bool increment
       *   Determines if we should we switch to next tab or to first.
       * @param bool|string user_selected
       *
       */
      function update_carousel(increment, user_selected) {
        var prev_index = index;

        if (user_selected) {
          index = user_selected;
        }
        else {
          index = (increment) ? index + 1 : 0;
        }

        $(carousel_tabs).find('li.index-' + prev_index).removeClass('active');
        $(carousel_tabs).find('li.index-' + index).addClass('active');
        $(carousel_wrapper).slick('slickUnfilter');
        $(carousel_wrapper).slick('slickFilter', '.index-' + index);
      }
    });
  });
})(jQuery);
