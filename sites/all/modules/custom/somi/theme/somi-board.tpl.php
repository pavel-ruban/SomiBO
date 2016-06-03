<h1><?php echo $title; ?></h1>

<div>
  <?php if (!empty($departament_links)): ?>
    <div class="departament-filter">
      <h3><?php echo t('Фильтр по отделам'); ?></h3>
      <ul>
      <?php foreach($departament_links as $link): ?>
        <li><?php echo $link; ?></li>
      <?php endforeach; ?>
      </ul>
    </div>
  <?php endif; ?>
  <?php if (!empty($form)): ?>
    <div class="board-filter-form">
      <?php echo drupal_render($form); ?>
    </div>
  <?php endif; ?>
  <table class="somi-board">
    <?php $i = 0; $tr_i = 1; ?>
    <?php foreach ($data as $v): ?>
      <?php if ($i == 0): ?>
        <tr id="tr-<?php echo $tr_i++; ?>">
      <?php endif; ?>
      <td id="<?php echo $v['uid']; ?>" class="<?php echo $v['class']; ?>">
        <span class="<?php echo !empty($class) ? $class . ' ' : ''; ?>board-counter"><?php echo $v['info']; ?></span>
        <?php if (!empty($v['sub_info'])): ?>
          <span class="sub-info <?php echo !empty($class) ? $class . ' ' : ''; ?>board-counter"><?php echo $v['sub_info']; ?></span>
        <?php endif; ?>
        <?php if (!empty($v['top_info'])): ?>
          <span class="top-info <?php echo !empty($class) ? $class . ' ' : ''; ?>board-counter"><?php echo $v['top_info']; ?></span>
        <?php endif; ?>
        <?php echo  $v['l']; ?>
      </td>
      <?php if ($i > $row_limit): ?>
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