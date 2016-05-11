(function ($) {
  function getRandomColor() {
    var letters = '0123456789ABCDEF'.split('');
    var color = '#';
    for (var i = 0; i < 6; i++) {
      color += letters[Math.floor(Math.random() * 16)];
    }
    return color;
  }

  Drupal.behaviors.somiUserChart = {
    attach: function (context) {
      var randomScalingFactor = function () {
        return Math.round(Math.random() * 100)
      };
      var randomColorFactor = function () {
        return Math.round(Math.random() * 255)
      };

      var lineData = {
        months: [],
        values: []
      };

      $.each(Drupal.settings.chartData, function (i, v) {
        $.each(i , function (ii, vv) {
          lineData.months.push(vv.month);
          lineData.values.push(vv.access_count);
        })
      });

      var lineChartData = {
        labels: lineData.months,
        datasets: [
          {
            label: "Статистика доступа",
            fillColor: "rgba(151,187,205,0.2)",
            strokeColor: "rgba(151,187,205,1)",
            pointColor: "rgba(151,187,205,1)",
            pointStrokeColor: "#fff",
            pointHighlightFill: "#fff",
            pointHighlightStroke: "rgba(151,187,205,1)",
            data: lineData.values
          }
        ]

      }

      var ctx = document.getElementById("chart-area").getContext("2d");
      window.myLine = new Chart(ctx).Line(lineChartData, {
        responsive: true
      });

      $('#randomizeData').click(function () {
        lineChartData.datasets[0].fillColor = 'rgba(' + randomColorFactor() + ',' + randomColorFactor() + ',' + randomColorFactor() + ',.3)';
        lineChartData.datasets[0].data = [randomScalingFactor(), randomScalingFactor(), randomScalingFactor(), randomScalingFactor(), randomScalingFactor(), randomScalingFactor(), randomScalingFactor()];

        window.myLine.update();
      });
    }
  }
})(jQuery);