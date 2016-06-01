<div id="user-crystalls-log">
  <h2><?php echo $title; ?></h2>
  <?php if (!empty($score_board_link)): ?>
    <?php echo $score_board_link; ?>
  <?php endif; ?>
  <?php if (!empty($account_form)): ?>
    <?php echo render($account_form); ?>
  <?php endif; ?>
  <?php echo $accounts_total; ?>
  <?php echo $accounts_history; ?>
</div>