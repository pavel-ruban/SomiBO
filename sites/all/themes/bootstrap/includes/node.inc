<?php

/**
 * @file
 */

/**
 * Override or insert variables into the node template.
 */
function bootstrap_preprocess_node(&$vars, $hook) {
  if ($vars['view_mode'] == 'full' && node_is_page($vars['node'])) {
    $vars['classes_array'][] = 'node-full';
  }

  $node = $vars['node'];
  $build_mode_for_preprocess = str_replace('-', '_', $vars['view_mode']);

  $vars['theme_hook_suggestions'][] = 'node__' . $vars['view_mode'];
  $vars['theme_hook_suggestions'][] = 'node__' . $node->type . '_' . $vars['view_mode'];

  // Defines the priority of calling preprocess fuctions for specific nodetype & build
  // modes.
  // Note: priority is calculated in reverse mode.
  $preprocess = array(
    'bootstrap_preprocess_node__' . $node->type,
    'bootstrap_preprocess_node__' . $build_mode_for_preprocess,
    'bootstrap_preprocess_node__' . $node->type . '_' . $build_mode_for_preprocess,
  );

  foreach (array_reverse($preprocess) as $function) {
    if (function_exists($function)) {
      $function($vars, $hook);
      break;
    }
  }
}