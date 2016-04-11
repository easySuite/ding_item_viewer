(function ($) {
  /**
   * Start the carousel when the document is ready.
   */
  $(document).ready(function() {
    $('.ding-item-viewer').each(function(i, e) {
      var autoplay = $(e).attr('ding-item-viewer-autoplay') * 1000;
      var tabs = $(e).find('ul.ding-item-viewer-list-tabs');
      var tabs_index = $(tabs).children().length - 1;
      var index = 0;

      // Init carousel on page load and tab change.
      function show_carousel(index) {
        var current_tab = '#tab-' + index;
        var carousel_wrapper = $(e).find(current_tab + ' div.carousel-items');

        $(current_tab).show();
        $(carousel_wrapper).show();

        // Change small carousel item on big when carousel library init.
        $(carousel_wrapper).on('init', function(event, slick) {
          change_item_size_to_big(this, index, slick.currentSlide);
        });

        // Init carousel
        $(carousel_wrapper).slick({
          arrows: true,
          centerMode: true,
          centerPadding: '50px',
          slidesToShow: 6,
          useTransform: false,
          slidesToScroll: 1,
          variableWidth: true,

          responsive: [{
            breakpoint: 1024,
            settings: {
              slidesToShow: 3
            }
          }]
        });

        // Change small carousel item on big on carousel change.
          $(carousel_wrapper).on('beforeChange', function(event, slick, currentSlide, nextSlide) {
            change_next_item_to_big(this, index, currentSlide, nextSlide);
        });
      }

      // Hide carousel on tab change.
      function hide_carousel(index) {
        var current_tab = '#tab-' + index;
        var carousel_wrapper = $(e).find(current_tab + ' div.carousel-items');
        var current_slide = $(carousel_wrapper).slick('slickCurrentSlide');

        reset_item_size($(carousel_wrapper), index, current_slide);
        $(carousel_wrapper).slick('unslick');
      }

      // Change item size from small to big on carousel init.
      function change_item_size_to_big(carousel, tab_index, slick_slide) {
        var current_tab = '#tab-' + tab_index;
        var current_item_id = $(carousel).find('[data-slick-index=' + slick_slide + ']').attr('carousel-item');
        var current_item = $(carousel).find('div[carousel-item="' + current_item_id + '"]');
        var current_item_big = $(current_tab).find('.carousel-items-big [carousel-item="' + current_item_id + '"]');
        var copy_holder = $(current_tab + ' .ding-item-viewer-small');

        // Copy current carousel item.
        copy_holder.html($(current_item).html());
        $(current_item).empty();
        copy_holder.children().hide();

        $(current_item).html($(current_item_big).html());
      }

      // Change current slide size to small and next slide to big on carousel slide.
      function change_next_item_to_big(carousel, tab_index, cur_slide, next_slide) {
        // Replace big slide with small.
        var current_tab = '#tab-' + tab_index;
        var current_item_id = $(carousel).find('[data-slick-index=' + cur_slide + ']').attr('carousel-item');
        var current_item = $(carousel).find('div[carousel-item="' + current_item_id + '"]');
        var copy_holder = $(current_tab + ' .ding-item-viewer-small');
        var current_item_small = copy_holder.html();

        copy_holder.empty();
        $(current_item).html(current_item_small);
        $(current_item).children('div').show();

        //Replace small slide with big.
        var next_item_id = $(carousel).find('[data-slick-index=' + next_slide + ']').attr('carousel-item');
        var next_item = $(carousel).find('div[carousel-item="' + next_item_id + '"]');
        var next_item_big = $(current_tab).find('.carousel-items-big [carousel-item="' + next_item_id + '"]');

        copy_holder.html($(next_item).html());
        $(next_item).empty();
        copy_holder.hide();

        $(next_item).html($(next_item_big).html());
        $(next_item).show();
      }

      // Reset current item size on tab change.
      function reset_item_size(carousel, tab_index, slick_slide) {
        // Replace big slide with small.
        var current_tab = '#tab-' + tab_index;
        var current_item_id = $(carousel).find('[data-slick-index=' + slick_slide + ']').attr('carousel-item');
        var current_item = $(carousel).find('div[carousel-item="' + current_item_id + '"]');
        var copy_holder = $(current_tab + ' .ding-item-viewer-small');
        var current_item_small = copy_holder.html();

        copy_holder.empty();
        $(current_item).html(current_item_small);
        $(current_item).children('div').show();
      }

      show_carousel(0);

      // Stop tab switching if mouse enters carousel.
      var is_active = true;
      $(e).mouseenter(function() {
        is_active = false;
      }).mouseleave(function() {
        is_active = true;
      });

      if (autoplay != 0) {
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
      }

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

        $(tabs).find('li.index-' + prev_index).removeClass('active');
        $(tabs).find('li.index-' + index).addClass('active');
        $(e).children('div#tab-' + prev_index).hide();
        hide_carousel(prev_index);
        show_carousel(index);
      }

      // Switch tabs on click by it.
      $(tabs).find('li').on('click', function(event) {
        event.preventDefault();
        update_carousel(false, $(this).attr('tab-index'));
      });
    });
  });
})(jQuery);
