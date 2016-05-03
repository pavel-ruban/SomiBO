<?php

function api_error_handler($error_level, $message, $filename, $line, $context) {
  if (defined('E_DEPRECATED') && ($error_level == E_DEPRECATED ||$error_level == E_USER_DEPRECATED)) {
    return;
  }

  // Check all errors system and use api_syslog().
  // "Level 2, stat() [<a href='0function.stat0'>function.stat0</a>]: stat failed for ..., includes/stream_wrappers.inc, 689"
  throw new ApiErrorException($error_level, $message, $filename, $line, $context);
}

class ApiException extends Exception {
  public function __construct($message = '', $code = 0) {
    parent::__construct($message, $code);
  }
}

class ApiErrorException extends ApiException {
  public function __construct($error_level, $message, $filename, $line, $context) {
    parent::__construct(implode(', ', array('Level' . $error_level, $message, $filename, $line)));
  }
}

class ApiInvalidJsonException extends ApiException {}

class ApiAccessDeniedException extends ApiException {
  public function getMessageForResponse() {
    $result = array();

    $result['error']['message'] = $this->getMessage();
    $result['error']['code'] = $this->getCode();

    return $result;
  }
}

class ApiAuthException extends ApiException {}

class ApiUserException extends ApiException {}

class ApiNotImplementedException extends ApiException {}