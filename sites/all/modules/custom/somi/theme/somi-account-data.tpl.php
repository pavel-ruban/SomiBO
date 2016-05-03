<?php

/**
 * @file
 *
 * Template.
 */
?>

<?php if (!empty($image)): ?>
  <?php echo $image; ?>
<?php endif; ?>

<?php if (isset($value)): ?>
  <span class="crystalls-count"><?php echo $value; ?></span>
<?php endif; ?>
