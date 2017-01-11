<div id="users-wish-lists">
  <h2><?php echo $title; ?></h2>
  <?php if (!empty($wish_lists)): ?>
    <?php echo $wish_lists; ?>
  <?php else: ?>
    <?php echo t('К сожалению wish листы пока не были заполнены :('); ?>
  <?php endif; ?>
</div>