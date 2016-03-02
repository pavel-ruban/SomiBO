<script src="/libs/js/Chartjs/Chart.js"></script>
<script src="/libs/js/jquery-ui-1.11.4.custom/jquery-ui.min.js"></script>
<script>var ChartData = <?php echo json_encode($chart_data); ?></script>
<script src="/js/chart.js"></script>

<link href="/css/chart.css" rel="stylesheet">
<link href="/libs/js/jquery-ui-1.11.4.custom/jquery-ui.css" rel="stylesheet">
<link href="/libs/js/jquery-ui-1.11.4.custom/jquery-ui.theme.css" rel="stylesheet">
<link href="/libs/js/jquery-ui-1.11.4.custom/jquery-ui.structure.css" rel="stylesheet">

<h1>SOMI - Smart Office Management  Interface</h1>

<div class="text">
  <b>Description: </b>this interface provides table of allowed persons to access RFID  controller based door system. You could see who have access & add new persons or delete from  table
</div>
<h2 class="chart">Статистика использование Rfid замка</h1>

  <a href="/">На главную страницу</a> <a href="/manage">Изменить доступ</a><a href="/availability">Availability</a><a href="/faq">FAQ</a><a href="/exit">Выйти</a>
  <div>
    <form id="chart" method="post">
      <p>Start Date: <input type="text" name="start-date" id="start-datepicker" value="<?php echo $start_date; ?>"></p>
      <p class="end">End Date: <input type="text" name="end-date" id="end-datepicker" value="<?php echo $end_date; ?>"></p>
      <input type="submit"  value="ok" name="ok" />
      <input type="submit" value="reset" name="reset" />
    </form>

    <div id="canvas-holder">
      <canvas id="chart-area" width="750" height="750"/>
    </div>
    <div class="chart-wrapper">
      <h3>Список</h3>
      <ul class="chart">
        <?php if (empty($chart_data)): ?>
          <li>данных пока нет</li>
        <?php else: ?>
          <?php foreach ($chart_data as $v): ?>
            <li class="chart-line">
              <?php echo chart_list_user_link($v);; ?>
            </li>
          <?php endforeach; ?>
        <?php endif; ?>
      </ul>
    </div>
    <div class="event-wrapper">
      <h3>Последние события</h3>
      <ul class="chart">
        <?php if (empty($event_data)): ?>
          <li>данных пока нет</li>
        <?php else: ?>
          <?php foreach ($event_data as $e): ?>
            <li class="chart-line">
              <?php echo event_list_user_link($e);; ?>
            </li>
          <?php endforeach; ?>
        <?php endif; ?>
      </ul>
    </div>
    <button style="display: none" id="randomizeData">Randomize Data</button>
  </div>