<?php

/**
 * @file
 *
 * Main API router.
 */

require_once('Exceptions.php');
define('API_PLATFORM_DRUPAL', 'DRUPAL');
// @todo: Later we need to detect this dynamically.
define('API_PLATFORM', API_PLATFORM_DRUPAL);

if (API_PLATFORM == API_PLATFORM_DRUPAL) {
  if (!defined('DRUPAL_ROOT')) {
    define('DRUPAL_ROOT', getcwd() . '/..');
  }
  define('API_ROOT', DRUPAL_ROOT . '/api');

  require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
  require_once DRUPAL_ROOT . '/includes/common.inc';
  require_once DRUPAL_ROOT . '/includes/module.inc';
  require_once DRUPAL_ROOT . '/includes/unicode.inc';
  require_once DRUPAL_ROOT . '/includes/file.inc';

  timer_start('api_call');

  drupal_bootstrap(DRUPAL_BOOTSTRAP_DATABASE);

  define('API_XHPROF_NAMESPACE', 'Api');
  _api_debug_xhprof_enable();
  _api_debug_queries_enable();

  // Prevent Devel from hi-jacking our output in any case (to save json format valid).
  $GLOBALS['devel_shutdown'] = FALSE;

  // Deactivate Drupal Error and Exception handling.
  restore_error_handler();
  restore_exception_handler();
  set_error_handler('api_error_handler');
}
elseif (API_PLATFORM == 'BITRIX') {
  define('API_ROOT', $_SERVER['DOCUMENT_ROOT'] . '/api');

  require_once(API_ROOT . '/includes/drupal-port.inc');

  timer_start('api_call');

  // Bootstrap Bitrix core on non-nested level.
  $include_path = $_SERVER['DOCUMENT_ROOT'] . '/bitrix/modules/main/include';
  require_once($include_path . '/prolog_before.php');
  if (!CModule::IncludeModule('iblock')) {
    throw new ApiException('Failed to load required iblock module.');
  }
}

// Indicator if request is failed.
$is_error = FALSE;
$callback_info = array();

try {
  if (!defined('API_ROOT')) {
    throw new ApiException('API root is undefined');
  }

  require_once(API_ROOT . '/api.php');

  $args = api_get_args();
  $callback_info = api_get_callback($args);
  $result = API_PLATFORM == API_PLATFORM_DRUPAL ? api_drupal_execute_callback($callback_info, $args) : api_bitrix_execute_callback($callback_info, $args);

  // General ETag/If-None-Match caching mechanism.
  if (!empty($callback_info['etag_enabled'])) {
    // 'W/' is mark of weak ETag to make it work with nginx.
    $etag = 'W/"' . md5(serialize($result)) . '"';

    if (!empty($_SERVER['HTTP_IF_NONE_MATCH']) && $etag === $_SERVER['HTTP_IF_NONE_MATCH']) {
      header($_SERVER['SERVER_PROTOCOL'] . ' 304 Not Modified');
      // @todo: Remove exit and integrate linear flow.
      exit();
    }
    else {
      header('ETag: ' . $etag);
    }
  }
}
catch (ApiAccessDeniedException $e) {
  api_set_is_error();
  // @todo: see drupal_add_http_header('Status', '403 Forbidden');
  header($_SERVER['SERVER_PROTOCOL'] . ' 403 Forbidden');
  $result = $e->getMessageForResponse();
}
catch (Exception $e) {
  $result = api_handle_prepare_error_response($e);
}

function api_set_is_error($status = TRUE) {
  $GLOBALS['is_error'] = $status;
}

function api_is_error() {
  return (bool) $GLOBALS['is_error'];
}

/**
 * @todo: Add logging of 500 errors.
 */
function api_handle_prepare_error_response(Exception $e) {
  api_set_is_error();

  api_syslog('debug', 'API4 exception:' . $e->getMessage());

  return array('error' => array('message' => $e->getMessage(), 'code' => (int) $e->getCode()));
}

$delivery = !empty($callback_info['delivery']) ? $callback_info['delivery'] : 'json';
if ($delivery === 'json') {
  // Validate structure of response for json delivery.
  if (!is_array($result) || isset($result['request_id'])) {
    $result = api_handle_prepare_error_response(new ApiException('Invalid API callback result', 34736));
  }
  else {
    try {
      $data = api_request_data();
    }
    catch (Exception $e) {
      $result = api_handle_prepare_error_response($e);
    }
    if (isset($data) && isset($data->request_id)) {
      $request_id = $data->request_id;
    }
  }

  // If we in error state - we should not convert response - it could be broken.
  if (!$is_error) {
    try {
      $result = api_convert_result($result, $callback_info);
    }
    catch (Exception $e) {
      $result = api_handle_prepare_error_response($e);
    }
  }

  // Debug cases to test API's behavior.
  if (!empty($_GET['debug_crash'])) {
    throw new Exception('Manual exception. debug_crash flag received.');
  }
  elseif (!empty($_GET['debug_time'])) {
    sleep(10);
  }
  elseif (!empty($_GET['debug_custom'])) {
    $result = api_handle_prepare_error_response(new ApiException('Manual error generated. debug_custom flag received', $_GET['debug_custom']));
  }

  // @todo: We need to move request ID logic to headers.
  if (isset($request_id)) {
    $result['request_id'] = $request_id;
  }
  // Add debug at the very end as it's needed even for errors.
  $result = api_provide_debug_data($result);

  $json = api_json_encode($result);
  // It we generate same response - do not return it, use empty object.
  // @todo: Implement ETag logic.
//  if (isset($data) && !empty($data->revision)) {
//    if ($data->revision == md5($json)) {
//      $json = api_json_encode(new stdClass());
//    }
//  }

  api_json_output($json);
}
// For now only html type as string supported.
elseif (is_string($result)) {
  print $result;
}

/**
 * Fork of js_execute_callback().
 */
function api_drupal_execute_callback($callback_info, $args) {
  // Define the callback function.
  $function = $callback_info['callback'];

  // If the callback function is located in another file, load that file now.
  if (isset($callback_info['file']) && ($filepath = SPAINT_API_MODULE_PATH . '/' . $callback_info['file'])) {
    if (!file_exists($filepath)) {
      throw new ApiException('API callback file not exists');
    }

    require_once $filepath;
  }

  // Validate the function existence of the defined callback.
  if (!function_exists($function)) {
    throw new ApiException("Invalid API callback: $function", 34735);
  }

  // Define session handler before any bootstrap action.
  if (!empty($callback_info['session handler'])) {
    $GLOBALS['conf']['session_inc'] = $callback_info['session handler'];
  }

  // Bootstrap to required level.
  $full_bootstrap = FALSE;
  if (!empty($callback_info['bootstrap'])) {
    drupal_bootstrap($callback_info['bootstrap']);
    $full_bootstrap = ($callback_info['bootstrap'] == DRUPAL_BOOTSTRAP_FULL);
  }

  if (!$full_bootstrap) {
    // The following mimics the behavior of _drupal_bootstrap_full().
    // The difference is that not all modules and includes are loaded.
    // @see _drupal_bootstrap_full().

    // Load required include files based on the callback.
    if (isset($callback_info['includes']) && is_array($callback_info['includes'])) {
      foreach ($callback_info['includes'] as $include) {
        if (file_exists("./includes/$include.inc")) {
          require_once "./includes/$include.inc";
        }
      }
    }

    // Detect string handling method.
    unicode_check();

    // Undo magic quotes.
    fix_gpc_magic();

    // To make stream wrappers work properly we need to fix path relative to API folder.
    $paths_to_fix = array('file_private_path', 'file_public_path', 'file_temporary_path');
    foreach ($paths_to_fix as $path_to_fix) {
      if (isset($GLOBALS['conf'][$path_to_fix])) {
        $GLOBALS['conf'][$path_to_fix] = '../' . ltrim($GLOBALS['conf'][$path_to_fix], '/');
      }
    }

    // Make sure all stream wrappers are registered.
    file_get_stream_wrappers();

    // Load required modules.
    $modules = array();
    if (isset($callback_info['dependencies']) && is_array($callback_info['dependencies'])) {
      foreach ($callback_info['dependencies'] as $dependency) {
        if (!drupal_load('module', $dependency)) {
          throw new ApiException('Wrong API callback dependency module specified');
        }
        $modules[$dependency] = 0;
      }
    }
    // Reset module list.
    module_list(FALSE, TRUE, FALSE, $modules);

    // Ensure the language variable is set, if not it might cause problems (e.g.
    // entity info).
    global $language;
    if (!isset($language)) {
      $language = language_default();
    }
  }

  // If access arguments are passed, boot to SESSION and validate if the user
  // has access to this callback.
  if (!empty($callback_info['access arguments']) || !empty($callback_info['access callback'])) {
    // Bootstrap to SESSION level unless if it already bootstrapped to higher level.
    // Also note, if we just call, it will not bootstrap, but final phase will change - it's wrong.
    if (drupal_bootstrap(NULL, FALSE) < DRUPAL_BOOTSTRAP_SESSION) {
      drupal_bootstrap(DRUPAL_BOOTSTRAP_SESSION);
    }

    // If no callback is provided, default to user_access.
    if (!isset($callback_info['access callback'])) {
      $callback_info['access callback'] = 'user_access';
    }

    if ($callback_info['access callback'] == 'user_access') {
      // Ensure the user module is available.
      drupal_load('module', 'user');
    }

    if ($callback_info['access callback'] !== TRUE) {
      $access_arguments = !empty($callback_info['access arguments'])
        ? $callback_info['access arguments']
        : array();
      if (!call_user_func_array($callback_info['access callback'], $access_arguments)) {
        throw new ApiAccessDeniedException('Access denied for endpoint:' . $callback_info['key'] . ' access callback:' . $callback_info['access callback'] . ' cookies:' . json_encode($_COOKIE));
      }
    }
  }

  // Invoke implementations of hook_init() if the callback doesn't indicate it
  // should be skipped.
  if (!$full_bootstrap && empty($callback_info['skip_hook_init'])) {
    module_invoke_all('init');
  }

  // If there are page arguments defined add them to the callback call.
  if (isset($callback_info['page arguments'])) {
    // Overwrite the arguments
    $args = array_intersect_key($args, array_flip($callback_info['page arguments']));
  }

  // Call init callback right before actual callback to apply general logic.
  if (!empty($callback_info['init callback'])) {
    if (!function_exists($callback_info['init callback'])) {
      throw new ApiException('API init callback could not be found: ' . $callback_info['init callback']);
    }
    call_user_func($callback_info['init callback']);
  }

  // Invoke callback function.
  return call_user_func_array($function, $args);
}

/**
 * Callback executor.
 */
function api_bitrix_execute_callback($callback_info, $args) {
  if (!empty($callback_info['access callback'])) {
    $access_args = !empty($callback_info['access arguments'])
      ? array_intersect_key($args, array_flip($callback_info['access arguments']))
      : array();
    $access_granted = call_user_func_array($callback_info['access callback'], $access_args);
    if (!$access_granted) {
      throw new ApiAccessDeniedException('Access denied for this action');
    }
  }

  // Define the callback function.
  $function = $callback_info['callback'];

  // If the callback function is located in another file, load that file now.
  if (!empty($callback_info['file']) && ($file_path = API_ROOT . '/' . $callback_info['file'])) {
    if (!file_exists($file_path)) {
      throw new ApiException('API callback file not exists');
    }

    require_once $file_path;
  }

  // Validate the function existence of the defined callback.
  if (!function_exists($function)) {
    throw new ApiException("Invalid API callback: $function", 34735);
  }

  // If there are arguments defined add them to the callback call.
  $page_args = array();
  if (!empty($callback_info['arguments'])) {
    // Overwrite the arguments
    $page_args = array_intersect_key($args, array_flip($callback_info['arguments']));
  }

  // Invoke callback function.
  return call_user_func_array($function, $page_args);
}

/**
 * Fetch input data from any type of request.
 *
 * @throws ApiInvalidJsonException
 */
function api_request_data() {
  static $static;

  if (!isset($static)) {
    if (isset($_SERVER['CONTENT_TYPE']) && (strpos($_SERVER['CONTENT_TYPE'], 'application/json') !== FALSE)) {
      $static = (object) json_decode(file_get_contents('php://input'), FALSE);
      if (json_last_error()) {
        throw new ApiInvalidJsonException('Invalid input JSON format');
      }
    }
    elseif (!empty($_POST['data'])) {
      $static = json_decode(urldecode($_POST['data']), FALSE);
      if (json_last_error()) {
        throw new ApiInvalidJsonException('Invalid input JSON format');
      }
    }
    elseif (!empty($_GET)) {
      $data = $_GET;
      if (isset($data['q'])) {
        unset($data['q']);
      }
      $static = (object) $data;
    }
    else {
      $static = new stdClass();
    }

    if (!empty($GLOBALS['api_version'])) {
      $static->api_version = $GLOBALS['api_version'];
    }

    // Get param for GET has the highest priority.
    if (!empty($_GET['request_id'])) {
      $static->request_id = $_GET['request_id'];
    }
  }

  // Log incoming data to debug on client side.
  if (!empty($_GET['debug'])) {
    $GLOBALS['api_debug']['request_data'] = $static;
  }

  return $static;
}

/**
 * Filter args to pass to callback.
 */
function api_get_args() {
  $query = isset($_GET['q']) ? $_GET['q'] : '';
  // Consider only URL without get params.
  // @todo: ???
  $query = parse_url($query, PHP_URL_PATH);

  $args = explode('/', $query);

  // @todo: Normally we need to move it at level upper to fill global options and pass only real args here.
  // Skip language from args, if needed it will be passed as
  if (!empty($args[0]) && in_array($args[0], array('en', 'ru'), TRUE)) {
    array_shift($args);
  }

  // Strip first argument 'api' prefix.
  if (!empty($args[0]) && strpos($args[0], 'api') === 0) {
    array_shift($args);
  }

  // Check API version in format api/v1/..., etc.
  if (!empty($args[0]) && strpos($args[0], 'v') === 0) {
    $GLOBALS['api_version'] = array_shift($args);
  }
  else {
    throw new ApiException('API version is not specified');
  }

  return $args;
}

/**
 * Find out relevant API callback.
 */
function api_get_callback($args) {
  // Get info hook function name.
  $callbacks_hook = 'api_methods';
  if (!function_exists($callbacks_hook)) {
    throw new ApiException('Callback hook function is missed');
  }

  $callbacks = $callbacks_hook();

  // Lookup for a direct match.
  $current_path_parts = array_merge($args, array(strtolower($_SERVER['REQUEST_METHOD'])));
  $current_path = implode('/', $current_path_parts);
  $callback_info = $callback_path = FALSE;
  foreach ($callbacks as $suggestion_path => $info) {
    if ($suggestion_path === $current_path) {
      $callback_path = $suggestion_path;
      $callback_info = $info;
      break;
    }
  }

  // If there is no direct match — try find a callback with placeholders.
  if (!$callback_info) {
    foreach ($callbacks as $suggestion_path => $info) {
      if (api_get_is_matched_callback($current_path_parts, $suggestion_path)) {
        $callback_path = $suggestion_path;
        $callback_info = $info;
        break;
      }
    }
  }

  // If there is still no callback found, the last chance is
  // to find callback starting with our request string (i.e. take a/b/c for a/b/c/d path).
  if (!$callback_info) {
    // Make sure if we trying to find most long string.
    // If we have both a/b and a/b/c, when we looking for a/b/c/d, a/b/c is more relevant.
    $keys = array_map('strlen', array_keys($callbacks));
    array_multisort($keys, SORT_DESC, $callbacks);
    foreach ($callbacks as $suggestion_path => $info) {
      if (api_get_is_matched_callback($current_path_parts, $suggestion_path, FALSE)) {
        $callback_path = $suggestion_path;
        $callback_info = $info;
        break;
      }
    }
  }

  if (empty($callback_info)) {
    throw new ApiException('API callback info is missed for args: ' . $current_path);
  }

  if (empty($callback_info['callback'])) {
    throw new ApiException('API callback function is missed for key: ' . $callback_path);
  }

  $callback_info['key'] = $callback_path;
  return $callback_info;
}

/**
 * Check if suggestion matched to current request
 *
 * @param array $current_path_parts
 * @param string $suggestion_path
 * @param bool|FALSE $strict_match
 *   For strict only full match return TRUE.
 *   Else if suggestion path string starts with current request string and methods are same.
 *
 * @return bool
 */
function api_get_is_matched_callback($current_path_parts, $suggestion_path, $strict_match = TRUE) {
  $suggestion_parts = explode('/', $suggestion_path);
  $tmp_parts = $current_path_parts;
  foreach ($suggestion_parts as $key => $part) {
    if (strpos($part, '%') === 0 && array_key_exists($key, $tmp_parts)) {
      $tmp_parts[$key] = $part;
    }
  }

  if ($strict_match) {
    return $suggestion_parts === $tmp_parts;
  }
  else {
    $current_method = array_pop($tmp_parts);
    $suggestion_method = array_pop($suggestion_parts);
    return $current_method === $suggestion_method && strpos(implode('/', $tmp_parts), implode('/', $suggestion_parts)) === 0;
  }
}

/**
 * Convert results into proper data types: string as is, numbers as int, bool as bool.
 *
 * @return array
 * @throws ApiException
 */
function api_convert_result($result, $callback_info) {
  $api_schema_filepath = api_get_schema_filepath();
  if (!$api_schema_filepath) {
    throw new ApiException('File with API format description is missed');
  }
  $api_format = api_json_decode(file_get_contents($api_schema_filepath));

  if (!$api_format) {
    throw new ApiException('Api description is invalid.');
  }

  if (!isset($api_format[$callback_info['key']])) {
    throw new ApiException('Missed api description for key: ' . $callback_info['key']);
  }

  $schema = FALSE;
  $callback_api_format = $api_format[$callback_info['key']];
  switch ($callback_api_format['type']) {
    case 'regular':
      $schema = $callback_api_format['schema'];
      break;

    case 'copy':
      if (!empty($callback_api_format['original']) && array_key_exists($callback_api_format['original'], $api_format)) {
        $schema = $api_format[$callback_api_format['original']]['schema'];
      }
      break;
  }

  if (empty($schema)) {
    throw new ApiException('Missed API schema definition');
  }

  return api_convert_result_item($schema, $result);
}

/**
 * Recursively convert result data to proper types.
 */
function api_convert_result_item($item, $result, $key_name = '') {
  if (!isset($item['type'])) {
    throw new ApiException("Missed type in: " . api_json_encode($item));
  }
  switch ($item['type']) {
    case 'object':
      if (!is_array($result)) {
        throw new ApiException("Non-array value passed to '" . $key_name . "' property: " . api_json_encode($result));
      }

      $new_result = array();
      $diff = array_diff(array_keys($result), array_keys($item['properties']));
      // @todo: Recheck this case.
      if (!empty($diff)) {
        throw new ApiException(
          "Missed API response schema for: '" . $key_name . "'. Keys: " . implode(', ', $diff) . '. Data: ' . api_json_encode($result)
        );
      }
      foreach ($item['properties'] as $property_name => $property_info) {
        // Check if all non-optional properties exists.
        if (!isset($result[$property_name]) && empty($property_info['optional'])) {
          throw new ApiException("Required property '" . $property_name . "' is missed in " . api_json_encode($result));
        }
        if (isset($result[$property_name])) {
          $new_result[$property_name] = api_convert_result_item($property_info, $result[$property_name], $property_name);
        }
      }
      return $new_result;

    case 'array':
      $new_result = array();
      foreach ($result as $result_item) {
        $new_result[] = api_convert_result_item($item['items'], $result_item, $key_name);
      }
      return $new_result;

    case 'string':
      return strval($result);

    case 'number':
      return strpos($result, '.') === FALSE ? intval($result) : floatval($result);

    case 'boolean':
      return (bool) $result;

    default:
      throw new ApiException("Unknown result item data type '" . $item['type'] . "' for: " . api_json_encode($result));
  }
}

/**
 * @group
 *
 * Debug functions section.
 */

/**
 * Add debug data to response.
 */
function api_provide_debug_data($result) {
  // Add debug info in any case, even if we in error.
  if (!empty($_GET['debug'])) {
    if (!function_exists('getallheaders')) {
      function getallheaders() {
        $headers = '';
        foreach ($_SERVER as $name => $value) {
          if (substr($name, 0, 5) === 'HTTP_') {
            $headers[str_replace(' ', '-', ucwords(strtolower(str_replace('_', ' ', substr($name, 5)))))] = $value;
          }
        }
        return $headers;
      }
    }

    $result['debug']['headers'] = getallheaders();
    $result['debug']['current_uid'] = intval($GLOBALS['user']->uid);
    $time = timer_stop('api_call');
    $result['debug']['time'] = $time['time'];
    if (!empty($GLOBALS['api_debug']) && is_array($GLOBALS['api_debug'])) {
      $result['debug'] = array_merge($result['debug'], $GLOBALS['api_debug']);
    }

    if (function_exists('_api_debug_xhprof_data') && $xhprof_debug = _api_debug_xhprof_data()) {
      $result['debug']['xhprof'] = $xhprof_debug;
    }

    if (function_exists('_api_debug_queries_data') && $queries_debug = _api_debug_queries_data()) {
      $result['debug']['queries'] = $queries_debug;
    }
  }

  return $result;
}

/**
 * Check if we need to start xhprof profiling.
 */
function _api_debug_is_xhprof_enabled($check_ext = TRUE) {
  return !empty($_GET['debug']) && !empty($_GET['xhprof_enabled']) && (!$check_ext || extension_loaded('xhprof'));
}

/**
 * Start profiling if possible.
 */
function _api_debug_xhprof_enable() {
  if (_api_debug_is_xhprof_enabled()) {
    if ($path = variable_get('devel_xhprof_directory', '')) {
      include_once $path . '/xhprof_lib/utils/xhprof_lib.php';
      include_once $path . '/xhprof_lib/utils/xhprof_runs.php';
      xhprof_enable(XHPROF_FLAGS_CPU + XHPROF_FLAGS_MEMORY);
    }
  }
}

/**
 * End profiling.
 */
function _api_debug_xhprof_shutdown() {
  if (_api_debug_is_xhprof_enabled()) {
    $xhprof_data = xhprof_disable();
    $xhprof_runs = new XHProfRuns_Default();
    return $xhprof_runs->save_run($xhprof_data, API_XHPROF_NAMESPACE);
  }
  return FALSE;
}

/**
 * Get link or status about profiling.
 */
function _api_debug_xhprof_data() {
  // Check without extension to get proper error.
  if (_api_debug_is_xhprof_enabled(FALSE)) {
    if (!extension_loaded('xhprof')) {
      return 'No extension loaded';
    }
    elseif (!variable_get('devel_xhprof_url', '')) {
      return 'Missed XHProf URL';
    }
    elseif (!variable_get('devel_xhprof_directory', '')) {
      return 'Missed XHProf logs directory path';
    }
    elseif ($run_id = _api_debug_xhprof_shutdown()) {
      return variable_get('devel_xhprof_url', '') . "/index.php?run=$run_id&source=" . API_XHPROF_NAMESPACE;
    }
  }
  return FALSE;
}

/**
 * Check if logging enabled.
 */
function _api_debug_is_queries_enabled() {
  return !empty($_GET['debug']) && !empty($_GET['queries_enabled']);
}

/**
 * Start logging.
 */
function _api_debug_queries_enable() {
  if (_api_debug_is_queries_enabled()) {
    @include_once DRUPAL_ROOT . '/includes/database/log.inc';
    Database::startLog('api');
  }
}

/**
 * Get queries data.
 */
function _api_debug_queries_data() {
  $output = array();
  if (_api_debug_is_queries_enabled()) {
    $queries = Database::getLog('api', 'default');
    foreach ($queries as $query) {
      $output[] = $query['query'] . ' Time: ' . round($query['time'] * 1000, 2) . ' ms.';
    }
  }

  return $output;
}

/**
 * @group
 *
 * API utils backport.
 */
function api_json_encode($var) {
  return json_encode($var, JSON_HEX_TAG | JSON_HEX_APOS | JSON_HEX_AMP | JSON_HEX_QUOT);
}

function api_json_decode($var) {
  return json_decode($var, TRUE);
}

function api_json_output($json = NULL) {
  // We are returning JSON, so tell the browser.
  header('Content-Type: application/json; charset=utf8', TRUE);

  if (isset($json)) {
    echo $json;
  }
}

/**
 * Stub for logger.
 */
function api_syslog($type, $message) {

}
