// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "print.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┐
     * │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │
     * ├───┼───┼───┼───┼───┼───┤
     * │` ~│ Q │ W │ E │ R │ T │
     * ├───┼───┼───┼───┼───┼───┤
     * │TAB│ A │ S │ D │ F │ G │
     * ├───┼───┼───┼───┼───┼───┤
     * │SHF│ Z │ X │ C │ V │ B │
     * ├───┼───┼───┼───┼───┼───┤
     * │CTR│WIN│ALT│F11│F12│F 2│
     * ├───┼───┼───┼───┼───┼───┤
     * │   │   │   │BCK│SPC│ENT│
     * └───┴───┴───┴───┴───┴───┘

     * ┌───┬───┬───┬───┬───┬───┐
     * │ 6 │ 7 │ 8 │ 9 │ 0 │- _│
     * ├───┼───┼───┼───┼───┼───┤
     * │ Y │ U │ I │ O │ P │= +│
     * ├───┼───┼───┼───┼───┼───┤
     * │ H │ J │ K │ L │; :│' "│
     * ├───┼───┼───┼───┼───┼───┤
     * │ N │ M │, <│. >│/ ?│\ |│
     * ├───┼───┼───┼───┼───┼───┤
     * │HOM│UP │LAY│{ [│} ]│SUP│
     * ├───┼───┼───┼───┼───┼───┤
     * │LEF│DOW│RIG│   │   │   │
     * └───┴───┴───┴───┴───┴───┘
     
     */ 
    [0] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,
        KC_GRV, KC_Q, KC_W, KC_E, KC_R, KC_T,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,
        KC_LCTL, KC_LGUI, KC_LALT, KC_F11, KC_F12, KC_F2,
        KC_NO, KC_NO, KC_NO, KC_BSPC, KC_SPC, KC_ENT,

        KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,
        KC_Y, KC_U, KC_I, KC_O, KC_P, KC_EQL,
        KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
        KC_HOME, KC_UP, KC_F13, KC_LBRC, KC_RBRC, KC_PGUP,
        KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_NO
    )
};


void keyboard_post_init_user(void) { 
    debug_enable = true;
    debug_matrix = true;
    print("Keyboard startup complete\n");
    if (is_keyboard_master())
        print("Master\n");
    else
        print("Slave\n");

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 
  return true;
}
/*
void matrix_scan_user(void) { 
    if (is_keyboard_master())
        print("Master\n");
    else
        print("Slave\n");
}
*/

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) }
};
#endif

#ifdef OLED_ENABLE
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master())
        print("OLED task running on master side\n");
    else
        print("OLED task running on slave side\n");
    render_logo();
    return false;
}
#endif