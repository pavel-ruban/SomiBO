<?php
/**
 * Created by PhpStorm.
 * User: user
 * Date: 06/12/15
 * Time: 13:59
 */

require_once __DIR__ . '/converter.php';

require_once __DIR__ . '/../sites/all/modules/custom/campuz_export/campuz_export.module';

$projects = campuz_export_get_projects_list();
$project = $projects['drupalcamp-sib'];
$converter = new Converter($project['mapping']);
$result = $converter->convert($project['api_version'], __DIR__ . '/xlsx/DrupalCamp Siberia — форматированный контент.xlsx');

file_put_contents(__DIR__ . '/xlsx/data-3.json', json_encode($result, JSON_HEX_TAG | JSON_HEX_APOS | JSON_HEX_AMP | JSON_HEX_QUOT | JSON_NUMERIC_CHECK));