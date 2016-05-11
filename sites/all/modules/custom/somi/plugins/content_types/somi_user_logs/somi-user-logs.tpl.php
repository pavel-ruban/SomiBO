<h2 class="chart">Статистика использование Rfid замка</h2>
<div>
  <div id="canvas-holder">
    <canvas id="chart-area" width="750" height="750"/>
  </div>
  <div class="chart-wrapper">
    <h3>Статистика использования RFID замка пользователем</h3>
    <h2>Сумма = <?php echo $access_count; ?></h2>
    <h4><?php echo chart_user_title($uid); ?></h4>
  </div>
  <div class="event-wrapper">
    <h3>История</h3>
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
