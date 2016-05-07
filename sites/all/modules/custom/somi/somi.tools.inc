<?php

/**
 * Used to provide russian plurals without translation subsystem.
 * @param $a
 * @param $str1
 * @param $str2
 * @param $str3
 * @return mixed
 */
function plural_str($a, $str1, $str2, $str3) {
  if ($a % 10 == 1 && $a % 100 != 11) return $str1;
  else if (($a % 10 >= 2) && ($a % 10 <= 4) && ($a % 100 < 10 || $a % 100 >= 20)) return $str2;
  else return $str3;
}