<?php

/**
 * @file
 *
 * Auth logic for social networks.
 */

define('API_USER_SOCIAL_VK', 'vk');
define('API_USER_SOCIAL_FB', 'fb');
define('API_USER_SOCIAL_GPLUS', 'gp');
define('API_USER_SOCIAL_TWITTER', 'tw');
define('API_USER_SOCIAL_TWITTER_DIGITS', 'td');

define('API_USER_SOCIAL_VK_APP_ID', '3708097');
define('API_USER_SOCIAL_VK_APP_SECRET', 'DzCyZBvvVUcZdzkO9X89');
define('API_USER_SOCIAL_VK_API_VERSION', '5.21');
// You can refresh token through
// https://oauth.vk.com/access_token?client_id=3708097&client_secret=DzCyZBvvVUcZdzkO9X89&v=5.26&grant_type=client_credentials
define('API_USER_SOCIAL_VK_APP_TOKEN', '1c9509061c9509061cb0c877dc1cad9dc711c951c9509064966e032c8d7bf97a93d220b');


// Used to build request to validate oAuth token for registration.
define('API_USER_SOCIAL_TWITTER_APP_CONSUMER', '4hctunABlfsPnh8zeLgjBQgJ9');
define('API_USER_SOCIAL_TWITTER_APP_CONSUMER_SECRET', 'zUi67agWX3eni1uiFtrrU36sZCKM6sB1JtXiV3abpjPLqGpC7P');

define('API_USER_SOCIAL_TIMEOUT', 5);

/**
 * Load or create user by social credentials.
 * @todo: Handle update user params (mail, name) in case of re-register/re-login.
 */
function api_user_load_by_social($social, $extra_data) {
  $access_token = $social->access_token;
  if (empty($access_token)) {
    throw new ApiAuthException('Social access token is required');
  }
  // TODO: Store language of a user.
  // Twitter: $data->lang
  // Pass from client?
  switch ($social->provider) {
    case API_USER_SOCIAL_VK:
      return api_user_social_get_vk($access_token, $extra_data);

    case API_USER_SOCIAL_FB:
      return api_user_social_get_fb($access_token, $extra_data);

    case API_USER_SOCIAL_GPLUS:
      return api_user_social_get_gplus($access_token, $extra_data);

    case API_USER_SOCIAL_TWITTER:
      return api_user_social_get_twitter($access_token, $extra_data);

    case API_USER_SOCIAL_TWITTER_DIGITS:
      return api_user_social_get_twitter_digits($access_token, $extra_data);

    default:
      return NULL;
  }
}

/**
 * Try to load user based on social data or create new account.
 */
function _api_user_prepare_social_account($provider, $social_user_id, $user_name, $data, $extra_data, $account = NULL) {
  $social = api_user_social_load($provider, $social_user_id);

  if (!$social) {
    $email = api_user_social_email(
      $provider,
      $social_user_id,
      isset($data->email) ? $data->email : NULL
    );
    $name = api_user_name(
      $provider,
      $social_user_id,
      $user_name,
      $email
    );

    if (!$account && !($account = api_user_load_by_email($email))) {
      $account = api_user_create(
        $name,
        $email,
        api_user_password(API_USER_PASSWORD_LENGTH),
        $extra_data->language
      );
    }

    api_user_social_create(
      $provider,
      $social_user_id,
      $name,
      array('raw' => $data, 'extra' => $extra_data),
      $account
    );
  }
  elseif (!$account) {
    $account = api_user_load_by_uid($social->uid);
  }

  // If user name is updated or just received - re-save it in account.
  if ($account && $user_name && $user_name != $account->display_name) {
    db_update('users')
      ->condition('uid', $account->uid)
      ->fields(['display_name' => $user_name])
      ->execute();
    $account->display_name = $user_name;
  }

  return $account;
}

/**
 * Save relation between Drupal user and social data.
 */
function api_user_social_create($provider, $social_id, $social_name, $social_data, $account) {
  $id = db_insert('users_social')
    ->fields(array(
      'provider' => $provider,
      'social_id' => $social_id,
      'social_name' => $social_name,
      'social_data' => serialize($social_data),
      'uid' => $account->uid,
      'created' => REQUEST_TIME,
    ))
    ->execute();

  return (int) $id;
}

/**
 * Check if relation from social data to our user exists.
 */
function api_user_social_load($provider, $social_id) {
  $social = db_select('users_social', 'us')
    ->fields('us', array('id', 'provider', 'social_id', 'social_name', 'uid'))
    ->condition('provider', $provider)
    ->condition('social_id', $social_id)
    ->execute()
    ->fetchObject();

  if (!$social) {
    return NULL;
  }

  $social->id = (int) $social->id;
  $social->uid = (int) $social->uid;

  return $social ? $social : NULL;
}

/**
 * @param $access_token
 * @param $extra_data
 *
 * @return mixed|null|object
 * @throws ApiAuthException
 * @throws ApiUserException
 */
function api_user_social_get_vk($access_token, $extra_data) {
  $data = array(
    'v' => API_USER_SOCIAL_VK_API_VERSION,
    'token' => $access_token,
    'client_secret' => API_USER_SOCIAL_VK_APP_SECRET,
    'access_token' => API_USER_SOCIAL_VK_APP_TOKEN,
  );
  $result = drupal_http_request(
    'https://api.vk.com/method/secure.checkToken?' . drupal_http_build_query($data),
    array('timeout' => API_USER_SOCIAL_TIMEOUT)
  );

  if (!$result || $result->code != 200) {
    throw new ApiUserException('Failed to fetch social data from VK for: ' . $access_token);
  }

  $raw_data = json_decode($result->data, FALSE);

  if (isset($raw_data->error)) {
    throw new ApiUserException($raw_data->error->error_msg, $raw_data->error->error_code);
  }

  if (!$raw_data->response->success) {
    throw new ApiUserException('Failed to parse social data response from VK for: ' . $access_token);
  }

  $data = new stdClass();
  $data->user_id = $raw_data->response->user_id;

  $user_name = api_user_name_build_parts($data);
  return _api_user_prepare_social_account(API_USER_SOCIAL_VK, $data->user_id, $user_name, $data, $extra_data);
}

/**
 * @param $access_token
 * @param $extra_data
 *
 * @return mixed|null|object
 * @throws ApiAuthException
 * @throws ApiUserException
 */
function api_user_social_get_fb($access_token, $extra_data) {
  $result = drupal_http_request(
    "https://graph.facebook.com/me?access_token={$access_token}",
    array('timeout' => API_USER_SOCIAL_TIMEOUT)
  );

  if (!$result || $result->code != 200) {
    throw new ApiUserException('Failed to fetch social data from FB for: ' . $access_token);
  }

  $data = json_decode($result->data, FALSE);

  if (isset($data->error)) {
    throw new ApiUserException($data->error->message, $data->error->code);
  }

  $user_name = isset($data->name) ? $data->name : NULL;
  return _api_user_prepare_social_account(API_USER_SOCIAL_FB, $data->id, $user_name, $data, $extra_data);
}

/**
 * @param $access_token
 * @param $extra_data
 *
 * @return mixed|null|object
 * @throws ApiAuthException
 * @throws ApiUserException
 */
function api_user_social_get_gplus($access_token, $extra_data) {
  $result = drupal_http_request(
    "https://www.googleapis.com/oauth2/v1/tokeninfo?access_token={$access_token}",
    array('timeout' => API_USER_SOCIAL_TIMEOUT)
  );

  if (!$result || $result->code != 200) {
    throw new ApiUserException('Failed to load G+ data for token: ' . $access_token);
  }

  $data = json_decode($result->data);

  if (isset($data->error)) {
    throw new ApiUserException("$data->error: $data->error_description");
  }

  $user_name = isset($extra_data->display_name) ? $extra_data->display_name : NULL;
  return _api_user_prepare_social_account(API_USER_SOCIAL_GPLUS, $data->user_id, $user_name, $data, $extra_data);
}

/**
 * Handle logic to register new Twitter users.
 */
function api_user_social_get_twitter($access_token, $extra_data) {
  if (empty($extra_data->access_token_secret)) {
    throw new ApiUserException('Missed required secret token for twitter user registration');
  }
  $access_token_secret = $extra_data->access_token_secret;
  $data = _api_user_social_get_twitter_data($access_token, $access_token_secret);

  if (!empty($data->errors)) {
    $messages = array();
    foreach ($data->errors as $error) {
      $messages[] = $error->message . '(' . $error->code . ')';
    }
    throw new ApiUserException('Access token verification failed: ' . implode(', ', $messages) . ' Tokens: ' . $access_token . '::' . $access_token_secret);
  }

  $user_name = !empty($data->name) ? $data->name : (!empty($data->screen_name) ? $data->screen_name : NULL);
  return _api_user_prepare_social_account(API_USER_SOCIAL_TWITTER, $data->id, $user_name, $data, $extra_data);
}

/**
 * Authenticate user via Twitter Digits.
 */
function api_user_social_get_twitter_digits($access_token, $extra_data) {
  // Verify and get phone number. Find uid by phone number.
  // Return auth data.
  if (empty($extra_data->service_provider)) {
    throw new ApiUserException('Missed required service provider URL');
  }

  $api_url = $extra_data->service_provider;
  $result = drupal_http_request(
    $api_url,
    array(
      'headers' => ['Authorization' => $access_token]
    )
  );

  if (!$result || $result->code != 200) {
    throw new ApiUserException('Failed to verify Twitter Digits token');
  }

  $data = json_decode($result->data);

  $account = api_user_load_by_phone($data->phone_number);
  $user_name = !empty($account->display_name) ? $account->display_name : NULL;
  return _api_user_prepare_social_account(API_USER_SOCIAL_TWITTER_DIGITS, $data->id, $user_name, $data, $extra_data, $account);
}

/**
 * Helper to get data from Twitter.
 */
function _api_user_social_get_twitter_data($access_token, $access_token_secret) {
  $params = array(
    'oauth_consumer_key' => API_USER_SOCIAL_TWITTER_APP_CONSUMER,
    'oauth_nonce' => md5(microtime() . mt_rand()),
    'oauth_signature_method' => 'HMAC-SHA1',
    'oauth_timestamp' => REQUEST_TIME,
    'oauth_token' => $access_token,
    'oauth_version' => '1.0',
  );

  $api_url = 'https://api.twitter.com/1.1/account/verify_credentials.json';
  $parts = array(
    'GET',
    $api_url,
    _api_user_twitter_build_http_query($params)
  );

  $parts = _api_user_twitter_urlencode_rfc3986($parts);

  $signature_base_string = implode('&', $parts);

  $key_parts = array(
    API_USER_SOCIAL_TWITTER_APP_CONSUMER_SECRET,
    $access_token_secret,
  );
  $key_parts = _api_user_twitter_urlencode_rfc3986($key_parts);
  $key = implode('&', $key_parts);

  $signature = base64_encode(hash_hmac('sha1', $signature_base_string, $key, true));

  $header_parts = array();
  foreach($params as $param_name => $param) {
    $header_parts[] = $param_name . '="' . $param . '"';
  }
  $header_parts[] = 'oauth_signature="' . _api_user_twitter_urlencode_rfc3986($signature) . '"';

  $result = drupal_http_request(
    $api_url,
    array(
      'timeout' => API_USER_SOCIAL_TIMEOUT,
      'headers' => array('Authorization' => 'OAuth ' . implode(', ', $header_parts))
    )
  );

  if (!$result) {
    throw new ApiUserException('Access token validation failed');
  }

  return json_decode($result->data, FALSE);
}

/**
 * oAuth friendly query building.
 */
function _api_user_twitter_build_http_query($params) {
  if (!$params) return '';

  // Urlencode both keys and values
  $keys = _api_user_twitter_urlencode_rfc3986(array_keys($params));
  $values = _api_user_twitter_urlencode_rfc3986(array_values($params));
  $params = array_combine($keys, $values);

  // Parameters are sorted by name, using lexicographical byte value ordering.
  // Ref: Spec: 9.1.1 (1)
  uksort($params, 'strcmp');

  $pairs = array();
  foreach ($params as $parameter => $value) {
    if (is_array($value)) {
      // If two or more parameters share the same name, they are sorted by their value
      // Ref: Spec: 9.1.1 (1)
      // June 12th, 2010 - changed to sort because of issue 164 by hidetaka
      sort($value, SORT_STRING);
      foreach ($value as $duplicate_value) {
        $pairs[] = $parameter . '=' . $duplicate_value;
      }
    }
    else {
      $pairs[] = $parameter . '=' . $value;
    }
  }
  // For each parameter, the name is separated from the corresponding value by an '=' character (ASCII code 61)
  // Each name-value pair is separated by an '&' character (ASCII code 38)
  return implode('&', $pairs);
}

/**
 * oAuth friendly encoding.
 */
function _api_user_twitter_urlencode_rfc3986($input) {
  if (is_array($input)) {
    return array_map('_api_user_twitter_urlencode_rfc3986', $input);
  }
  elseif (is_scalar($input)) {
    return str_replace(
      '+',
      ' ',
      str_replace('%7E', '~', rawurlencode($input))
    );
  }
  else {
    return '';
  }
}

