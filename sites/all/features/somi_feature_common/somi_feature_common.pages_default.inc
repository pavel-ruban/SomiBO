<?php
/**
 * @file
 * somi_feature_common.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function somi_feature_common_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'site_template__panel_context_446f2726-dc74-4a3e-9dd0-ee3b37be2736';
  $handler->task = 'site_template';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Common',
    'no_blocks' => 1,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'access' => array(
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'one_main' => NULL,
      'top' => NULL,
      'left' => NULL,
      'middle' => NULL,
      'right' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '3d246d3f-c18e-4134-835e-934fc3fa9f7f';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-92c86403-a6aa-4200-9580-14d2925a396d';
    $pane->panel = 'middle';
    $pane->type = 'somi_header';
    $pane->subtype = 'somi_header';
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
    $pane->uuid = '92c86403-a6aa-4200-9580-14d2925a396d';
    $display->content['new-92c86403-a6aa-4200-9580-14d2925a396d'] = $pane;
    $display->panels['middle'][0] = 'new-92c86403-a6aa-4200-9580-14d2925a396d';
    $pane = new stdClass();
    $pane->pid = 'new-bc977508-d131-493f-8319-d81253567453';
    $pane->panel = 'middle';
    $pane->type = 'page_content';
    $pane->subtype = 'page_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_page_content_1',
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'bc977508-d131-493f-8319-d81253567453';
    $display->content['new-bc977508-d131-493f-8319-d81253567453'] = $pane;
    $display->panels['middle'][1] = 'new-bc977508-d131-493f-8319-d81253567453';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['site_template__panel_context_446f2726-dc74-4a3e-9dd0-ee3b37be2736'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function somi_feature_common_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'account_details';
  $page->task = 'page';
  $page->admin_title = 'Account details';
  $page->admin_description = '';
  $page->path = 'admin/user/%uid/account/!currency_tid';
  $page->access = array(
    'logic' => 'and',
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'none',
    'title' => '',
    'name' => 'navigation',
    'weight' => '0',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array(
    'uid' => array(
      'id' => 1,
      'identifier' => 'User: ID',
      'name' => 'entity_id:user',
      'settings' => array(),
    ),
    'currency_tid' => array(
      'id' => 1,
      'identifier' => 'String',
      'name' => 'string',
      'settings' => array(
        'use_tail' => 0,
      ),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_account_details__panel_context_3e1add34-091f-45f4-806e-20c38ecfbf10';
  $handler->task = 'page';
  $handler->subtask = 'account_details';
  $handler->handler = 'panel_context';
  $handler->weight = 1;
  $handler->conf = array(
    'title' => 'Данные счёта пользователя',
    'no_blocks' => 1,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
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
  $display->title = '';
  $display->uuid = '32dc962b-612b-43dc-9cbb-134436ea0b47';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-0bc38835-f088-4ea0-8bec-0060cfee0468';
    $pane->panel = 'middle';
    $pane->type = 'somi_user_account_data';
    $pane->subtype = 'somi_user_account_data';
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
    $pane->uuid = '0bc38835-f088-4ea0-8bec-0060cfee0468';
    $display->content['new-0bc38835-f088-4ea0-8bec-0060cfee0468'] = $pane;
    $display->panels['middle'][0] = 'new-0bc38835-f088-4ea0-8bec-0060cfee0468';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['account_details'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'account_events';
  $page->task = 'page';
  $page->admin_title = 'Последние операции';
  $page->admin_description = '';
  $page->path = 'admin/content/accounts/events';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'role',
        'settings' => array(
          'rids' => array(
            0 => 2,
          ),
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
    'type' => 'none',
    'settings' => NULL,
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
  $handler->name = 'page_account_events__panel';
  $handler->task = 'page';
  $handler->subtask = 'account_events';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Последние события',
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
  $display->title = 'Последние события';
  $display->uuid = '06bf0622-90b3-441f-b8e3-826c7224d36e';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-0739ecd2-4114-450d-b16c-2c7e67550d24';
    $pane->panel = 'middle';
    $pane->type = 'somi_user_recent_account_events';
    $pane->subtype = 'somi_user_recent_account_events';
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
    $pane->uuid = '0739ecd2-4114-450d-b16c-2c7e67550d24';
    $display->content['new-0739ecd2-4114-450d-b16c-2c7e67550d24'] = $pane;
    $display->panels['middle'][0] = 'new-0739ecd2-4114-450d-b16c-2c7e67550d24';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-0739ecd2-4114-450d-b16c-2c7e67550d24';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['account_events'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'crystalls_log';
  $page->task = 'page';
  $page->admin_title = 'Crystalls Log';
  $page->admin_description = '';
  $page->path = 'user/%uid/crystalls';
  $page->access = array(
    'logic' => 'and',
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'none',
    'title' => '',
    'name' => 'navigation',
    'weight' => '0',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array(
    'uid' => array(
      'id' => 1,
      'identifier' => 'User: ID',
      'name' => 'entity_id:user',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_crystalls_log__panel';
  $handler->task = 'page';
  $handler->subtask = 'crystalls_log';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Crystalls Log',
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
  $display->title = '';
  $display->uuid = '0643320f-9ac9-4c16-b72d-8de78c0669e4';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-188c5b4e-ef6a-494c-acc5-5724c5f41561';
    $pane->panel = 'middle';
    $pane->type = 'somi_user_crystalls_log';
    $pane->subtype = 'somi_user_crystalls_log';
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
    $pane->uuid = '188c5b4e-ef6a-494c-acc5-5724c5f41561';
    $display->content['new-188c5b4e-ef6a-494c-acc5-5724c5f41561'] = $pane;
    $display->panels['middle'][0] = 'new-188c5b4e-ef6a-494c-acc5-5724c5f41561';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-188c5b4e-ef6a-494c-acc5-5724c5f41561';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['crystalls_log'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'home_page';
  $page->task = 'page';
  $page->admin_title = 'Home page';
  $page->admin_description = '';
  $page->path = 'home';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
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
  $handler->name = 'page_home_page__panel';
  $handler->task = 'page';
  $handler->subtask = 'home_page';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
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
      'one_main' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'e2851a78-cb04-4a6c-8971-cc5f92d48dc4';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-64b32a55-1ac7-44bb-8049-bf39a73204df';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'users-users';
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
    $pane->uuid = '64b32a55-1ac7-44bb-8049-bf39a73204df';
    $display->content['new-64b32a55-1ac7-44bb-8049-bf39a73204df'] = $pane;
    $display->panels['middle'][0] = 'new-64b32a55-1ac7-44bb-8049-bf39a73204df';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['home_page'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'somi_availability';
  $page->task = 'page';
  $page->admin_title = 'Somi Availability';
  $page->admin_description = '';
  $page->path = 'admin/somi/availability';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'perm',
        'settings' => array(
          'perm' => 'access somi availability',
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
    'type' => 'none',
    'settings' => NULL,
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
  $handler->name = 'page_somi_availability__panel';
  $handler->task = 'page';
  $handler->subtask = 'somi_availability';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Somi Availability',
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
  $display->title = 'SOMI Активность Персонала';
  $display->uuid = 'df551cb6-de88-408f-9ebc-4b9a168dd337';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-b193e4a6-19e0-4a86-9f2a-51050ab9996b';
    $pane->panel = 'middle';
    $pane->type = 'somi_availability';
    $pane->subtype = 'somi_availability';
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
    $pane->uuid = 'b193e4a6-19e0-4a86-9f2a-51050ab9996b';
    $display->content['new-b193e4a6-19e0-4a86-9f2a-51050ab9996b'] = $pane;
    $display->panels['middle'][0] = 'new-b193e4a6-19e0-4a86-9f2a-51050ab9996b';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-b193e4a6-19e0-4a86-9f2a-51050ab9996b';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['somi_availability'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'somi_charts';
  $page->task = 'page';
  $page->admin_title = 'Somi Charts';
  $page->admin_description = '';
  $page->path = 'admin/somi/chart';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'perm',
        'settings' => array(
          'perm' => 'access somi logs',
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
    'type' => 'none',
    'settings' => NULL,
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
  $handler->name = 'page_somi_charts__panel';
  $handler->task = 'page';
  $handler->subtask = 'somi_charts';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
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
  $display->title = 'SOMI Графики';
  $display->uuid = '89b7f09b-3931-4615-b1ed-1dc9e3b21b6f';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-b4b05327-4b16-4735-9479-edd25689dc25';
    $pane->panel = 'middle';
    $pane->type = 'somi_logs';
    $pane->subtype = 'somi_logs';
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
    $pane->uuid = 'b4b05327-4b16-4735-9479-edd25689dc25';
    $display->content['new-b4b05327-4b16-4735-9479-edd25689dc25'] = $pane;
    $display->panels['middle'][0] = 'new-b4b05327-4b16-4735-9479-edd25689dc25';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-b4b05327-4b16-4735-9479-edd25689dc25';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['somi_charts'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'somi_crystals_winner';
  $page->task = 'page';
  $page->admin_title = 'Somi Crystals Winner';
  $page->admin_description = '';
  $page->path = 'admin/somi/crystal-winner';
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
  $handler->name = 'page_somi_crystals_winner__panel';
  $handler->task = 'page';
  $handler->subtask = 'somi_crystals_winner';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Somi Crystal Winner',
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
  $display->title = 'Доска награждений';
  $display->uuid = '2a308a35-be27-49e7-be9e-8ad12c45378f';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-61303143-205a-49b0-be03-4bccbe90d18e';
    $pane->panel = 'middle';
    $pane->type = 'somi_crystal_winner';
    $pane->subtype = 'somi_crystal_winner';
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
    $pane->uuid = '61303143-205a-49b0-be03-4bccbe90d18e';
    $display->content['new-61303143-205a-49b0-be03-4bccbe90d18e'] = $pane;
    $display->panels['middle'][0] = 'new-61303143-205a-49b0-be03-4bccbe90d18e';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-61303143-205a-49b0-be03-4bccbe90d18e';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['somi_crystals_winner'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'somi_logs';
  $page->task = 'page';
  $page->admin_title = 'SOMI Logs';
  $page->admin_description = '';
  $page->path = 'somi-logs';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
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
  $handler->name = 'page_somi_logs__panel';
  $handler->task = 'page';
  $handler->subtask = 'somi_logs';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'SOMI Logs',
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
  $display->title = '';
  $display->uuid = 'aa9f94a9-e714-44f4-960c-61f794d52916';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-8ee4e8d2-e281-4bb2-9c9c-03b8bf2921ca';
    $pane->panel = 'middle';
    $pane->type = 'somi_logs';
    $pane->subtype = 'somi_logs';
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
    $pane->uuid = '8ee4e8d2-e281-4bb2-9c9c-03b8bf2921ca';
    $display->content['new-8ee4e8d2-e281-4bb2-9c9c-03b8bf2921ca'] = $pane;
    $display->panels['middle'][0] = 'new-8ee4e8d2-e281-4bb2-9c9c-03b8bf2921ca';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-8ee4e8d2-e281-4bb2-9c9c-03b8bf2921ca';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['somi_logs'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'somi_score_board';
  $page->task = 'page';
  $page->admin_title = 'Somi Score Board';
  $page->admin_description = '';
  $page->path = 'admin/somi/score-board';
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
    'type' => 'none',
    'settings' => NULL,
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
  $handler->name = 'page_somi_score_board__panel';
  $handler->task = 'page';
  $handler->subtask = 'somi_score_board';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Somi Score Board',
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
  $display->uuid = '16b884d1-ed21-49be-bf44-0d2c65de1ccb';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-34206006-419b-4fd5-812f-5ac8b3ded1f8';
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
    $pane->uuid = '34206006-419b-4fd5-812f-5ac8b3ded1f8';
    $display->content['new-34206006-419b-4fd5-812f-5ac8b3ded1f8'] = $pane;
    $display->panels['middle'][0] = 'new-34206006-419b-4fd5-812f-5ac8b3ded1f8';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-34206006-419b-4fd5-812f-5ac8b3ded1f8';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['somi_score_board'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'somi_user_chart';
  $page->task = 'page';
  $page->admin_title = 'Somi User Chart';
  $page->admin_description = '';
  $page->path = 'admin/somi/chart/%uid';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'perm',
        'settings' => array(
          'perm' => 'access somi logs',
        ),
        'context' => 'argument_entity_id:user_1',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array(
    'uid' => array(
      'id' => 1,
      'identifier' => 'String',
      'name' => 'string',
      'settings' => array(
        'use_tail' => 0,
      ),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_somi_user_chart__panel';
  $handler->task = 'page';
  $handler->subtask = 'somi_user_chart';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Somi User Chart',
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
  $display->title = 'SOMI График Пользователя';
  $display->uuid = '3b97a63d-7bfa-4dfc-84b5-174b732ad29a';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-36740365-31ea-4554-acea-ef9a4c8f63ea';
    $pane->panel = 'middle';
    $pane->type = 'somi_user_logs';
    $pane->subtype = 'somi_user_logs';
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
    $pane->uuid = '36740365-31ea-4554-acea-ef9a4c8f63ea';
    $display->content['new-36740365-31ea-4554-acea-ef9a4c8f63ea'] = $pane;
    $display->panels['middle'][0] = 'new-36740365-31ea-4554-acea-ef9a4c8f63ea';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-36740365-31ea-4554-acea-ef9a4c8f63ea';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['somi_user_chart'] = $page;

  return $pages;

}
