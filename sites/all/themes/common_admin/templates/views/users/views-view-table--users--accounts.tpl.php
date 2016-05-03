<?php
/**
 * @file
 * Template to display a view as a table.
 */
?>
<table <?php if ($classes) { print 'class="'. $classes . '" '; } ?><?php print $attributes; ?>>
  <?php if (!empty($title) || !empty($caption)) : ?>
  <caption><?php print $caption . $title; ?></caption>
  <?php endif; ?>
  <?php if (!empty($header)) : ?>
  <thead>
  <tr>
    <?php foreach ($header as $field => $label): ?>
    <th>
      <?php print $label; ?>
    </th>
    <?php endforeach; ?>
  </tr>
  </thead>
  <?php endif; ?>
  <tbody>
  <?php foreach ($rows as $row_count => $row): ?>
  <tr>
    <?php foreach ($row as $field => $content): ?>
    <td>
      <?php print $content; ?>
    </td>
    <?php endforeach; ?>
  </tr>
    <?php endforeach; ?>
  </tbody>
</table>
