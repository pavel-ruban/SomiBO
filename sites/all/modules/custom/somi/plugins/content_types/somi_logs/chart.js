(function ($) {
  function getRandomColor() {
    var letters = '0123456789ABCDEF'.split('');
    var color = '#';
    for (var i = 0; i < 6; i++) {
      color += letters[Math.floor(Math.random() * 16)];
    }
    return color;
  }

  var randomScalingFactor = function () {
    return Math.round(Math.random() * 100)
  };
  var randomColorFactor = function () {
    return Math.round(Math.random() * 255)
  };

  Drupal.behaviors.somiChart = {
    attach: function (context) {
      var pieData = [];

      $.each(Drupal.settings.chartData, function (i, v) {
        var rand_color = getRandomColor();

        pieData.push({
          value: v.access_count,
          color: rand_color,
          highlight: getRandomColor(),
          label: 'uid: ' + v.uid + ' ' + v.name + ' card: ' + v.card
        });
      });

      var ctx = document.getElementById("chart-area").getContext("2d");
      window.myPie = new Chart(ctx).Pie(pieData);

      $('#randomizeData').click(function () {
        $.each(pieData, function (i, piece) {
          pieData[i].value = randomScalingFactor();
          pieData[i].color = 'rgba(' + randomColorFactor() + ',' + randomColorFactor() + ',' + randomColorFactor() + ',.7)';
        });

        window.myPie.update();
      });
    }
  }
})(jQuery);