#include QMK_KEYBOARD_H

enum custom_keycodes {
  BIN0 = SAFE_RANGE,
  BIN1,
  BIN_RESET
};

uint8_t bits_collected = 0;
char binary_char = 0;

void push_binary_value(uint8_t value) {
    binary_char <<= 1;
    binary_char |= value;
    bits_collected++;
    if (bits_collected == 8) {
        send_char(binary_char);
        binary_char = 0;
        bits_collected = 0;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BIN0:
            if (record->event.pressed) {
                push_binary_value(0);
            }
            return false;
            break;
        case BIN1:
            if (record->event.pressed) {
                push_binary_value(1);
            }
            return false;
            break;
        case BIN_RESET:
            if (record->event.pressed) {
                bits_collected = 0;
                binary_char = 0;
            }
            return false;
            break;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_default (
        BIN0,
        BIN1 
        )
};

