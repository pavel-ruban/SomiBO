<?php

/**
 * @file
 *
 * CTools content type.
 */

$plugin = array(
  'title' => t('Somi Users Wish Lists'),
  'description' => t('Provides users wish lists'),
  'content_types' => 'somi_user_wish_lists',
  'single' => TRUE,
  'render callback' => 'somi_user_wish_lists_content_type_render',
  'category' => t('Somi'),
  'hook theme' => 'somi_user_wish_lists_content_type_theme',
);

/**
 * Output function for the content type.
 */
function somi_user_wish_lists_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  // Get all users.
  $query = db_select('users', 'u');
  $query->addField('u', 'uid');
  $query->condition('status', 1);
  $uids = $query->execute()->fetchCol();

  $title = t('Wish листы всех сотрудников');
  $wish_lists = [];

  foreach ($uids as $uid) {

    if ($account = user_load($uid)) {
      if (empty($account->field_wish_list)) continue;

      $w = entity_metadata_wrapper('user', $account);

      $rows = [];
      foreach ($w->field_wish_list->value() as $wish) {
        $row = [];
        $row[] = $wish;

        foreach ($row as &$data) {
          $data = "<span class=\"wish\">$data</span";
        }

        $rows[] = $row;
      }

      $wish_list = theme('table', [
        'attributes' => ['class' => ['wish-list']],
        'header' => [
          $account->name,
        ],
        'rows' => $rows
      ]);

      $wish_lists[$account->name] = ['#markup' => $wish_list];


    }
  }

  sort($wish_lists);

  $block->content = theme(
    'somi_user_wish_lists',
    array(
      'wish_lists' => empty($wish_lists) ? '' : render($wish_lists),
      'title' => $title,
    )
  );

  return $block;
}

/**
 * CCT hook_theme.
 */
function somi_user_wish_lists_content_type_theme(&$theme, $plugin) {
  $theme['somi_user_wish_lists'] = array(
    'variables' => array(
      'wish_lists' => [],
      'title' => '',
    ),
    'path' => $plugin['path'],
    'template' => 'somi-user-wish-lists',
  );
}
