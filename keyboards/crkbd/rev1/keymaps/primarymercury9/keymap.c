/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "quantum.h"
#include "os_detection.h"
#include "private_macros.h"
#include "work_macros.h"


bool is_jiggling = false;
bool is_leader_active = false;
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

__attribute__((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) { return true; }

/*#############################################################################
                             Define Macros
#############################################################################*/
enum custom_keycodes {
    MACRO_CELL_EDIT = LOCAL_SAFE_RANGE,
    CTRL_BKSP,
    CC_JIGG,
    CC_ATAB,
};

/*#############################################################################
                             Jiggler Toggle
#############################################################################*/
void toggle_jiggler(void) {
    is_jiggling = !is_jiggling; /*flip boolean to true*/
}

/*#############################################################################
                                 Aliases
#############################################################################*/
#define CC_TAB     LCTL_T(KC_TAB)
#define CC_ESC     LT(_NAV, KC_ESC)
#define CC_LGUI    LGUI_T(KC_ESC)
#define CC_BSPC    LT(_SYM, KC_BSPC)
#define CC_LENT    KC_TAB

#define CC_RENT    LT(_NUMPAD, KC_ENT)
#define CC_SPC     LT(_SYM, KC_SPC)
//#define CC_RGUI    LCTL_T(KC_DEL)
#define CC_RGUI    KC_LCTL
#define CC_QUOT    LALT_T(KC_QUOT) 

#define CC_HW    MO(_HW)
#define CC_EDIT    MACRO_CELL_EDIT

//#############################################################################
//                            Define Tap Dance
//#############################################################################
#if defined(TAP_DANCE_ENABLE)
enum {
    TD_QCAPS,
};

//#############################################################################
//                             Set Tap Dance
//#############################################################################
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Q, twice for Caps Lock
    [TD_QCAPS] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_CAPS),
};

#endif

//#############################################################################
//                          Define Combos
//#############################################################################
#if defined(COMBO_ENABLE)
enum combo_events {
    CO_BKSP,
    CO_F1,
    CO_F2,
    CO_F3,
    CO_F4,
    CO_F5,
    CO_F6,
    CO_F7,
    CO_F8,
    CO_F9,
    CO_F10,
    CO_F11,
    CO_F12,
    CO_ANS,
    CO_MUTE,
};
#endif
/*#############################################################################
                       Define keymap layer names
#############################################################################*/
enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
    _NUMPAD,
    _HW,
};

//#############################################################################
//                             Keymaps
//#############################################################################
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|             |-----------------------------------------------------.
     CC_TAB ,  KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  ,                KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  , KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|             |--------+--------+--------+--------+--------+--------|
     CC_ESC ,  KC_A  ,  KC_S  ,  KC_D  ,  KC_F  ,  KC_G  ,                KC_H  ,  KC_J  ,  KC_K  ,  KC_L  ,KC_SCLN , CC_QUOT,
  //|--------+--------+--------+--------+--------+--------|             |--------+--------+--------+--------+--------+--------|
     KC_LSFT,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  ,               CC_TCAM, CC_TEND,  KC_N  ,  KC_M  , KC_COMM, KC_DOT ,KC_SLSH , KC_RSFT,
  //|--------+--------+--------+--------+--------+--------|             |--------+--------+--------+--------+--------+--------|
                                CC_LGUI, CC_BSPC, CC_LENT,               CC_RENT, CC_SPC , CC_RGUI 
                             //`--------------------------|             |---------------------------'
    ),

    [_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|             |-----------------------------------------------------.
     _______, XXXXXXX, DM_REC1, DM_REC2, XXXXXXX, CC_JIGG,               KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_VOLU, QK_LEAD,
  //|--------+--------+--------+--------+--------+--------|             |--------+--------+--------+--------+--------+--------|
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,               KC_LEFT, KC_DOWN,  KC_UP , KC_RGHT, KC_MUTE, _______,
  //|--------+--------+--------+--------+--------+--------|             |--------+--------+--------+--------+--------+--------|
     _______, XXXXXXX, DM_PLY1, DM_PLY2, DM_RSTP, XXXXXXX,               KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_VOLD, _______,
  //|--------+--------+--------+--------+--------+--------|             |--------+--------+--------+--------+--------+--------|
                                 CC_HW , KC_DEL , QK_RBT ,               CC_EDIT, KC_CAPS, _______, _______, _______ 
                             //`--------------------------|             |---------------------------'

  ),

    [_NUMPAD] = LAYOUT_split_3x6_3( /*TODO: this map*/
  //,-----------------------------------------------------|             |-----------------------------------------------------.
     _______, KC_LBRC,  KC_7  ,  KC_8  ,  KC_9  , KC_RBRC,               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|             |--------+--------+--------+--------+--------+--------|
     _______, KC_SCLN,  KC_4  ,  KC_5  ,  KC_6  , KC_EQL ,               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|             |--------+--------+--------+--------+--------+--------|
     _______, KC_GRV ,  KC_1  ,  KC_2  ,  KC_3  , KC_BSLS,               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|             |--------+--------+--------+--------+--------+--------|
                                KC_DOT ,   KC_0 , KC_MINS,               _______, _______, _______, _______,_______ 
                             //`--------------------------|             |---------------------------'
  ),

    [_SYM] = LAYOUT_split_3x6_3(/*TODO: this map*/
  //,-----------------------------------------------------|             |-----------------------------------------------------.
     _______, KC_LPRN, KC_LBRC, KC_LCBR, KC_MINS, KC_PIPE,               KC_EQL , KC_DQT , KC_RCBR, KC_RBRC, KC_RPRN, QK_LEAD,
  //|--------+--------+--------+--------+--------+--------|             |--------+--------+--------+--------+--------+--------|
     _______,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,               KC_6   ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  , _______,
  //|--------+--------+--------+--------+--------+--------|             |--------+--------+--------+--------+--------+--------|
     _______, KC_TILD, KC_COLN, KC_SCLN, KC_UNDS, KC_BSLS,               KC_PLUS, KC_QUOT, XXXXXXX, XXXXXXX, KC_GRV , _______,
  //|--------+--------+--------+--------+--------+--------|             |--------+--------+--------+--------+--------+--------|
                                _______, KC_DEL , _______,               _______, _______, _______,
                             //`--------------------------|             |---------------------------'
  ),

    [_HW] = LAYOUT_split_3x6_3(/*TODO: this map*/
  //,-----------------------------------------------------|              |-----------------------------------------------------.
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,                QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|              |--------+--------+--------+--------+--------+--------|
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_TOG, _______,
  //|--------+--------+--------+--------+--------+--------|              |--------+--------+--------+--------+--------+--------|
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                XXXXXXX, RGB_SAD, RGB_HUD, RGB_VAD, RGB_MOD, _______,
  //|--------+--------+--------+--------+--------+--------|              |--------+--------+--------+--------+--------+--------|
                                _______, _______, _______,                _______, _______, _______ 
                             //`--------------------------|              |---------------------------'
  )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif
