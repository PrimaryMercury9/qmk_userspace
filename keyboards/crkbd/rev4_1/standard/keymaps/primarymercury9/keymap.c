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

#pragma once
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "quantum.h"
#include "os_detection.h"
#include "private_macros.h"
#include "work_macros.h"
#include "mouse_jiggler.h"
#include "transactions.h"

//bool is_jiggling = false;
bool is_leader_active = false;
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

typedef struct _sync_data_t {
    bool is_jiggling;
    bool is_leader_active;
} sync_data_t;


__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

__attribute__((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) { return true; }

/*#############################################################################
                             Define Macros
#############################################################################*/
enum custom_keycodes {
    MACRO_CELL_EDIT = LOCAL_SAFE_RANGE,
    MACRO_BROWSER_BACK,
    MACRO_BROWSER_FORWARD,
    CTRL_BKSP,
    CC_JIGG,
    CC_ATAB,
};

/*#############################################################################
                             Jiggler Toggle
#############################################################################*/
//void toggle_jiggler(void) {
//    is_jiggling = !is_jiggling; /*flip boolean to true*/
//}

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
#define CC_RGUI    LCTL_T(KC_APP)
//#define CC_RGUI    KC_LCTL
#define CC_QUOT    LALT_T(KC_QUOT)

#define CC_HW      MO(_HW)
#define CC_MS      MO(_MOUSE)
#define MS_BACK    MACRO_BROWSER_BACK
#define MS_FWD     MACRO_BROWSER_FORWARD
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

/*#############################################################################
                       Define keymap layer names
#############################################################################*/
enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
    _NUMPAD,
    _HW,
    _MOUSE,
};

//#############################################################################
//                             Keymaps
//#############################################################################
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3_ex2(
  //,-------------------------------------------------------------|     |--------------------------------------------------------------.
     CC_TAB ,  KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  , CC_TMUT,       CC_TSHR,  KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  , KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+-------|     |--------+--------+--------+--------+--------+--------+--------|
     CC_ESC ,  KC_A  ,  KC_S  ,  KC_D  ,  KC_F  ,  KC_G  , CC_TCAM,       CC_TEND,  KC_H  ,  KC_J  ,  KC_K  ,  KC_L  ,KC_SCLN , CC_QUOT,
  //|--------+--------+--------+--------+--------+--------+-------|     |--------+--------+--------+--------+--------+--------+--------|
     KC_LSFT,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  ,                          KC_N  ,  KC_M  , KC_COMM, KC_DOT ,KC_SLSH , KC_RSFT,
  //|--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------|
                                CC_LGUI, CC_BSPC, CC_LENT,                         CC_RENT, CC_SPC , CC_RGUI
                             //`--------------------------|                      |---------------------------'
    ),

    [_NAV] = LAYOUT_split_3x6_3_ex2(
  //,-------------------------------------------------------------|     |--------------------------------------------------------------.
      CC_MS , XXXXXXX, DM_REC1, DM_REC2, XXXXXXX, CC_JIGG, PM_LOGS,       PM_LOGS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_VOLU, QK_LEAD,
  //|--------+--------+--------+--------+--------+--------+-------|     |--------+--------+--------+--------+--------+--------+--------|
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, PM_ACON,       PM_ACON, KC_LEFT, KC_DOWN,  KC_UP , KC_RGHT, KC_MUTE, _______,
  //|--------+--------+--------+--------+--------+--------+-------|     |--------+--------+--------+--------+--------+--------+--------|
     _______, XXXXXXX, DM_PLY1, DM_PLY2, DM_RSTP, XXXXXXX,                         KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_VOLD, _______,
  //|--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------|
                                 CC_HW , KC_DEL , QK_RBT ,                         CC_EDIT, KC_CAPS, CC_JIGG
                             //`--------------------------|                      |---------------------------'

  ),

    [_NUMPAD] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------|    |--------------------------------------------------------------.
     _______, KC_LBRC,  KC_7  ,  KC_8  ,  KC_9  , KC_RBRC, DM_REC1,      DM_REC2, DM_RSTP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------+--------|
     _______, KC_SCLN,  KC_4  ,  KC_5  ,  KC_6  , KC_EQL , DM_PLY1,      DM_PLY2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------+--------|
     _______, KC_GRV ,  KC_1  ,  KC_2  ,  KC_3  , KC_BSLS,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------|
                                KC_DOT ,   KC_0 , KC_MINS,                        _______, _______, _______
                             //`--------------------------|                      |---------------------------'
  ),

    [_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|             |-----------------------------------------------------.
     _______, KC_LPRN, KC_LBRC, KC_LCBR, KC_MINS, KC_PIPE,               KC_EQL , KC_DQT , KC_RCBR, KC_RBRC, KC_RPRN, QK_LEAD,
  //|--------+--------+--------+--------+--------+--------|             |--------+--------+--------+--------+--------+--------|
     _______,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,               KC_6   ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  , _______,
  //|--------+--------+--------+--------+--------+--------|             |--------+--------+--------+--------+--------+--------|
     _______, KC_TILD, KC_COLN, KC_SCLN, KC_UNDS, KC_BSLS,               KC_PLUS, KC_QUOT, XXXXXXX, XXXXXXX, KC_GRV , _______,
  //|--------+--------+--------+--------+--------+--------|             |--------+--------+--------+--------+--------+--------|
                                _______, KC_DEL , _______,               _______, _______, _______
                             //`--------------------------|             |---------------------------'
  ),

    [_MOUSE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------|           |-----------------------------------------------------.
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             MS_BACK, XXXXXXX, XXXXXXX, MS_FWD , XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             MS_LEFT, MS_DOWN,  MS_UP , MS_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX, MS_WHLD, MS_WHLU, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
                                XXXXXXX, XXXXXXX, XXXXXXX,             MS_BTN1, MS_BTN2, XXXXXXX
                             //`--------------------------|           |--------------------------'
    ),

    [_HW] = LAYOUT_split_3x6_3(
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

/*#############################################################################
                              Set Macros
#############################################################################*/
bool process_local_macros(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case MACRO_CELL_EDIT:
            if (record->event.pressed) {
                switch (detected_host_os()) {
                    case OS_MACOS:
                    case OS_IOS:
                        tap_code16(LALT(KC_ENT));
                    break;
                default:
                    tap_code(KC_F2);
                    break;
              }
          }
          break;

        case MACRO_BROWSER_BACK:
            if (record->event.pressed) {
                switch (detected_host_os()) {
                    case OS_MACOS:
                    case OS_IOS:
                        tap_code16(LGUI(KC_LBRC));
                    break;
                default:
                    tap_code16(LALT(KC_LEFT));
                    break;
              }
          }
          break;

        case MACRO_BROWSER_FORWARD:
            if (record->event.pressed) {
                switch (detected_host_os()) {
                    case OS_MACOS:
                    case OS_IOS:
                        tap_code16(LGUI(KC_RBRC));
                    break;
                default:
                    tap_code16(LALT(KC_RIGHT));
                    break;
              }
          }
          break;

        case CC_ATAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            return false;


    }
    return true;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == CC_JIGG && record->event.pressed) {
        toggle_jiggler();
        return false;  // Consume key here
    }
    // Pass key event to the jiggler timer manager
    if (!mouse_jiggler_process_record(keycode, record)) {
        return false;
    }

    if (!process_private_macros(keycode, record)) return false;
    if (!process_work_macros(keycode, record)) return false;
    if (!process_local_macros(keycode, record)) return false;
    return true;
};

/*#############################################################################
                               Leader
#############################################################################*/
#if defined(LEADER_ENABLE)
void leader_start_user(void) {
    // Do something when the leader key is pressed
    is_leader_active = true;
}

void leader_end_user(void) {
    if (leader_sequence_two_keys(KC_P, KC_M)) {
        SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_N) SS_UP(X_LCTL));
        SEND_STRING(SS_DELAY(500));
        SEND_STRING("Post meeting");
        SEND_STRING(SS_TAP(X_TAB));
        SEND_STRING(SS_TAP(X_TAB));
        SEND_STRING(SS_TAP(X_TAB));
        SEND_STRING(SS_TAP(X_TAB));
        SEND_STRING(SS_TAP(X_TAB));
        SEND_STRING(SS_TAP(X_TAB));
        SEND_STRING(SS_TAP(X_DOWN)); //Set to 30 min block
        SEND_STRING(SS_TAP(X_LALT) "HV"); //Set to private
        SEND_STRING(SS_TAP(X_LALT) "HREN" SS_TAP(X_ENT));
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_S) SS_UP(X_LALT));
    }

    // smilies
    if (leader_sequence_two_keys(KC_R, KC_O)) {
        SEND_STRING("(rofl)");
    }

    if (leader_sequence_two_keys(KC_L, KC_O)) {
        SEND_STRING("(lol)");
    }

    if (leader_sequence_two_keys(KC_T, KC_H)) {
        SEND_STRING("(thumbsup)");
    }

    if (leader_sequence_two_keys(KC_S, KC_I)) {
        SEND_STRING("(sigh)");
    }

    if (leader_sequence_two_keys(KC_P, KC_L)) {
        SEND_STRING("(facepalm)");
    }

    // Clear outlook flag
    if (leader_sequence_three_keys(KC_O, KC_F, KC_F)) {
        SEND_STRING(SS_TAP(X_RALT) "HUE");
    }

    // Outlook find related
    if (leader_sequence_three_keys(KC_O, KC_F, KC_R)) {
        SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_F10) SS_UP(X_LSFT) "FC");
    }

    // Selects the current word under the cursor.
    if (leader_sequence_one_key(KC_W)) {
        switch (detected_host_os()) {
            case OS_MACOS:
            case OS_IOS:
                tap_code16(LALT(KC_RIGHT));
                tap_code16(LSFT(LALT(KC_LEFT)));
                //SEND_STRING(SS_LALT(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))));
                break;
            default:
                tap_code16(LCTL(KC_RIGHT));
                tap_code16(LSFT(LCTL(KC_LEFT)));
                break;
        }
    }

    // Selects the current line.
    if (leader_sequence_one_key(KC_V)) {
        switch (detected_host_os()) {
            case OS_MACOS:
            case OS_IOS:
                //SEND_STRING(SS_LCTL("a" SS_LSFT("e")));
                tap_code16(LCTL(KC_A));
                tap_code16(LSFT(LCTL(KC_E)));
                break;
            default:
                //SEND_STRING(SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END)));
                tap_code(KC_HOME);
                tap_code16(LSFT(KC_END));
                break;
        }
    }
    is_leader_active = false;
}

#endif

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (is_jiggling) {
        uint8_t leds_to_light[] = {3, 26};
        for (uint8_t i = 0; i < sizeof(leds_to_light) / sizeof(leds_to_light[0]); i++) {
            uint8_t led = leds_to_light[i];
            if (led >= led_min && led < led_max) {
                rgb_matrix_set_color(led, 0, 255, 0);  // Green color
            }
        }
    }

    //light the bottom buttons a different colour
    switch (detected_host_os()) {
        case OS_WINDOWS:
            rgb_matrix_sethsv_noeeprom(0, 0, 0);
            break;
        case OS_UNSURE:
            break;
        case OS_LINUX:
        case OS_MACOS:
        case OS_IOS: {
            rgb_matrix_sethsv_noeeprom(180, 255, 150);
            uint8_t leds_to_light[] = {0, 7, 8, 21, 22, 23, 30, 31, 44, 45};
            for (uint8_t i = 0; i < sizeof(leds_to_light) / sizeof(leds_to_light[0]); i++) {
                uint8_t led = leds_to_light[i];
                if (led >= led_min && led < led_max) {
                    rgb_matrix_set_color(led, 255, 100, 0);  // Orange color
                }
            }
            uint8_t leds_to_light_2[] = {5, 28};
            for (uint8_t i = 0; i < sizeof(leds_to_light_2) / sizeof(leds_to_light_2[0]); i++) {
                uint8_t led = leds_to_light_2[i];
                if (led >= led_min && led < led_max) {
                    rgb_matrix_set_color(led, 0, 255, 0);  // Green color
                }
            }
         }
            break;
      return true;
    }

    if (layer_state_is(3)) {
        uint8_t leds_to_light[] = {4, 5, 6, 9, 10, 11, 12, 13, 14, 7};
        for (uint8_t i = 0; i < sizeof(leds_to_light) / sizeof(leds_to_light[0]); i++) {
            uint8_t led = leds_to_light[i];
            if (led >= led_min && led < led_max) {
                rgb_matrix_set_color(led, 0, 255, 0);  // Green color
            }
        }
    }

    if (is_leader_active) {
        rgb_matrix_set_color_all(0, 255, 0);
    }

    return false; // Return false to allow other effects to run as well
}


// ─── Slave handler ────────────────────────────────────────────────────────────
void sync_state_slave_handler(uint8_t in_buflen, const void *in_data,
                               uint8_t out_buflen, void *out_data) {
    const sync_data_t *data = (const sync_data_t *)in_data;
    is_jiggling      = data->is_jiggling;
    is_leader_active = data->is_leader_active;
}

// ─── Register handler ─────────────────────────────────────────────────────────
void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    transaction_register_rpc(USER_SYNC_STATE, sync_state_slave_handler);
}

// ─── Master pushes to slave periodically ──────────────────────────────────────
void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        static uint32_t last_sync          = 0;
        static bool     last_jiggling      = false;
        static bool     last_leader_active = false;

        bool state_changed = (is_jiggling      != last_jiggling) ||
                             (is_leader_active != last_leader_active);
        bool keepalive_due = (timer_elapsed32(last_sync) > 500);

        if (state_changed || keepalive_due) {
            sync_data_t data = {
                .is_jiggling      = is_jiggling,
                .is_leader_active = is_leader_active,
            };

            if (transaction_rpc_send(USER_SYNC_STATE, sizeof(data), &data)) {
                last_sync          = timer_read32();
                last_jiggling      = is_jiggling;
                last_leader_active = is_leader_active;
            }
        }
    }
}

//LEDs -> RED when in booloader mode
bool shutdown_user(bool jump_to_bootloader) {
    if (jump_to_bootloader) {
        // Entering bootloader (e.g. QK_BOOT keycode) — set a visible color
        rgb_matrix_set_color_all(RGB_RED);
    } else {
        // Soft reset (QK_REBOOT or QK_CLEAR_EEPROM) — different feedback
        rgb_matrix_set_color_all(RGB_GREEN);
    }
    // REQUIRED: force-flush the LED buffer, otherwise the change never renders
    rgb_matrix_update_pwm_buffers();
    return false; // return false to skip the kb-level function
}
