<h1>Лидеры по наличию жуков</h1>

<div>
  <table>
    <?php $i = 0; ?>
    <?php foreach ($bugs_data as $v): ?>
      <?php if ($i == 0): ?>
        <tr>
      <?php endif; ?>
      <td id="<?php echo $v['uid']; ?>" access="<?php echo $v['bugs']; ?>" class="<?php echo $v['class']; ?>">
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