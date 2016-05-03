<?php

/**
 * @file
 *
 * Custom session handlers to identify users by Bearer token.
 */

/**
 * Initializes global user.
 */
function drupal_session_initialize() {
  global $user;

  session_set_save_handler(
    '_drupal_session_open',
    '_drupal_session_close',
    '_drupal_session_read',
    '_drupal_session_write',
    '_drupal_session_destroy',
    '_drupal_session_garbage_collection'
  );

  $authorization = !empty($_SERVER['HTTP_X_API_AUTHORIZATION'])
                   ? explode(' ', $_SERVER['HTTP_X_API_AUTHORIZATION'])
                   : NULL;

  list($token_type, $access_token) = count($authorization) == 2
                                    ? $authorization
                                    : array('', '');

  if ($token_type == 'Bearer' && !empty($access_token)) {
    $session = db_select('sessions', 's')
        ->fields('s', array('uid'))
        ->condition('s.ssid', $access_token)
        ->execute()
        ->fetchObject();

    if ($session && ($account = api_user_load_by_uid($session->uid))) {
      if ($account->status = 1) {
        $user = $account;
      }
    }
  }

  if ($user && $user->uid > 0) {
    $user->roles = array();
    $user->roles[DRUPAL_AUTHENTICATED_RID] = 'authenticated user';
    $user->access_token = $access_token;
  }
  else {
    $user = drupal_anonymous_user();
    $user->access_token = NULL;
  }
}

function _drupal_session_open() {
  throw new ApiNotImplementedException('Handler is not implemented: ' . __FUNCTION__);
}

function _drupal_session_close() {
  throw new ApiNotImplementedException('Handler is not implemented: ' . __FUNCTION__);
}

function _drupal_session_read($sid) {
  throw new ApiNotImplementedException('Handler is not implemented: ' . __FUNCTION__);
}

function _drupal_session_write($sid, $value) {
  throw new ApiNotImplementedException('Handler is not implemented: ' . __FUNCTION__);
}

function drupal_session_start() {
  throw new ApiNotImplementedException('Handler is not implemented: ' . __FUNCTION__);
}

function drupal_session_commit() {
  throw new ApiNotImplementedException('Handler is not implemented: ' . __FUNCTION__);
}

function drupal_session_started($set = NULL) {
  throw new ApiNotImplementedException('Handler is not implemented: ' . __FUNCTION__);
}

function drupal_session_regenerate() {
  throw new ApiNotImplementedException('Handler is not implemented: ' . __FUNCTION__);
}

function _drupal_session_destroy($sid) {
  throw new ApiNotImplementedException('Handler is not implemented: ' . __FUNCTION__);
}

function drupal_session_destroy_uid($uid) {
  throw new ApiNotImplementedException('Handler is not implemented: ' . __FUNCTION__);
}

function drupal_save_session($status = NULL) {
  throw new ApiNotImplementedException('Handler is not implemented: ' . __FUNCTION__);
}

/**
 * Fork of includes/_drupal_session_garbage_collection()
 */
function _drupal_session_garbage_collection($lifetime) {
  db_delete('sessions')
    ->condition('timestamp', REQUEST_TIME - $lifetime, '<')
    ->execute();
  return TRUE;
}
