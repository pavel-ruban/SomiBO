<h1>Лидеры по наличию друпликонов</h1>

<div>
  <table>
    <?php $i = 0; ?>
    <?php foreach ($drupal_data as $v): ?>
      <?php if ($i == 0): ?>
        <tr>
      <?php endif; ?>
      <td id="<?php echo $v['uid']; ?>" access="<?php echo $v['drupal']; ?>" class="<?php echo $v['class']; ?>">
        <span class="board-counter"><?php echo  $v['drupal']; ?></span>
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