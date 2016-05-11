<h1>Активность сотрудников I20 за <?php echo date('d.m.y', time()); ?>, текущее время <?php echo date('H:i:s', time()); ?></h1>

<div>
  <table>
    <?php $i = 0; ?>
    <?php foreach ($availability_data as $v): ?>
      <?php if ($i == 0): ?>
        <tr>
      <?php endif; ?>
      <td id="<?php echo $v['uid']; ?>" access="<?php echo $v['access']; ?>" class="<?php echo $v['class']; ?>">
        <?php echo  $v['l']; ?>
      </td>
      <?php if ($i > 8): ?>
        <?php $i = 0; ?>
        </tr>
      <?php else: ?>
        <?php ++$i; ?>
      <?php endif; ?>
    <?php endforeach; ?>
  </table>
</div>