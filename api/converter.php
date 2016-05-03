<?php
/**
 * @file
 *
 * Logic about of conversion of xlsx data to our JSON structures (initially).
 */

require __DIR__ . '/../vendor/autoload.php';

class Converter {

  protected $mapping = array();
  /** @var  PHPExcel $excel */
  protected $excel;

  public function __construct($mapping) {
    $this->mapping = $mapping;
  }

  private function init($sourcePath) {
    $this->excel = PHPExcel_IOFactory::load($sourcePath);
  }

  public function convert($dataApiVersion, $sourcePath) {
    if (!file_exists($sourcePath)) {
      throw new Exception('Failed to load xlsx file: ' . $sourcePath);
    }

    $this->init($sourcePath);

    // Before any mapping process we need to set up some value from settings tab.
    if (isset($this->mapping['timezone'])) {
      // @todo: Turn timezone back after conversion.
      // Set up target timezone to proper date-timestamp conversion.
      date_default_timezone_set($this->mapping['timezone']);
    }

    // Process sheets on pre-defined order to respect dependencies.
    foreach ($this->mapping['groups'] as $group => $sheets) {
      $useSubgroups = TRUE;
      if (!is_array($sheets)) {
        $sheets = array($group => $sheets);
        $useSubgroups = FALSE;
      }
      foreach ($sheets as $machineName => $humanName) {
        foreach ($this->excel->getAllSheets() as $sheet) {
          if ($sheet->getTitle() === $humanName) {
            $parser = new DataParser($dataApiVersion);
            if ($useSubgroups) {
              $data = StaticStorage::getData($group);
              $data[$machineName] = $parser->processSheet($machineName, $sheet);
            }
            else {
              $data = $parser->processSheet($machineName, $sheet);
            }
            StaticStorage::setData($group, $data);
          }
        }
      }
    }

    $result = StaticStorage::getPlainData();

    // Re-arrange content group. In future this should be removed.
    if (isset($result['content'])) {
      $reArrangedContent = array();
      foreach ($result['content'] as $type => $content) {
        $reArrangedContent[] = array('type' => $type, 'data' => $content);
      }
      $result['content'] = $reArrangedContent;
    }

    $result = array('data' => $result);
    return $result;
  }
}


class StaticStorage {
  private static $staticData = array();
  const TEMPORARY = 'tmp';

  public static function setData($group, $data, $storage_type = NULL) {
    self::$staticData[$group]['data'] = $data;
    if ($storage_type) {
      self::$staticData[$group]['storage_type'] = $storage_type;
    }
  }

  public static function getData($group = NULL) {
    return $group ? (isset(self::$staticData[$group]['data']) ? self::$staticData[$group]['data'] : array()) : self::$staticData;
  }

  public static function getDataSubgroup($group, $subgroup) {
    return isset(self::$staticData[$group]) && isset(self::$staticData[$group]['data'][$subgroup]) ? self::$staticData[$group]['data'][$subgroup] : array();
  }

  public static function getPlainData() {
    $result = array();
    foreach (self::$staticData as $group => $data) {
      if (empty($data['storage_type']) || $data['storage_type'] !== StaticStorage::TEMPORARY) {
        $result[$group] = $data['data'];
      }
    }

    return $result;
  }
}

class DataParser {
  protected $dataApiVersion;
  const DATA_PARSER_API_VERSION_DEFAULT = '1.0';

  function __construct($dataApiVersion) {
    $this->dataApiVersion = $dataApiVersion;
  }

  /**
   * Get square range wrapping all data in Excel formant, i.e. A1:B2.
   *
   * @param PHPExcel_Worksheet $sheet
   * @return string
   */
  private function detectRange(PHPExcel_Worksheet $sheet) {
    $lastRow = $lastColumn = 0;

    foreach ($sheet->getRowIterator() as $row) {
      $previousIndex = $lastColumn = 0;
      foreach ($row->getCellIterator() as $cell) {
        /** @var $cell PHPExcel_Cell */
        if (!$cell->getValue()) {
          $lastColumn = $previousIndex;
          break;
        }
        $previousIndex = $lastColumn;
        $lastColumn++;
      }
      break;
    }

    $previousIndex = 0;
    foreach ($sheet->getRowIterator() as $row) {
      $i = 0;
      $isEmpty = TRUE;

      foreach ($row->getCellIterator() as $cell) {
        if ($i <= $lastColumn) {
          /** @var $cell PHPExcel_Cell */
          if ($cell->getValue()) {
            $isEmpty = FALSE;
            break;
          }
        }
      }

      if ($isEmpty) {
        $lastRow = $previousIndex;
        break;
      }
      $previousIndex = $lastRow;
      $lastRow++;
    }

    $end = PHPExcel_Cell::stringFromColumnIndex($lastColumn) . ($lastRow + 1);
    return 'A1' . ($end ? ':' . $end : '');
  }

  public function processSheet($contentType, PHPExcel_Worksheet $sheet) {
    $range = $this->detectRange($sheet);
    $sheetData = $sheet->rangeToArray($range);
    $columns = array_shift($sheetData);
    $mapper = MapperFactory::getFormatter($contentType, $this->dataApiVersion);

    $content = $mapper->mapData($columns, $sheetData);

    return $content;
  }
}

abstract class MapperFactory {
  /**
   * @param string $contentType
   *
   * @param string $dataApiVersion
   *   Version of data API structure.
   *
   * @throws Exception
   *
   * @return Mapper
   */
  public static function getFormatter($contentType, $dataApiVersion) {
    $suggestions = [];
    // Try to find highest available Mapper class version by version suffix.
    // Default(starting) version has no suffix.
    if ($dataApiVersion && $dataApiVersion !== DataParser::DATA_PARSER_API_VERSION_DEFAULT) {
      $suggestions[] = ucfirst($contentType) . 'Mapper_V_' . preg_replace('/[^0-9]/', '_', $dataApiVersion);
    }
    $suggestions[] = ucfirst($contentType) . 'Mapper';

    $class = FALSE;
    while ($suggestion = array_shift($suggestions)) {
      if (class_exists($suggestion)) {
        $class = $suggestion;
        break;
      }
    }

    if (!$class) {
      $message = 'Mapper class not found for: ' . $class;
      if ($dataApiVersion) {
        $message .= ' (version: ' . $dataApiVersion . ')';
      }
      throw new Exception($message);
    }

    return new $class();
  }
}

abstract class Mapper {
  protected $mapping = array();
  const multiValueSeparator = '||';

  protected function getMapping($keys, $rows) {
    return $this->mapping;
  }

  protected function prepareImageId($value) {
    $images = StaticStorage::getData('image');
    $lastId = 0;
    $imageId = NULL;
    foreach ($images as $image) {
      // If image already added, re-use it.
      if ($image['image'] === $value) {
        $imageId = $image['id'];
        break;
      }
      if ($image['id'] > $lastId) {
        $lastId = $image['id'];
      }
    }

    if (is_null($imageId)) {
      $imageId = $lastId + 1;
      $images[] = array('id' => $imageId, 'image' => $value);
      StaticStorage::setData('image', $images);
    }

    return $imageId;
  }

  /**
   * @param $keys
   * @param $rows
   *
   * @throws Exception
   *
   * @return array
   */
  public function mapData($keys, $rows) {
    $result = array();

    $fieldsInfo = array();

    foreach ($this->getMapping($keys, $rows) as $fieldInfo) {
      $found = FALSE;
      foreach ($keys as $index => $name) {
        if ($fieldInfo['humanName'] === $name) {
          $fieldsInfo[$index] = $fieldInfo;
          $found = TRUE;
          break;
        }
      }

      if (!$found) {
        throw new Exception('Missed mapped data for: ' . $fieldInfo['machineName']);
      }
    }

    foreach ($rows as $row) {
      $item = $relations = array();
      $add = TRUE;

      foreach ($row as $key => $value) {
        // Skip non-mapped values.
        if (!isset($fieldsInfo[$key])) {
          continue;
        }
        $fieldInfo = $fieldsInfo[$key];

        switch ($fieldInfo['type']) {
          case 'copy':
            // If at least one non-optional field is missed skip all row.
            if (empty($value) && empty($fieldInfo['optional'])) {
              $add = FALSE;
              break 2;
            }

            $itemKey = $fieldInfo['machineName'];
            $value = trim($value);
            if (!is_null($value) && $value !== "") {
              $item[$itemKey] = $value;
            }
            break;

          case 'relation':
            if ($value && (!empty($fieldInfo['relatedContentType']) || !empty($fieldInfo['relatedGroup']))) {
              $relatedType = !empty($fieldInfo['relatedContentType']) ? $fieldInfo['relatedContentType'] : $fieldInfo['relatedGroup'];
              if (!isset($relations[$relatedType])) {
                $relations[$relatedType] = array();
              }

              if (!empty($fieldInfo['relatedGroup'])) {
                $relatedContent = StaticStorage::getData($fieldInfo['relatedGroup']);
              }
              else {
                $relatedContent = StaticStorage::getDataSubgroup('content', $relatedType);
              }

              $values = array_map('trim', explode(self::multiValueSeparator, $value));
              foreach ($values as $singleValue) {
                foreach ($relatedContent as $contentEntry) {
                  $matched = FALSE;
                  if (isset($fieldInfo['relatedContentKey']) && isset($contentEntry[$fieldInfo['relatedContentKey']]) && $contentEntry[$fieldInfo['relatedContentKey']] === $singleValue) {
                    $matched = TRUE;
                  }
                  elseif (!empty($fieldInfo['relatedContentMatchCallback']) && $this->{$fieldInfo['relatedContentMatchCallback']}($contentEntry, $singleValue)) {
                    $matched = TRUE;
                  }

                  if ($matched) {
                    $id = $contentEntry[$fieldInfo['relatedContentId']];
                    if (!in_array($id, $relations[$relatedType])) {
                      $relations[$relatedType][] = $id;
                    }
                    break;
                  }
                }
              }
            }
            break;

          // Collect all items referenced to current item.
          case 'backRelation':
            if (!empty($fieldInfo['relatedContentType']) && !empty($fieldInfo['relatedContentKey']) && !empty($item[$fieldInfo['relatedContentKey']])) {
              $relatedType = $fieldInfo['relatedContentType'];
              if (!isset($relations[$relatedType])) {
                $relations[$relatedType] = array();
              }

              $value = $item[$fieldInfo['relatedContentKey']];
              $relatedContent = StaticStorage::getDataSubgroup('content', $fieldInfo['storageKey']);
              foreach ($relatedContent as $contentEntry) {
                if (!empty($contentEntry[$fieldInfo['relatedContentKey']]) && $contentEntry[$fieldInfo['relatedContentKey']] == $value) {
                  $id = $contentEntry[$fieldInfo['relatedContentId']];
                  if (!in_array($id, $relations[$relatedType])) {
                    $relations[$relatedType][] = $id;
                  }
                }
              }
            }
            break;

          // @todo: Merge with Relation type.
          case 'reference':
            if ($value) {
              $data = StaticStorage::getData($fieldInfo['referenceGroup']);
              foreach ($data as $dataEntry) {
                if ($dataEntry['name'] === $value) {
                  $item[$fieldInfo['machineName']] = $dataEntry['id'];
                  break;
                }
              }
            }

            break;

          case 'callbackValue':
            if (!empty($fieldInfo['callback']) && method_exists($this, $fieldInfo['callback'])) {
              $item = $this->{$fieldInfo['callback']}($item, $value);
            }
            break;

          case 'image':
            if ($value) {
              $imageKey = isset($fieldInfo['machineName']) ? $fieldInfo['machineName'] : 'image';
              $item[$imageKey] = $this->prepareImageId($value);
            }
            break;
        }
      }

      if ($add) {
        // Convert relations storage format.
        if (!empty($relations)) {
          $formattedRelations = array();
          foreach ($relations as $type => $entries) {
            if (!empty($entries)) {
              $formattedRelations[] = array(
                'type' => $type,
                'identifiers' => $entries,
              );
            }
          }
          if ($formattedRelations) {
            $item['relationships'] = $formattedRelations;
          }
        }
        $result[] = $item;
      }
    }

    return $result;
  }
}

class PlaceMapper extends Mapper {
  protected $mapping = array(
    array('type' => 'copy', 'humanName' => 'ИД', 'machineName' => 'id'),
    array('type' => 'copy', 'humanName' => 'Название', 'machineName' => 'name'),
    array('type' => 'copy', 'humanName' => 'address', 'machineName' => 'address', 'optional' => TRUE),
    array('type' => 'copy', 'humanName' => 'latitude', 'machineName' => 'latitude', 'optional' => TRUE),
    array('type' => 'copy', 'humanName' => 'longitude', 'machineName' => 'longitude', 'optional' => TRUE),
    array('type' => 'callbackValue', 'humanName' => 'Координаты', 'optional' => TRUE, 'callback' => 'placeCoords'),
    array('type' => 'callbackValue', 'humanName' => 'Участник', 'optional' => TRUE, 'callback' => 'placeParticipant'),
  );

  protected function placeCoords($item, $value) {
    if ($value) {
      $coords = array();

      $values = array_map('trim', explode(self::multiValueSeparator, $value));
      foreach ($values as $value) {
        list($x, $y) = array_map('trim', explode(';', $value));
        $coords[] = array('x' => $x, 'y' => $y);
      }

      if ($coords) {
        $item['coordinates'] = $coords;
      }
    }

    return $item;
  }

  protected function placeParticipant($item, $value) {
    $data = StaticStorage::getData('place-exhibit-relations');
    $data[] = array('id' => $item['id'], 'name' => $value);
    StaticStorage::setData('place-exhibit-relations', $data, StaticStorage::TEMPORARY);

    return $item;
  }
}

class EventMapper extends Mapper {
  protected $mapping = array(
    array('type' => 'copy', 'humanName' => 'ИД', 'machineName' => 'id'),
    array('type' => 'callbackValue', 'humanName' => 'Дата', 'callback' => 'eventDatesRange'),
    array('type' => 'copy', 'humanName' => 'Название', 'machineName' => 'name'),
    array('type' => 'copy', 'humanName' => 'Описание', 'machineName' => 'info', 'optional' => TRUE),
    array('type' => 'relation', 'relatedContentType' => 'place', 'relatedContentKey' => 'name', 'relatedContentId' => 'id', 'humanName' => 'Зал', 'optional' => TRUE),
    array('type' => 'relation', 'relatedContentType' => 'user', 'relatedContentMatchCallback' => 'eventUsersMatch', 'relatedContentId' => 'id', 'humanName' => 'Спикеры', 'optional' => TRUE),

    array('type' => 'relation', 'humanName' => 'Тематика докладов', 'relatedGroup' => 'term', 'relatedContentKey' => 'name', 'relatedContentId' => 'id', 'optional' => TRUE),
    array('type' => 'relation', 'humanName' => 'Experience level', 'relatedGroup' => 'term', 'relatedContentKey' => 'name', 'relatedContentId' => 'id', 'optional' => TRUE),
    array('type' => 'relation', 'humanName' => 'Направления', 'relatedGroup' => 'term', 'relatedContentKey' => 'name', 'relatedContentId' => 'id', 'optional' => TRUE),
  );

  protected function eventDatesRange($item, $value) {
    list($date, $timeRange) = explode(' ', $value);
    list($startTime, $endTime) = explode('-', $timeRange);
    list($day, $month, $year) = explode('.', $date);
    $date = "$year-$month-$day";
    if ($startTime && $startTime != '?') {
      $dateTime = new DateTime($date . ' ' . $startTime . ':00');
      $item['dateStart'] = $dateTime->getTimestamp();
    }
    if ($endTime && $endTime != '?') {
      $dateTime = new DateTime($date . ' ' . $endTime . ':00');
      $item['dateEnd'] = $dateTime->getTimestamp();
    }
    return $item;
  }

  protected function eventUsersMatch($user, $name) {
    $user_name_parts = array();
    $user_name_parts[] = $user['name'];
    if (!empty($user['patronymic'])) {
      $user_name_parts[] = $user['patronymic'];
    }

    if (!empty($user['surName'])) {
      $user_name_parts[] = $user['surName'];
    }

    return implode(' ', $user_name_parts) === $name;
  }
}

class NewsMapper extends Mapper {
  protected $mapping = array(
    array('type' => 'copy', 'humanName' => 'ИД', 'machineName' => 'id'),
    array('type' => 'copy', 'humanName' => 'Заголовок', 'machineName' => 'name'),
    array('type' => 'copy', 'humanName' => 'Описание', 'machineName' => 'info', 'optional' => TRUE),
    array('type' => 'image', 'humanName' => 'Картинка', 'optional' => TRUE),
    array('type' => 'callbackValue', 'humanName' => 'Дата', 'callback' => 'newsDate', 'optional' => TRUE),
  );

  protected function newsDate($item, $value) {
    list($date, $time) = explode(' ', $value);
    list($day, $month, $year) = explode('.', $date);
    $date = "$year-$month-$day";

    $dateTime = new DateTime($date . ' ' . $time . ':00');
    $item['date'] = $dateTime->getTimestamp();

    return $item;
  }
}

class OrganizationMapper extends Mapper {
  protected $mapping = array(
    array('type' => 'copy', 'humanName' => 'ИД', 'machineName' => 'id'),
    array('type' => 'copy', 'humanName' => 'Название', 'machineName' => 'name'),
    array('type' => 'copy', 'humanName' => 'Ссылка', 'machineName' => 'link', 'optional' => TRUE),
    array('type' => 'copy', 'humanName' => 'Описание', 'machineName' => 'info', 'optional' => TRUE),
    array('type' => 'image', 'humanName' => 'Картинка'),
  );
}

class ExhibitMapper extends Mapper {
  protected $mapping = array(
    array('type' => 'copy', 'humanName' => 'ИД', 'machineName' => 'id'),
    array('type' => 'copy', 'humanName' => 'Название', 'machineName' => 'name'),
    array('type' => 'copy', 'humanName' => 'Ссылка', 'machineName' => 'link', 'optional' => TRUE),
    array('type' => 'image', 'humanName' => 'Картинка'),
    array('type' => 'copy', 'humanName' => 'Описание', 'machineName' => 'info', 'optional' => TRUE),
    // @todo: Uncomment this and fix fatal.
    //array('type' => 'backRelation', 'relatedContentType' => 'place', 'storageKey' => 'place-exhibit-relations', 'relatedContentKey' => 'name', 'relatedContentId' => 'id', 'humanName' => 'Стенд', 'optional' => TRUE),
  );
}

class TemplateMapper extends Mapper {
  protected $mapping = array(
    array('type' => 'copy', 'humanName' => 'ИД', 'machineName' => 'id'),
    array('type' => 'copy', 'humanName' => 'name', 'machineName' => 'name'),
    array('type' => 'callbackValue', 'humanName' => 'regions', 'callback' => 'templateRegions'),
  );

  protected function templateRegions($item, $value) {
    $regions = array();
    $values = array_filter(explode(self::multiValueSeparator, $value));
    foreach ($values as $value) {
      $regions[] = array(
        'name' => $value,
        'components' => array()
      );
    }

    $item['regions'] = $regions;

    return $item;
  }
}

class MenuMapper extends Mapper {
  protected $mapping = array(
    array('type' => 'copy', 'humanName' => 'ИД', 'machineName' => 'id'),
    array('type' => 'copy', 'humanName' => 'Название', 'machineName' => 'name'),
    array('type' => 'copy', 'humanName' => 'actionType', 'machineName' => 'actionType'),
    array('type' => 'image', 'humanName' => 'image'),
    array('type' => 'callbackValue', 'humanName' => 'component', 'callback' => 'menuComponent'),
  );

  protected function menuComponent($item, $value) {
    if ($value) {
      $item['data']['components'][] = array('id' => $value);
    }

    return $item;
  }
}

class MenuMapper_V_1_1 extends Mapper {
  protected $mapping = array(
    array('type' => 'copy', 'humanName' => 'ИД', 'machineName' => 'id'),
    array('type' => 'copy', 'humanName' => 'Название', 'machineName' => 'name'),
    array('type' => 'callbackValue', 'humanName' => 'actionType', 'callback' => 'menuActionType'),
    array('type' => 'image', 'humanName' => 'image'),
    array('type' => 'callbackValue', 'humanName' => 'component', 'callback' => 'menuActionComponent'),
  );

  protected function menuActionType($item, $value) {
    if ($value) {
      $item['action']['type'] = $value;
    }

    return $item;
  }

  protected function menuActionComponent($item, $value) {
    if ($value) {
      $item['action']['component']['id'] = $value;
    }

    return $item;
  }
}

class ImageMapper extends Mapper {
  protected $mapping = array(
    array('type' => 'copy', 'humanName' => 'ИД', 'machineName' => 'id'),
    array('type' => 'copy', 'humanName' => 'Название', 'machineName' => 'image'),
    array('type' => 'copy', 'humanName' => 'type', 'machineName' => 'type')
  );
}

class VocabularyMapper extends Mapper {
  protected $mapping = array(
    array('type' => 'copy', 'humanName' => 'ИД', 'machineName' => 'id'),
    array('type' => 'copy', 'humanName' => 'Название', 'machineName' => 'name'),
  );
}

class TermMapper extends Mapper {
  protected $mapping = array(
    array('type' => 'copy', 'humanName' => 'ИД', 'machineName' => 'id'),
    array('type' => 'copy', 'humanName' => 'Название', 'machineName' => 'name'),
    array('type' => 'callbackValue', 'humanName' => 'Цвет', 'callback' => 'termColor', 'optional' => TRUE),
    array('type' => 'image', 'humanName' => 'image', 'optional' => TRUE),
    array('type' => 'image', 'humanName' => 'icon', 'machineName' => 'icon', 'optional' => TRUE),
    array('type' => 'reference', 'humanName' => 'Словарь', 'referenceGroup' => 'vocabulary', 'machineName' => 'vocabularyId'),
  );

  protected function termColor($item, $value) {
    if ($value) {
      $item['color']['HEX'] = $value;
    }

    return $item;
  }
}

class StaticMapper extends Mapper {
  protected $mapping = array(
    array('type' => 'copy', 'humanName' => 'ИД', 'machineName' => 'id'),
    array('type' => 'copy', 'humanName' => 'Название', 'machineName' => 'name'),
    array('type' => 'copy', 'humanName' => 'Описание', 'machineName' => 'info', 'optional' => TRUE),
  );
}

class UserMapper extends Mapper {
  protected $mapping = array(
    array('type' => 'copy', 'humanName' => 'ИД', 'machineName' => 'id'),
    array('type' => 'copy', 'humanName' => 'Имя', 'machineName' => 'name'),
    array('type' => 'copy', 'humanName' => 'Отчество', 'machineName' => 'patronymic', 'optional' => TRUE),
    array('type' => 'copy', 'humanName' => 'Фамилия', 'machineName' => 'surName'),
    array('type' => 'copy', 'humanName' => 'phone', 'machineName' => 'phone', 'optional' => TRUE),
    array('type' => 'copy', 'humanName' => 'email', 'machineName' => 'email', 'optional' => TRUE),
    array('type' => 'copy', 'humanName' => 'Описание', 'machineName' => 'info', 'optional' => TRUE),
    array('type' => 'callbackValue', 'humanName' => 'Пол (М/Ж)', 'callback' => 'userGender', 'optional' => TRUE),
    array('type' => 'image', 'humanName' => 'image', 'optional' => TRUE),
  );

  protected function userGender($item, $value) {
    // False for male, as default value.
    $item['gender'] = (!empty($value) && $value === 'Ж');

    return $item;
  }
}

class SettingsMapper extends Mapper {

  protected function getMapping($keys, $rows) {
    $mapping = array();
    foreach ($keys as $key) {
      switch ($key) {
        case 'menu':
          $mapping[] = array('type' => 'callbackValue', 'humanName' => $key, 'callback' => 'settingsMenu', 'optional' => TRUE);
          break;

        case 'showDeveloperInfo':
          $mapping[] = array('type' => 'callbackValue', 'humanName' => $key, 'callback' => 'showInfo', 'optional' => TRUE);
          break;

        default:
          $mapping[] = array('type' => 'copy', 'humanName' => $key, 'machineName' => $key);
          break;
      }
    }

    return $mapping;
  }

  /**
   * @param $keys
   * @param $rows
   *
   * @throws Exception
   *
   * @return array
   */
  public function mapData($keys, $rows) {
    $new_row = array();
    $new_keys = array();
    foreach ($rows as $row) {
      list($name, $value) = $row;
      $new_keys[] = $name;
      $new_row[] = $value;
    }

    $data = parent::mapData($new_keys, array($new_row));
    // Settings is not array of objects, it's plain object itself.
    return current($data);
  }

  protected function settingsMenu($item, $value) {
    if ($value) {
      list($id, $type) = array_map('trim', explode(';', $value));
      $item['menu'] = array('id' => $id, 'type' => $type);
    }

    return $item;
  }

  protected function showInfo($item, $value) {
    $item['showDeveloperInfo'] = ($value && $value === 'Y');

    return $item;
  }
}

class ComponentMapper extends Mapper {
  protected $mapping = array(
    array('type' => 'copy', 'humanName' => 'ИД', 'machineName' => 'id'),
    array('type' => 'copy', 'humanName' => 'type', 'machineName' => 'type'),
    array('type' => 'copy', 'humanName' => 'name', 'machineName' => 'name', 'optional' => TRUE),
    array('type' => 'callbackValue', 'humanName' => 'template', 'callback' => 'componentTemplate', 'optional' => TRUE),
    array('type' => 'callbackValue', 'humanName' => 'regions', 'callback' => 'componentRegions', 'optional' => TRUE),

    array('type' => 'callbackValue', 'humanName' => 'filters', 'callback' => 'componentFilters', 'optional' => TRUE),
    array('type' => 'callbackValue', 'humanName' => 'sorts', 'callback' => 'componentSorts', 'optional' => TRUE),
    array('type' => 'callbackValue', 'humanName' => 'entities', 'callback' => 'componentEntities', 'optional' => TRUE),
    array('type' => 'callbackValue', 'humanName' => 'extraElements', 'callback' => 'componentExtraElements', 'optional' => TRUE),
    array('type' => 'callbackValue', 'humanName' => 'components', 'callback' => 'componentComponents', 'optional' => TRUE),

    array('type' => 'callbackValue', 'humanName' => 'request', 'callback' => 'componentRequest', 'optional' => TRUE),
    array('type' => 'callbackValue', 'humanName' => 'image', 'callback' => 'componentImage', 'optional' => TRUE),

    array('type' => 'callbackValue', 'humanName' => 'heightPercent', 'callback' => 'componentHeightPercent', 'optional' => TRUE),
    array('type' => 'callbackValue', 'humanName' => 'headline', 'callback' => 'componentHeadline', 'optional' => TRUE),
    array('type' => 'callbackValue', 'humanName' => 'size', 'callback' => 'componentSize', 'optional' => TRUE),
    array('type' => 'callbackValue', 'humanName' => 'viewMode', 'callback' => 'componentViewMode', 'optional' => TRUE),
  );

  protected function componentTemplate($item, $value) {
    if ($value) {
      $item['data']['template']['id'] = $value;
    }
    return $item;
  }

  protected function replaceImages($array) {
    foreach ($array as $key => $value) {
      if ($key === 'image' && is_string($value)) {
        $array[$key] = $this->prepareImageId($value);
      }
      elseif (is_array($value)) {
        $array[$key] = $this->replaceImages($value);
      }
    }

    return $array;
  }
  protected function prepareArrayData($value) {
    $value = '[' . $value . ']';
    $value = json_decode($value, TRUE);
    $values = array();
    foreach ($value as $entry) {
      $entry = $this->replaceImages($entry);
      $values[] = $entry;
    }

    return $values;
  }

  protected function componentRegions($item, $value) {
    if ($value) {
      $item['data']['regions'] = $this->prepareArrayData($value);
    }
    return $item;
  }

  protected function componentFilters($item, $value) {
    if ($value) {
      $item['data']['filters'] = $this->prepareArrayData($value);
    }
    return $item;
  }

  protected function componentSorts($item, $value) {
    if ($value) {
      $item['data']['sorts'] = $this->prepareArrayData($value);
    }
    return $item;
  }

  protected function componentEntities($item, $value) {
    if ($value) {
      $item['data']['entities'] = $this->prepareArrayData($value);
    }
    return $item;
  }

  protected function componentExtraElements($item, $value) {
    if ($value) {
      $item['data']['extraElements'] = $this->prepareArrayData($value);
    }
    return $item;
  }

  protected function componentComponents($item, $value) {
    if ($value) {
      $ids = array_map('trim', explode(',', $value));
      $components = array();
      foreach ($ids as $id) {
        $components[] = array('id' => $id);
      }

      $item['data']['components'] = $components;
    }
    return $item;
  }

  protected function componentRequest($item, $value) {
    if ($value) {
      $item['data']['request']['url'] = $value;
    }
    return $item;
  }

  protected function componentImage($item, $value) {
    if ($value) {
      $item['data']['image'] = $this->prepareImageId($value);
    }

    return $item;
  }

  protected function componentHeightPercent($item, $value) {
    if ($value) {
      $item['data']['heightPercent'] = $value;
    }

    return $item;
  }

  protected function componentHeadline($item, $value) {
    $item['data']['headline'] = ($value && $value === 'Y');

    return $item;
  }

  protected function componentSize($item, $value) {
    if ($value) {
      $item['data']['size'] = $value;
    }

    return $item;
  }

  protected function componentViewMode($item, $value) {
    if ($value) {
      $item['data']['viewMode'] = $value;
    }

    return $item;
  }

}

class ComponentMapper_V_1_1 extends ComponentMapper {

  protected function componentSorts($item, $value) {
    if ($value) {
      $item['data']['sort'] = json_decode($value, TRUE);
    }
    return $item;
  }
}
