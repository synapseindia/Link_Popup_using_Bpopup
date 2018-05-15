/**
 * @file
 * A JavaScript file for the theme.
 *
 * In order for this JavaScript to be loaded on pages, see the instructions in
 * the README.txt next to this file.
 */
/**
 * verify mobile popup
 **/
(function($) {
  $(document).ready(function() {
  var link = $('a[rel="link-popup"]');
  if (link) {
    $('body').append('<div><div id="popup"><span class="button b-close"><span></span></span><div class="c_area"></div></div></div>').html();
  }
  $('a[rel="link-popup"]').click(function(e){
    e.preventDefault();
    var scroll = $(document).scrollTop();
    $("#popup-load-img").css("top", scroll+"px");
    $("#popup").css("height", "");
    $("#popup").css("width", "");
    var url = $(this).attr('href');
    var slide = 'slideBack';

    var p = {},
    width = "950",
    height = "850",
    e,
    a = /\+/g,  // Regex for replacing addition symbol with a space
    r = /([^&=]+)=?([^&]*)/g,
    d = function (s) { return decodeURIComponent(s.replace(a, ' ')); },
    q = url.split('?');        
    while (e = r.exec(q[1])) {
      e[1] = d(e[1]);
      e[2] = d(e[2]);
      if (e[1] != 'slide'){
        if (e[1] == 'width') {
          width = e[2];
        }
        else if (e[1] == 'height') {
          height = e[2];
        }
      }
      else {
        if (e[2] == 'top') {
          slide = 'slideDown';
        }
        else if (e[2] == 'bottom') {
          slide = 'slideUp';
        }
        else if (e[2] == 'right') {
          slide = 'slideBack';
        }
        else if (e[2] == 'left') {
          slide = 'slideIn';
        }
      }
    }
    $("#popup").css('width', width+"px");
    $("#popup").css('height', height+"px");
    $('.c_area').html('');
    $('.b-close span').html('');
    $('#modal-popup').show();
    
    $('#popup').bPopup({
      content:'iframe', //'ajax', 'iframe' or 'image'
      contentContainer:'.c_area',
      loadUrl:url, //Uses $.load()
      speed: 650,
      amsl: 0,
      transition: slide,
      positionStyle: 'fixed',
      iframeAttr: ('scrolling="yes" frameborder="0"'),
      onOpen: function() {
        $('#popup-load-img').show();
        var loader = "/images/dim-loading.gif";
        var close_button = "/images/close.png";
        $('.b-close span').html('<img src="'+Drupal.settings.basePath + Drupal.settings.lpop_up.lpop_upPath + close_button + '"/>');
      },
      onClose: function() {
        $('.c_area').empty();
        $('.b-close span').empty();
      }
    }, function(){
      width = width - 10;
      height = height - 60;
      $("#popup iframe").css('width', width+"px");
      $("#popup iframe").css('height', height+"px");
    });
  });
});
})(jQuery);
