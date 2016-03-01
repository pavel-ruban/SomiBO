<?php
/**
 * @file
 * Template for article full view mode.
 */
?>
<?php if (!empty($node->nid)): ?>
  <?php echo $node->nid; ?>
<?php endif; ?>
<?php echo l($title, "node/{$node->nid}", array('html' => TRUE)); ?>
<span>status: <?php echo $node->status ? 'on' : 'off'; ?></span>
<?php if (!empty($content)): ?>
  <?php echo render($content); ?>
<?php endif; ?>
