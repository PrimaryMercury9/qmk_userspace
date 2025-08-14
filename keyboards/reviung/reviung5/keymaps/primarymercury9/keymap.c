/* Copyright 2021 gtips
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "quantum.h"
#include "os_detection.h"
#include "private_macros.h"

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

__attribute__((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) { return true; }

/*#############################################################################
                            Jiggler stuff
#############################################################################*/
bool is_jiggling = false;

void toggle_jiggler(void) {
    is_jiggling = !is_jiggling; /*flip boolean to true*/
    rgblight_set_layer_state(0, is_jiggling);
}

/* Random number generator */
static uint32_t prng_seed;

void init_prng(void) {
    prng_seed = timer_read32();
}

uint32_t qmk_rand(void) {
    prng_seed = (prng_seed * 1103515245U + 12345U) % 0xFFFFFFFFU;
    return prng_seed;
}

uint32_t random_mouse_interval(void) {
    // Get a random number between 0 and 30000
    uint32_t interval_ms = qmk_rand() % 30001;
    // Shift to 5000 - 35000
    return interval_ms + 5000;
}
/*#############################################################################
                             Define Macros           
#############################################################################*/
enum custom_keycodes {
    CC_JIGG = SAFE_RANGE,
    CC_PLAY,
    CC_NEXT,
    CC_PREV,
    CC_VOLU,
    CC_VOLD,
    CC_MUTE
};
/*#############################################################################
                             Define Combos           
#############################################################################*/
enum combos {
  CO_BOOT,
};
/*#############################################################################
                       Define keymap layer names
#############################################################################*/
enum layers {
    _MEDIA,
};
//#############################################################################
//                             Keymaps
//#############################################################################
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_MEDIA] = LAYOUT(
        CC_JIGG,  CC_PREV,  CC_PLAY,  CC_NEXT,  CC_MUTE
    ),

};
//#############################################################################
//                               Jiggler
//#############################################################################
/*timers*/
uint32_t idle_timeout = 30000; // (start after 30s inactivity)
//uint32_t mouse_interval = 10000; // (jiggle every 10s)
static uint32_t mouse_interval; // (jiggle every *random* milliseconds)

static uint32_t idle_callback(uint32_t trigger_time, void* cb_arg) {
    // now idle
    if(is_jiggling) {
        tap_code(KC_MS_UP);
        tap_code(KC_MS_DOWN);
        tap_code(KC_MS_LEFT);
        tap_code(KC_MS_RIGHT);
    }
    mouse_interval = random_mouse_interval();
    return mouse_interval;
}
//#############################################################################
//                          Combos
//#############################################################################
const uint16_t PROGMEM boot_combo[] = {CC_JIGG, KC_MNXT, COMBO_END};

combo_t key_combos[] = {
  [CO_BOOT] = COMBO(boot_combo, QK_BOOT),
};
//#############################################################################
//                             Encoders
//#############################################################################
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (IS_LAYER_ON(_MEDIA)) {
        tap_code16((clockwise == false) ? CC_VOLU : CC_VOLD);
        }
    }

    return false;
}
//#############################################################################
//                             Lighting
//#############################################################################
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _MEDIA:
        rgblight_setrgb (RGB_CYAN); //Cyan
        break;
    default:
        rgblight_setrgb (RGB_RED); //Magenta
        break;
    }
    return state;
}

const rgblight_segment_t PROGMEM jiggler_led_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_PURPLE}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    jiggler_led_layer
);

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_TEAL);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_layers = my_rgb_layers;
}
/*#############################################################################
                              Set Macros           
#############################################################################*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // on every key event start or extend `idle_callback()` deferred execution after IDLE_TIMEOUT_MS
    // this is used as the timer to trigger the jiggler after a period of inactivity on the keyboard
    static deferred_token idle_token = INVALID_DEFERRED_TOKEN;
        if (!extend_deferred_exec(idle_token, idle_timeout)) {
            idle_token = defer_exec(idle_timeout, idle_callback, NULL);
    }

    switch (keycode) {

        case CC_JIGG:
            if (record->event.pressed) {
                toggle_jiggler();
            }
        break;

        case CC_PLAY:
            if (record->event.pressed) {
                tap_code(KC_MPLY);
                //tap_code(KC_MS_UP);
                //tap_code(KC_MS_DOWN);
                //tap_code(KC_MS_LEFT);
                //tap_code(KC_MS_RIGHT);
            }
        break;

        case CC_NEXT:
            if (record->event.pressed) {
                tap_code(KC_MNXT);
            }
        break;

        case CC_PREV:
            if (record->event.pressed) {
                tap_code(KC_MPRV);
            }
        break;

        case CC_VOLU:
            if (record->event.pressed) {
                tap_code(KC_VOLU);
            }
        break;

        case CC_VOLD:
            if (record->event.pressed) {
                tap_code(KC_VOLD);
            }
        break;

        case CC_MUTE:
            if (record->event.pressed) {
                tap_code(KC_MUTE);
            }
        break;

    }
    return true;
};
