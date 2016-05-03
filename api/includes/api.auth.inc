<?php

/**
 * @file
 *
 * API Logic about auth actions.
 */

define('API_TOKEN_REFRESH_BYTES', 128);
define('API_TOKEN_ACCESS_BYTES', 64);

define('API_USER_NAME_LENGTH', defined('USERNAME_MAX_LENGTH') ? USERNAME_MAX_LENGTH : 60);

define('API_USER_DEFAULT_EMAIL_DOMAIN', 'api.local');
define('API_USER_PASSWORD_LENGTH', 32);
define('API_USER_PASSWORD_HASH_COUNT', 10);
define('API_USER_SECRET_KEY', '4e7514f23654648558d469d7261e47ff74ab213db86dec8f133ea7dfde7f02be');

/**
 * Fork of user_is_logged_in().
 *
 * @see user_is_logged_in()
 */
function api_user_is_logged_in() {
  return (bool) $GLOBALS['user']->uid;
}

/**
 * Fork of user_is_anonymous().
 *
 * @see user_is_anonymous()
 */
function api_user_is_anonymous() {
  return !api_user_is_logged_in();
}

/**
 * Create user entity during registration.
 */
function api_user_create($name, $email, $password, $language) {
  if (!$name || !valid_email_address($email) || !$password) {
    throw new ApiAuthException('Missed required parameter during account creation', 35865);
  }

  require_once DRUPAL_ROOT . '/includes/password.inc';
  $uid = db_next_id(db_query('SELECT MAX(uid) FROM {users}')->fetchField());
  db_insert('users')
    ->fields(array(
        'uid' => $uid,
        'name' => $email,
        'display_name' => $name,
        'pass' => user_hash_password($password, API_USER_PASSWORD_HASH_COUNT),
        'mail' => $email,
        'init' => $email,
        'status' => 1,
        'created' => REQUEST_TIME,
        'refresh_token' => api_user_refresh_token(),
        'language' => $language,
      )
    )
    ->execute();

  $account = api_user_load_by_uid($uid);
  $account->new_user = TRUE;

  return $account;
}

/**
 * Prepare user name either of social data name or email.
 */
function api_user_name($prefix, $id, $name, $email) {
  if (!$name && $email) {
    $parts = explode('@', $email);
    if (count($parts) == 2) {
      $name = $parts[0];
    }
  }

  if (!$name || !api_user_validate_name($name)) {
    $name = "u{$prefix}{$id}";
  }

  return $name;
}

/**
 * Fork of user_validate_name().
 *
 * @param $name
 *
 * @return bool
 *
 * @see user_validate_name()
 */
function api_user_validate_name($name) {
  if (!$name) {
    return FALSE;
  }
  if (preg_match('/[^\x{80}-\x{F7} a-z0-9@_.\'-]/i', $name)) {
    return FALSE;
  }
  if (preg_match('/[\x{80}-\x{A0}' .         // Non-printable ISO-8859-1 + NBSP
    '\x{AD}' .                // Soft-hyphen
    '\x{2000}-\x{200F}' .     // Various space characters
    '\x{2028}-\x{202F}' .     // Bidirectional text overrides
    '\x{205F}-\x{206F}' .     // Various text hinting characters
    '\x{FEFF}' .              // Byte order mark
    '\x{FF01}-\x{FF60}' .     // Full-width latin
    '\x{FFF9}-\x{FFFD}' .     // Replacement characters
    '\x{0}-\x{1F}]/u',        // NULL byte and control characters
    $name)) {

    return FALSE;
  }
  if (drupal_strlen($name) > API_USER_NAME_LENGTH) {
    return FALSE;
  }

  return TRUE;
}

/**
 * Helper to get account record for user.
 */
function _api_user_load_account($uid, $fields) {
  return db_select('users', 'u')
    ->fields('u', $fields)
    ->condition('uid', $uid)
    ->execute()
    ->fetchObject();
}

/**
 * @param $email
 *
 * @return object
 */
function api_user_load_by_email($email) {
  $account = db_select('users', 'u')
    ->fields('u', [])
    ->condition('mail', $email)
    ->execute()
    ->fetchObject();

  return _api_user_fix($account);
}

/**
 * @param $secret_key
 * @return bool|null|object
 */
function api_user_load_by_secret_key($secret_key) {
  if (hash('sha256', $secret_key) == API_USER_SECRET_KEY) {
    $account = db_select('users', 'u')
      ->fields('u', [])
      ->condition('uid', 1)
      ->execute()
      ->fetchObject();

    return _api_user_fix($account);
  }
  else {
    return FALSE;
  }
}

/**
 * Get account object by phone.
 *
 * @param string $phone
 *
 * @return \stdClass|FALSE
 */
function api_user_load_by_phone($phone) {
  drupal_load('module', 'field');
  drupal_load('module', 'field_sql_storage');
  require_once DRUPAL_ROOT . '/includes/entity.inc';

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'user', '=');
  $query->fieldCondition('field_phone_number', 'value', $phone);
  $result = $query->execute();

  $account = FALSE;
  if (!empty($result['user'])) {
    $uid = key($result['user']);
    drupal_load('module', 'user');
    $account = user_load($uid);

    $name_parts = [];
    if (!empty($account->field_first_name[LANGUAGE_NONE][0]['value'])) {
      $name_parts[] = $account->field_first_name[LANGUAGE_NONE][0]['value'];
    }
    if (!empty($account->field_last_name[LANGUAGE_NONE][0]['value'])) {
      $name_parts[] = $account->field_last_name[LANGUAGE_NONE][0]['value'];
    }

    if ($name_parts) {
      $account->display_name = implode(' ', $name_parts);
    }
  }

  return _api_user_fix($account);
}

/**
 * @param $refresh_token
 *
 * @return null|object
 */
function api_user_load_by_refresh_token($refresh_token) {
  $account = db_select('users', 'u')
    ->fields('u', [])
    ->condition('refresh_token', $refresh_token)
    ->execute()
    ->fetchObject();

  return _api_user_fix($account);
}

/**
 * @param $uid
 *
 * @return null|object
 */
function api_user_load_by_uid($uid) {
  $account = _api_user_load_account($uid, []);
  return _api_user_fix($account);
}

/**
 * Generate token string.
 */
function api_user_refresh_token() {
  return drupal_random_key(API_TOKEN_REFRESH_BYTES);
}

/**
 * @param object $account
 */
function _api_user_fix($account) {
  if ($account === FALSE) {
    return NULL;
  }

  // Generate Refresh Token for backward compatibility with native Drupal.
  if (empty($account->refresh_token)) {
    $account->refresh_token = api_user_refresh_token();
    db_update('users')
      ->fields(array(
        'refresh_token' => $account->refresh_token,
      ))
      ->condition('uid', $account->uid)
      ->execute();
  }

  $account->uid = (int) $account->uid;
  $account->status = (int) $account->status;
  return $account;
}

/**
 * Build fake email to register social based user in Drupal.
 */
function api_user_social_email($provider, $social_id, $email) {
  return $email ? urldecode($email) : "u{$provider}{$social_id}@" . API_USER_DEFAULT_EMAIL_DOMAIN;
}

/**
 * Concat first and last name parts
 */
function api_user_name_build_parts($data) {
  $first_name = isset($data->first_name) ? $data->first_name : '';
  $last_name = isset($data->last_name) ? $data->last_name : '';
  return trim("$first_name $last_name");
}

/**
 * Fork of user_password().
 *
 * @param int $length
 *
 * @return string
 *
 * @see user_password()
 */
function api_user_password($length = 10) {
  // This variable contains the list of allowable characters for the
  // password. Note that the number 0 and the letter 'O' have been
  // removed to avoid confusion between the two. The same is true
  // of 'I', 1, and 'l'.
  $allowable_characters = 'abcdefghijkmnopqrstuvwxyzABCDEFGHJKLMNPQRSTUVWXYZ23456789';

  // Zero-based count of characters in the allowable list:
  $len = strlen($allowable_characters) - 1;

  // Declare the password as a blank string.
  $pass = '';

  // Loop the number of times specified by $length.
  for ($i = 0; $i < $length; $i++) {
    do {
      // Find a secure random number within the range needed.
      $index = ord(drupal_random_bytes(1));
    } while ($index > $len);

    // Each iteration, pick a random character from the
    // allowable string and append it to the password:
    $pass .= $allowable_characters[$index];
  }

  return $pass;
}

/**
 * For register case it's possible to assign anonymous device to newly register user.
 * I.e. to claim push token which was registered by anon.
 *
 * @param stdClass $device
 * @param stdClass $account
 */
function api_auth_update_device(stdClass $device, stdClass $account) {
  if ($account->uid && empty($device->uid)) {
    $device_data = ['uid' => $account->uid];
    user_device_update($device, $device_data);
  }
}

/**
 * Prepare response for register/login actions.
 *
 * @param $account
 * @param $device
 *
 * @return array
 *
 * @throws \Exception
 * @throws \InvalidMergeQueryException
 */
function api_auth_access_token($account) {
  global $user;
  // Make account as current user after all authorization actions.
  $user = $account;
  $access_token = drupal_random_key(API_TOKEN_ACCESS_BYTES);

  db_insert('sessions')
    ->fields(array(
      'uid' => $account->uid,
      'sid' => drupal_random_key(), // Dummy value for backward compatibility with native Drupal.
      'ssid' => $access_token,
      'hostname' => ip_address(),
      'timestamp' => REQUEST_TIME,
    ))
    ->execute();

  $response = array(
    'authorization' => array(
      'access_token' => array(
        'token_type' => 'Bearer',
        'expires_in' => (int) ini_get('session.gc_maxlifetime'),
        'value' => $access_token,
      ),
    ),
    'user' => array(
      'id' => $account->uid,
      'display_name' => !empty($account->display_name) ? $account->display_name : FALSE,
      'refresh_token' => $account->refresh_token,
      'is_new_user' => (bool) isset($account->new_user),
    ),
  );

  // Update last login date on each login action.
  db_update('users')
    ->fields(array(
      'login' => REQUEST_TIME,
    ))
    ->condition('uid', $account->uid)
    ->execute();

  return $response;
}
