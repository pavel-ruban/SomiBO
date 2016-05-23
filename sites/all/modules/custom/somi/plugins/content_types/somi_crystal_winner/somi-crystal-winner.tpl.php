<h1>Лидеры по наличию кристаллов</h1>

<div>
  <table>
    <?php $i = 0; ?>
    <?php foreach ($crystal_data as $v): ?>
      <?php if ($i == 0): ?>
        <tr>
      <?php endif; ?>
      <td id="<?php echo $v['uid']; ?>" access="<?php echo $v['crystals']; ?>" class="<?php echo $v['class']; ?>">
        <span class="board-counter"><?php echo  $v['crystals']; ?></span>
        <?php echo  $v['l']; ?>
      </td>
      <?php if ($i > 8): ?>
        <?php $i = 0; ?>
        </tr>
      <?php else: ?>
        <?php ++$i; ?>
      <?php endif; ?>
    <?php endforeach; ?>
    <?php if ($i > 0): ?>
      </tr>
    <?php endif; ?>
  </table>
</div>