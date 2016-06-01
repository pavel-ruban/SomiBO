<?php
/**
 * @file
 * somi_feature_vocabularies_content_types.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function somi_feature_vocabularies_content_types_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'score_board';
  $page->task = 'page';
  $page->admin_title = 'Score Board';
  $page->admin_description = '';
  $page->path = 'admin/somi/score_board';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'perm',
        'settings' => array(
          'perm' => 'access somi winner boards',
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_score_board__panel';
  $handler->task = 'page';
  $handler->subtask = 'score_board';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Score Board',
    'no_blocks' => 1,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'panel',
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Score Board';
  $display->uuid = '34904147-61e6-4a26-99b2-c31ffa19ff9c';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-32f8e027-f51b-49a9-bc86-7b4c9b0f30e5';
    $pane->panel = 'middle';
    $pane->type = 'somi_score_board';
    $pane->subtype = 'somi_score_board';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '32f8e027-f51b-49a9-bc86-7b4c9b0f30e5';
    $display->content['new-32f8e027-f51b-49a9-bc86-7b4c9b0f30e5'] = $pane;
    $display->panels['middle'][0] = 'new-32f8e027-f51b-49a9-bc86-7b4c9b0f30e5';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-32f8e027-f51b-49a9-bc86-7b4c9b0f30e5';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['score_board'] = $page;

  return $pages;

}
