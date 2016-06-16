var SOMI = SOMI || {};
(function($) {
  // This function resort table to put most recent elements to upper left corner. It works only with one td, marked as
  // most recent element.
  SOMI.somi_board_update = function(td) {
    if (td && td.id && td.class && td.info) {
      var $table = $('table.somi-board');
      var uid = td.id
      var selector = 'td#' + uid;
      var $target_td = $(selector);

      if ($target_td.length) {
        var $target_tr = $target_td.parent('tr');
        var $next_last_td = undefined;

        $('table tr').each(function (i, v) {
          var $cur_tr = $(v);

          if ($cur_tr.attr('id') == $target_tr.attr('id')) {
            $target_td.remove();

            $target_td.find('span').html(td.info);
            $target_td.find('img').attr('class', td.class);
            $target_td.attr('class', 'td.class');

            $('tr#tr-1').prepend($target_td);

            var promise1 = $target_td.animate(
              {backgroundColor: '#FFF79F'},
              1500
            );

            var promise2 = $target_td.find('img').animate(
              {opacity: 0.7},
              1500
            );

            $.when(promise1, promise2).done(function () {
              $target_td.animate(
                {backgroundColor: 'transparent'},
                1500
              );
              $target_td.find('img').animate(
                {opacity: 1},
                1500
              );
            });

            // Brake each loop.
            return false;
          }
          else {
            // Get last td from row. If we already removed last element in previous iteration use it.
            var $cur_last_td = $next_last_td
              ? $next_last_td
              : $cur_tr.find('td').last('td');

            var $next_tr = $cur_tr.next(v);

            if ($next_tr.attr('id') == $target_tr.attr('id')) {
              $target_td.remove();
              $next_tr.prepend($cur_last_td);
            }
            else {
              $next_last_td = $next_tr.find('td').last('td');

              $cur_last_td.remove();
              $next_last_td.remove();
              $next_tr.prepend($cur_last_td);
            }
          }
        });
      }
    }
  }

  var now = new Date();
  // Set function execute at 05 am. To reload the page.
  var secsToDate = new Date(now.getFullYear(), now.getMonth(), now.getDate(), 5, 0, 0, 0) - now;
  if (secsToDate < 0) {
    secsToDate += 86400000; // if it's after 05am, try 10am tomorrow.
  }

  // Reload page to clear previous date data.
  setTimeout(function(){
    window.location.reload(false);
  }, secsToDate);

  // Получить полноценный tcp туннель для работы в обе стороны, протокол websocket.
  var socket = io.connect('http://95.172.148.149:8080');
  //var socket = io.connect('http://127.0.0.1:8080');

  // Функция которая сработает когда нам по туннелю через протокол websocket
  // отправят данные как и в случае с ajax.
  socket.on('stream', function (data) {
    // Для наглядности вставим ответ внутрь враппера.
    if (data && data.info && data.class && data.id) {
      SOMI.somi_board_update(data);
    }
  });
})(jQuery);