<div>
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
      <?php if (empty($events_data)): ?>
        <li>данных пока нет</li>
      <?php else: ?>
        <?php foreach ($events_data as $e): ?>
          <li class="chart-line">
            <?php echo event_list_user_link($e);; ?>
          </li>
        <?php endforeach; ?>
      <?php endif; ?>
    </ul>
  </div>
  <button style="display: none" id="randomizeData">Randomize Data</button>
</div>