#include QMK_KEYBOARD_H

enum layers {
    _BASE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     *  Undo | Redo  | Cut  | Prev
     *  Copy | Paste | Save | Play
     *  All  | Find  | Mute | Next
    */
    [_BASE] = LAYOUT(
        C(KC_Z), C(KC_Y), C(KC_X), KC_MPRV,
        C(KC_C), C(KC_V), C(KC_S), KC_MPLY,
        C(KC_A), C(KC_F), KC_MUTE, KC_MNXT
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM keymaps[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = {ENCODER_CCW_CW(KC_COLD, KC_VOLU)}
};
#endif

#if defined(OLED_ENABLE)
static uint16_t keypress_count = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && keypress_count < UINT16_MAX) {
        keypress_count++;
    }
    return true;
}

bool oled_task_user(void) {
    oled_write_P(PSTR("Kira Hackpad\n"), false);
    oled_write_P(PSTR("edit + media\n"), false);
    oled_write_P(PSTR("keys: "), false);
    oled_write(get_u16_str(keypress_count, ' '), false);
    return false;
}
#endif