(function($) {
  // set interval
  var tid;

  function default_door_status($tracker, data) {
    $tracker.css('background', '#ECF3F6').text(data);

  }

  function node_status(data, $this)
  {
    if (data && data.status) {
      $tracker = $this;
      var old_data = $tracker.text();

      var color;
      if (data.status != 'OK') {
        color = 'rgb(251, 192, 192)';
      } else {
        color = 'rgb(248, 255, 204)';
      }
      $tracker.css('background-color', color).text(data.status);
      setTimeout(default_door_status, 1000, $tracker, old_data);
    }
  }

  function open_node(node_id, $this)
  {
    $.ajax({
      url: "/open-node/" + node_id,
      success: function(data) { node_status(data, $this)}
    });
  }

  function default_tracker_state($tracker, data) {
    $tracker.css('background', '#ECF3F6').text(data);
  }

  function update_rfid_tag(data) {
    $tracker = $('span#rfid-tracker');
    var old_data = $tracker.text();

    if (old_data != data) {
      $tracker.css('background-color', 'rgb(248, 255, 204)').text(data + ' !!!UPDATED!!!').css('display', 'inline');
      setTimeout(default_tracker_state, 1000, $tracker, data);
    }
  }

  function rfid_tag_tracker() {
    $.ajax({
      url: "/tracker.txt",
      success: update_rfid_tag
    });
  }

  function start_tracker()
  {
    tid = setInterval(rfid_tag_tracker, 1000);
  }

  // to be called when you want to stop the timer
  function stop_tracker()
  {
    clearInterval(tid);
  }

  Drupal.behaviors.somi = {
    attach: function (context, settings) {
      $('input#track-rfids').once('somi-manage', function () {
        $(this).change(function () {
          $input = $(this);

          if ($input.is(':checked')) {
            start_tracker();
            $('input#track-rfid-status').val('on');
          }
          else {
            stop_tracker();
            $('input#track-rfid-status').val('');
          }
        });
      });

      $('a.somi-open-node').each(function(i, v) {
        $(v).once('open-node', function () {
          $this = $(this);
          $this.click(function (e) {
            e.preventDefault();
            open_node($this.attr('node-id'), $this);
            return false;
          });
        });
      });
    }
  }

})(jQuery);
