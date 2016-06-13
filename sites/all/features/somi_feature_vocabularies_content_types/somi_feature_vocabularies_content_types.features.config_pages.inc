<?php
/**
 * @file
 * somi_feature_vocabularies_content_types.features.config_pages.inc
 */

/**
 * Implements hook_config_pages_default_data().
 */
function somi_feature_vocabularies_content_types_config_pages_default_data() {
  $config_pages = array();

  // Exported format: somi_settings-.
  $config_pages['somi_settings-'] = array(
    'context' => '',
    'data' => '',
    'field_collection_item:field_currencies' => array(
      0 => array(
        'field_collection_item:field_cases_declensions' => array(
          0 => array(
            'field_1_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Жук',
                  'format' => NULL,
                  'safe_value' => 'Жук',
                ),
              ),
            ),
            'field_2_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Жука',
                  'format' => NULL,
                  'safe_value' => 'Жука',
                ),
              ),
            ),
            'field_3_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Жуков',
                  'format' => NULL,
                  'safe_value' => 'Жуков',
                ),
              ),
            ),
          ),
          1 => array(
            'field_1_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Жуке',
                  'format' => NULL,
                  'safe_value' => 'Жуке',
                ),
              ),
            ),
            'field_2_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Жуках',
                  'format' => NULL,
                  'safe_value' => 'Жуках',
                ),
              ),
            ),
            'field_3_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Жуках',
                  'format' => NULL,
                  'safe_value' => 'Жуках',
                ),
              ),
            ),
          ),
          2 => array(
            'field_1_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Жука',
                  'format' => NULL,
                  'safe_value' => 'Жука',
                ),
              ),
            ),
            'field_2_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Жуков',
                  'format' => NULL,
                  'safe_value' => 'Жуков',
                ),
              ),
            ),
            'field_3_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Жуков',
                  'format' => NULL,
                  'safe_value' => 'Жуков',
                ),
              ),
            ),
          ),
          3 => array(
            'field_1_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Жуком',
                  'format' => NULL,
                  'safe_value' => 'Жуком',
                ),
              ),
            ),
            'field_2_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Жуками',
                  'format' => NULL,
                  'safe_value' => 'Жуками',
                ),
              ),
            ),
            'field_3_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Жуками',
                  'format' => NULL,
                  'safe_value' => 'Жуками',
                ),
              ),
            ),
          ),
        ),
        'field_collection_item:field_slack_op' => array(
          0 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'error_status',
                  'format' => NULL,
                  'safe_value' => 'error_status',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '*Сделка на %qty% %goods% не удалась!* :no_entry_sign:\\n\\n*Отправитель*',
                  'format' => NULL,
                  'safe_value' => '*Сделка на %qty% %goods% не удалась!* :no_entry_sign:\\n\\n*Отправитель*',
                ),
              ),
            ),
          ),
          1 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_header',
                  'format' => NULL,
                  'safe_value' => 'op_header',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Наказание жуками',
                  'format' => NULL,
                  'safe_value' => 'Наказание жуками',
                ),
              ),
            ),
          ),
          2 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'event_error',
                  'format' => NULL,
                  'safe_value' => 'event_error',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '_Наказание не удалось_',
                  'format' => NULL,
                  'safe_value' => '_Наказание не удалось_',
                ),
              ),
            ),
          ),
          3 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'event_remind',
                  'format' => NULL,
                  'safe_value' => 'event_remind',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '_Напоминание_',
                  'format' => NULL,
                  'safe_value' => '_Напоминание_',
                ),
              ),
            ),
          ),
          4 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'event_private',
                  'format' => NULL,
                  'safe_value' => 'event_private',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '_Вы были наказаны %usr% %qty% %goods%_',
                  'format' => NULL,
                  'safe_value' => '_Вы были наказаны %usr% %qty% %goods%_',
                ),
              ),
            ),
          ),
          5 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'event_owner',
                  'format' => NULL,
                  'safe_value' => 'event_owner',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '_Вы наказали %qty% %goods% %users%_',
                  'format' => NULL,
                  'safe_value' => '_Вы наказали %qty% %goods% %users%_',
                ),
              ),
            ),
          ),
          6 => array(
            'field_op_alt' => array(
              'und' => array(
                0 => array(
                  'value' => '_Был(а) наказан(а) %users%_',
                  'format' => NULL,
                  'safe_value' => '_Был(а) наказан(а) %users%_',
                ),
              ),
            ),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'event_channel',
                  'format' => NULL,
                  'safe_value' => 'event_channel',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '_Были наказаны %users%_',
                  'format' => NULL,
                  'safe_value' => '_Были наказаны %users%_',
                ),
              ),
            ),
          ),
          7 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_status',
                  'format' => NULL,
                  'safe_value' => 'op_status',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '*Наказание %qty% %goods% прошло успешно!* :white_check_mark:\\n\\n*Кем*',
                  'format' => NULL,
                  'safe_value' => '*Наказание %qty% %goods% прошло успешно!* :white_check_mark:\\n\\n*Кем*',
                ),
              ),
            ),
          ),
          8 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_status_private',
                  'format' => NULL,
                  'safe_value' => 'op_status_private',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '*Вы получили %qty% %goods%!* %currencies%\\n\\n*От кого*',
                  'format' => NULL,
                  'safe_value' => '*Вы получили %qty% %goods%!* %currencies%\\n\\n*От кого*',
                ),
              ),
            ),
          ),
          9 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_status_remind',
                  'format' => NULL,
                  'safe_value' => 'op_status_remind',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => ':bell: *Вы хотели наказать %qty% %currency% %users%*',
                  'format' => NULL,
                  'safe_value' => ':bell: *Вы хотели наказать %qty% %currency% %users%*',
                ),
              ),
            ),
          ),
          10 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'attach_balance_remind_title',
                  'format' => NULL,
                  'safe_value' => 'attach_balance_remind_title',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Жуки в наличии',
                  'format' => NULL,
                  'safe_value' => 'Жуки в наличии',
                ),
              ),
            ),
          ),
          11 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'attach_balance_private_title',
                  'format' => NULL,
                  'safe_value' => 'attach_balance_private_title',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Всего наказаны',
                  'format' => NULL,
                  'safe_value' => 'Всего наказаны',
                ),
              ),
            ),
          ),
          12 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'attach_balance_owner_title',
                  'format' => NULL,
                  'safe_value' => 'attach_balance_owner_title',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Жуков осталось',
                  'format' => NULL,
                  'safe_value' => 'Жуков осталось',
                ),
              ),
            ),
          ),
          13 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'attach_balance_needed_title',
                  'format' => NULL,
                  'safe_value' => 'attach_balance_needed_title',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Жуков необходимо',
                  'format' => NULL,
                  'safe_value' => 'Жуков необходимо',
                ),
              ),
            ),
          ),
          14 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_color',
                  'format' => NULL,
                  'safe_value' => 'op_color',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'danger',
                  'format' => NULL,
                  'safe_value' => 'danger',
                ),
              ),
            ),
          ),
          15 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_remind',
                  'format' => NULL,
                  'safe_value' => 'op_remind',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Наказать',
                  'format' => NULL,
                  'safe_value' => 'Наказать',
                ),
              ),
            ),
          ),
        ),
        'field_emoticon' => array(
          'und' => array(
            0 => array(
              'value' => ':beetle:',
              'format' => NULL,
              'safe_value' => ':beetle:',
            ),
          ),
        ),
      ),
      1 => array(
        'field_collection_item:field_cases_declensions' => array(
          0 => array(
            'field_1_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Кристалл',
                  'format' => NULL,
                  'safe_value' => 'Кристалл',
                ),
              ),
            ),
            'field_2_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Кристалла',
                  'format' => NULL,
                  'safe_value' => 'Кристалла',
                ),
              ),
            ),
            'field_3_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Кристаллов',
                  'format' => NULL,
                  'safe_value' => 'Кристаллов',
                ),
              ),
            ),
          ),
          1 => array(
            'field_1_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Кристалле',
                  'format' => NULL,
                  'safe_value' => 'Кристалле',
                ),
              ),
            ),
            'field_2_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Кристаллах',
                  'format' => NULL,
                  'safe_value' => 'Кристаллах',
                ),
              ),
            ),
            'field_3_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Кристаллах',
                  'format' => NULL,
                  'safe_value' => 'Кристаллах',
                ),
              ),
            ),
          ),
          2 => array(
            'field_1_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Кристалл',
                  'format' => NULL,
                  'safe_value' => 'Кристалл',
                ),
              ),
            ),
            'field_2_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Кристалла',
                  'format' => NULL,
                  'safe_value' => 'Кристалла',
                ),
              ),
            ),
            'field_3_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Кристаллов',
                  'format' => NULL,
                  'safe_value' => 'Кристаллов',
                ),
              ),
            ),
          ),
          3 => array(
            'field_1_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Кристаллом',
                  'format' => NULL,
                  'safe_value' => 'Кристаллом',
                ),
              ),
            ),
            'field_2_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Кристаллами',
                  'format' => NULL,
                  'safe_value' => 'Кристаллами',
                ),
              ),
            ),
            'field_3_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Кристаллами',
                  'format' => NULL,
                  'safe_value' => 'Кристаллами',
                ),
              ),
            ),
          ),
        ),
        'field_collection_item:field_slack_op' => array(
          0 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'error_status',
                  'format' => NULL,
                  'safe_value' => 'error_status',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '*Сделка на %qty% %goods% не удалась!* :no_entry_sign:\\n\\n*Отправитель*',
                  'format' => NULL,
                  'safe_value' => '*Сделка на %qty% %goods% не удалась!* :no_entry_sign:\\n\\n*Отправитель*',
                ),
              ),
            ),
          ),
          1 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_header',
                  'format' => NULL,
                  'safe_value' => 'op_header',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Награждение кристаллами',
                  'format' => NULL,
                  'safe_value' => 'Награждение кристаллами',
                ),
              ),
            ),
          ),
          2 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'event_error',
                  'format' => NULL,
                  'safe_value' => 'event_error',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '_Произошла ошибка при награждении_',
                  'format' => NULL,
                  'safe_value' => '_Произошла ошибка при награждении_',
                ),
              ),
            ),
          ),
          3 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'event_remind',
                  'format' => NULL,
                  'safe_value' => 'event_remind',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '_Напоминание_',
                  'format' => NULL,
                  'safe_value' => '_Напоминание_',
                ),
              ),
            ),
          ),
          4 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'event_private',
                  'format' => NULL,
                  'safe_value' => 'event_private',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '_Вам подарили %qty% %goods% от %usr%_',
                  'format' => NULL,
                  'safe_value' => '_Вам подарили %qty% %goods% от %usr%_',
                ),
              ),
            ),
          ),
          5 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'event_owner',
                  'format' => NULL,
                  'safe_value' => 'event_owner',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '_Вы подарили %qty% %goods% %users%_',
                  'format' => NULL,
                  'safe_value' => '_Вы подарили %qty% %goods% %users%_',
                ),
              ),
            ),
          ),
          6 => array(
            'field_op_alt' => array(
              'und' => array(
                0 => array(
                  'value' => '_Был(а) награжден(а) %users%_',
                  'format' => NULL,
                  'safe_value' => '_Был(а) награжден(а) %users%_',
                ),
              ),
            ),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'event_channel',
                  'format' => NULL,
                  'safe_value' => 'event_channel',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '_Были награждены %users%_',
                  'format' => NULL,
                  'safe_value' => '_Были награждены %users%_',
                ),
              ),
            ),
          ),
          7 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_status',
                  'format' => NULL,
                  'safe_value' => 'op_status',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '*Сделка на %qty% %goods% прошла успешно!* :white_check_mark:\\n\\n*От кого*',
                  'format' => NULL,
                  'safe_value' => '*Сделка на %qty% %goods% прошла успешно!* :white_check_mark:\\n\\n*От кого*',
                ),
              ),
            ),
          ),
          8 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_status_private',
                  'format' => NULL,
                  'safe_value' => 'op_status_private',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '*Вы получили %qty% %goods%!* %currencies%\\n\\n*От кого*',
                  'format' => NULL,
                  'safe_value' => '*Вы получили %qty% %goods%!* %currencies%\\n\\n*От кого*',
                ),
              ),
            ),
          ),
          9 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_status_remind',
                  'format' => NULL,
                  'safe_value' => 'op_status_remind',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => ':bell: *Вы хотели подарить %qty% %currency%*',
                  'format' => NULL,
                  'safe_value' => ':bell: *Вы хотели подарить %qty% %currency%*',
                ),
              ),
            ),
          ),
          10 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'attach_balance_remind_title',
                  'format' => NULL,
                  'safe_value' => 'attach_balance_remind_title',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Кристаллов на вашем счете',
                  'format' => NULL,
                  'safe_value' => 'Кристаллов на вашем счете',
                ),
              ),
            ),
          ),
          11 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'attach_balance_private_title',
                  'format' => NULL,
                  'safe_value' => 'attach_balance_private_title',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Кристаллов в наличии',
                  'format' => NULL,
                  'safe_value' => 'Кристаллов в наличии',
                ),
              ),
            ),
          ),
          12 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'attach_balance_owner_title',
                  'format' => NULL,
                  'safe_value' => 'attach_balance_owner_title',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Кристаллов осталось',
                  'format' => NULL,
                  'safe_value' => 'Кристаллов осталось',
                ),
              ),
            ),
          ),
          13 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'attach_balance_needed_title',
                  'format' => NULL,
                  'safe_value' => 'attach_balance_needed_title',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Не хватает кристаллов',
                  'format' => NULL,
                  'safe_value' => 'Не хватает кристаллов',
                ),
              ),
            ),
          ),
          14 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_color',
                  'format' => NULL,
                  'safe_value' => 'op_color',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'good',
                  'format' => NULL,
                  'safe_value' => 'good',
                ),
              ),
            ),
          ),
          15 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_remind',
                  'format' => NULL,
                  'safe_value' => 'op_remind',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Подарить',
                  'format' => NULL,
                  'safe_value' => 'Подарить',
                ),
              ),
            ),
          ),
        ),
        'field_emoticon' => array(
          'und' => array(
            0 => array(
              'value' => ':gem:',
              'format' => NULL,
              'safe_value' => ':gem:',
            ),
          ),
        ),
      ),
      2 => array(
        'field_collection_item:field_cases_declensions' => array(
          0 => array(
            'field_1_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Друпликон',
                  'format' => NULL,
                  'safe_value' => 'Друпликон',
                ),
              ),
            ),
            'field_2_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Друпликона',
                  'format' => NULL,
                  'safe_value' => 'Друпликона',
                ),
              ),
            ),
            'field_3_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Друпликонов',
                  'format' => NULL,
                  'safe_value' => 'Друпликонов',
                ),
              ),
            ),
          ),
          1 => array(
            'field_1_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Друпликоне',
                  'format' => NULL,
                  'safe_value' => 'Друпликоне',
                ),
              ),
            ),
            'field_2_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Друпликонах',
                  'format' => NULL,
                  'safe_value' => 'Друпликонах',
                ),
              ),
            ),
            'field_3_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Друпликонах',
                  'format' => NULL,
                  'safe_value' => 'Друпликонах',
                ),
              ),
            ),
          ),
          2 => array(
            'field_1_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Друпликон',
                  'format' => NULL,
                  'safe_value' => 'Друпликон',
                ),
              ),
            ),
            'field_2_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Друпликона',
                  'format' => NULL,
                  'safe_value' => 'Друпликона',
                ),
              ),
            ),
            'field_3_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Друпликонов',
                  'format' => NULL,
                  'safe_value' => 'Друпликонов',
                ),
              ),
            ),
          ),
          3 => array(
            'field_1_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Друпликоном',
                  'format' => NULL,
                  'safe_value' => 'Друпликоном',
                ),
              ),
            ),
            'field_2_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Друпликонами',
                  'format' => NULL,
                  'safe_value' => 'Друпликонами',
                ),
              ),
            ),
            'field_3_declension' => array(
              'und' => array(
                0 => array(
                  'value' => 'Друпликонами',
                  'format' => NULL,
                  'safe_value' => 'Друпликонами',
                ),
              ),
            ),
          ),
        ),
        'field_collection_item:field_slack_op' => array(
          0 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'error_status',
                  'format' => NULL,
                  'safe_value' => 'error_status',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '*Друпликация на %qty% %goods% не удалась!* :no_entry_sign:\\n\\n*Отправитель*',
                  'format' => NULL,
                  'safe_value' => '*Друпликация на %qty% %goods% не удалась!* :no_entry_sign:\\n\\n*Отправитель*',
                ),
              ),
            ),
          ),
          1 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_header',
                  'format' => NULL,
                  'safe_value' => 'op_header',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Друпликация за контрибьют',
                  'format' => NULL,
                  'safe_value' => 'Друпликация за контрибьют',
                ),
              ),
            ),
          ),
          2 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'event_error',
                  'format' => NULL,
                  'safe_value' => 'event_error',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '_Произошла ошибка при друпликации_',
                  'format' => NULL,
                  'safe_value' => '_Произошла ошибка при друпликации_',
                ),
              ),
            ),
          ),
          3 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'event_remind',
                  'format' => NULL,
                  'safe_value' => 'event_remind',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '_Напоминание_',
                  'format' => NULL,
                  'safe_value' => '_Напоминание_',
                ),
              ),
            ),
          ),
          4 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'event_private',
                  'format' => NULL,
                  'safe_value' => 'event_private',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '_Вас наградил(а) %qty% %goods% %usr%_',
                  'format' => NULL,
                  'safe_value' => '_Вас наградил(а) %qty% %goods% %usr%_',
                ),
              ),
            ),
          ),
          5 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'event_owner',
                  'format' => NULL,
                  'safe_value' => 'event_owner',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '_Вы наградили %qty% %goods% %users%_',
                  'format' => NULL,
                  'safe_value' => '_Вы наградили %qty% %goods% %users%_',
                ),
              ),
            ),
          ),
          6 => array(
            'field_op_alt' => array(
              'und' => array(
                0 => array(
                  'value' => '_Был(а) награжден(а) %users%_',
                  'format' => NULL,
                  'safe_value' => '_Был(а) награжден(а) %users%_',
                ),
              ),
            ),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'event_channel',
                  'format' => NULL,
                  'safe_value' => 'event_channel',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '_Были нарграждены %users%_',
                  'format' => NULL,
                  'safe_value' => '_Были нарграждены %users%_',
                ),
              ),
            ),
          ),
          7 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_status',
                  'format' => NULL,
                  'safe_value' => 'op_status',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '*Друпликация на %qty% %goods% прошла успешно!* :white_check_mark:\\n\\n*От кого*',
                  'format' => NULL,
                  'safe_value' => '*Друпликация на %qty% %goods% прошла успешно!* :white_check_mark:\\n\\n*От кого*',
                ),
              ),
            ),
          ),
          8 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_status_private',
                  'format' => NULL,
                  'safe_value' => 'op_status_private',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => '*Вас наградили %qty% %goods%!* %currencies%\\n\\n*От кого*',
                  'format' => NULL,
                  'safe_value' => '*Вас наградили %qty% %goods%!* %currencies%\\n\\n*От кого*',
                ),
              ),
            ),
          ),
          9 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_status_remind',
                  'format' => NULL,
                  'safe_value' => 'op_status_remind',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => ':bell: *Вы хотели наградить %qty% %currency%*',
                  'format' => NULL,
                  'safe_value' => ':bell: *Вы хотели наградить %qty% %currency%*',
                ),
              ),
            ),
          ),
          10 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'attach_balance_remind_title',
                  'format' => NULL,
                  'safe_value' => 'attach_balance_remind_title',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Друпликонов на вашем счете',
                  'format' => NULL,
                  'safe_value' => 'Друпликонов на вашем счете',
                ),
              ),
            ),
          ),
          11 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'attach_balance_private_title',
                  'format' => NULL,
                  'safe_value' => 'attach_balance_private_title',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Друпликонов у вас в наличии',
                  'format' => NULL,
                  'safe_value' => 'Друпликонов у вас в наличии',
                ),
              ),
            ),
          ),
          12 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'attach_balance_owner_title',
                  'format' => NULL,
                  'safe_value' => 'attach_balance_owner_title',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Друпликонов осталось',
                  'format' => NULL,
                  'safe_value' => 'Друпликонов осталось',
                ),
              ),
            ),
          ),
          13 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'attach_balance_needed_title',
                  'format' => NULL,
                  'safe_value' => 'attach_balance_needed_title',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Не хватает друпликонов',
                  'format' => NULL,
                  'safe_value' => 'Не хватает друпликонов',
                ),
              ),
            ),
          ),
          14 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_color',
                  'format' => NULL,
                  'safe_value' => 'op_color',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'good',
                  'format' => NULL,
                  'safe_value' => 'good',
                ),
              ),
            ),
          ),
          15 => array(
            'field_op_alt' => array(),
            'field_op_id' => array(
              'und' => array(
                0 => array(
                  'value' => 'op_remind',
                  'format' => NULL,
                  'safe_value' => 'op_remind',
                ),
              ),
            ),
            'field_op_msg' => array(
              'und' => array(
                0 => array(
                  'value' => 'Подарить',
                  'format' => NULL,
                  'safe_value' => 'Подарить',
                ),
              ),
            ),
          ),
        ),
        'field_emoticon' => array(
          'und' => array(
            0 => array(
              'value' => ':drupal:',
              'format' => NULL,
              'safe_value' => ':drupal:',
            ),
          ),
        ),
      ),
    ),
    'field_collection_item:field_limit' => array(
      0 => array(
        'field_active_limit' => array(
          'und' => array(
            0 => array(
              'value' => 20,
            ),
          ),
        ),
        'field_core_limit' => array(
          'und' => array(
            0 => array(
              'value' => 30,
            ),
          ),
        ),
        'field_regular_limit' => array(
          'und' => array(
            0 => array(
              'value' => 10,
            ),
          ),
        ),
        'field_top_limit' => array(
          'und' => array(
            0 => array(
              'value' => 50,
            ),
          ),
        ),
      ),
    ),
    'field_collection_item:field_notifications' => array(
      0 => array(
        'field_react_on' => array(
          'und' => array(
            0 => array(
              'value' => 'first',
              'format' => NULL,
              'safe_value' => 'first',
            ),
            1 => array(
              'value' => 'second',
              'format' => NULL,
              'safe_value' => 'second',
            ),
          ),
        ),
      ),
      1 => array(
        'field_react_on' => array(
          'und' => array(
            0 => array(
              'value' => 'second',
              'format' => NULL,
              'safe_value' => 'second',
            ),
          ),
        ),
      ),
    ),
    'field_collection_item:field_op_limit' => array(
      0 => array(
        'field_collection_item:field_limit' => array(
          0 => array(
            'field_active_limit' => array(
              'und' => array(
                0 => array(
                  'value' => 2,
                ),
              ),
            ),
            'field_core_limit' => array(
              'und' => array(
                0 => array(
                  'value' => 3,
                ),
              ),
            ),
            'field_regular_limit' => array(
              'und' => array(
                0 => array(
                  'value' => 1,
                ),
              ),
            ),
            'field_top_limit' => array(
              'und' => array(
                0 => array(
                  'value' => 3,
                ),
              ),
            ),
          ),
        ),
        'field_op_limit_msg' => array(
          'und' => array(
            0 => array(
              'value' => 'Превышено максимальное колличество жуков для одной операции. Вы можете выдать за раз жуков не больше !qty.',
              'format' => NULL,
              'safe_value' => 'Превышено максимальное колличество жуков для одной операции. Вы можете выдать за раз жуков не больше !qty.',
            ),
          ),
        ),
      ),
    ),
    'type' => 'somi_settings',
  );

  return $config_pages;
}
