#include QMK_KEYBOARD_H
#include <stdio.h>
#include "quantum.h"
#include "os_detection.h"
#include "gpio.h" //required to turn off the Liatris LED
#include "transactions.h"
#include "qmk-vim/src/vim.h"
#include "qmk-vim/src/modes.h" //required to display which vim mode is active on OLED

#include "private_macros.h"
#include "work_macros.h"
#include "mouse_jiggler.h"


//Turn off Liatris power LED
void keyboard_pre_init_user(void) {
    gpio_set_pin_output(24);
    gpio_write_pin_high(24);
}

//bool is_jiggling = false;
bool is_leader_active = false;
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

__attribute__((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) { return true; }

/*#############################################################################
                                 Combos
#############################################################################*/
#if defined(COMBO_ENABLE)
enum combo_index {
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
    CO_MUTE
};

// Define your combo key codes.
const uint16_t PROGMEM combf1[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM combf2[] = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM combf3[] = {KC_Z, KC_V, COMBO_END};
const uint16_t PROGMEM combf4[] = {KC_Z, KC_B, COMBO_END};
const uint16_t PROGMEM combf5[] = {KC_Z, KC_S, COMBO_END};
const uint16_t PROGMEM combf6[] = {KC_Z, KC_D, COMBO_END};
const uint16_t PROGMEM combf7[] = {KC_Z, KC_F, COMBO_END};
const uint16_t PROGMEM combf8[] = {KC_Z, KC_G, COMBO_END};
const uint16_t PROGMEM combf9[] = {KC_Z, KC_W, COMBO_END};
const uint16_t PROGMEM combf10[] = {KC_Z, KC_E, COMBO_END};
const uint16_t PROGMEM combf11[] = {KC_Z, KC_R, COMBO_END};
const uint16_t PROGMEM combf12[] = {KC_Z, KC_T, COMBO_END};
const uint16_t PROGMEM mute[] = {CC_TMUT, CC_TSHR, COMBO_END};
const uint16_t PROGMEM answer[] = {CC_TCAM, CC_TEND, COMBO_END};

// Define the combos.
combo_t key_combos[] = {
    [CO_F1]   = COMBO(combf1,  KC_F1),
    [CO_F2]   = COMBO(combf2,  KC_F2),
    [CO_F3]   = COMBO(combf3,  KC_F3),
    [CO_F4]   = COMBO(combf4,  KC_F4),
    [CO_F5]   = COMBO(combf5,  KC_F5),
    [CO_F6]   = COMBO(combf6,  KC_F6),
    [CO_F7]   = COMBO(combf7,  KC_F7),
    [CO_F8]   = COMBO(combf8,  KC_F8),
    [CO_F9]   = COMBO(combf9,  KC_F9),
    [CO_F10]  = COMBO(combf10, KC_F10),
    [CO_F11]  = COMBO(combf11, KC_F11),
    [CO_F12]  = COMBO(combf12, KC_F12),
    [CO_ANS]  = COMBO(answer,  CC_ANS),
    [CO_MUTE] = COMBO(mute,    KC_MUTE),
};
#endif

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

#define CC_HW      MO(_HW)
#define CC_EDIT    MACRO_CELL_EDIT
#define CC_MOUS    MO(_MOUSE)

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

    [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------------------------|           |-----------------------------------------------------------------------.
     CC_TAB ,  KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  ,                                                  KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  , KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
     CC_ESC ,  KC_A  ,  KC_S  ,  KC_D  ,  KC_F  ,  KC_G  ,     /*ANS*/                      /*MUT E*/       KC_H  ,  KC_J  ,  KC_K  ,  KC_L  ,KC_SCLN , CC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
     KC_LSFT,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  , CC_TMUT, CC_TSHR,             CC_TCAM, CC_TEND,  KC_N  ,  KC_M  , KC_COMM, KC_DOT ,KC_SLSH , KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
                                CC_ATAB, KC_LALT, CC_LGUI, CC_BSPC, CC_LENT,             CC_RENT, CC_SPC , CC_RGUI, KC_LALT,  KC_APP
                             //`--------------------------------------------|           |---------------------------------------------'
    ),

    [_NAV] = LAYOUT(
  //,-----------------------------------------------------------------------|           |-----------------------------------------------------------------------.
     _______, XXXXXXX, DM_REC1, DM_REC2, XXXXXXX, CC_JIGG,                                                 KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_VOLU, QK_LEAD,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                                 KC_LEFT, KC_DOWN,  KC_UP , KC_RGHT, KC_MUTE, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
     _______, XXXXXXX, DM_PLY1, DM_PLY2, DM_RSTP, XXXXXXX, KC_VOLD, KC_VOLU,            KC_PGDN , KC_PGUP, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_VOLD, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
                                _______, CC_MOUS,  CC_HW , KC_DEL , QK_RBT ,            CC_EDIT , KC_CAPS, _______, _______, _______
                             //`--------------------------------------------|           |---------------------------------------------'
    ),

    [_NUMPAD] = LAYOUT(
  //,-----------------------------------------------------------------------|           |-----------------------------------------------------------------------.
     _______, KC_LBRC,  KC_7  ,  KC_8  ,  KC_9  , KC_RBRC,                                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
     _______, KC_SCLN,  KC_4  ,  KC_5  ,  KC_6  , KC_EQL ,                                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
     _______, KC_GRV ,  KC_1  ,  KC_2  ,  KC_3  , KC_BSLS, XXXXXXX, XXXXXXX,             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
                                _______, _______, KC_DOT ,   KC_0 , KC_MINS,             _______, _______, _______, _______, _______
                             //`--------------------------------------------|           |---------------------------------------------'
    ),

    [_SYM] = LAYOUT(
  //,-----------------------------------------------------------------------|           |-----------------------------------------------------------------------.
     _______, KC_LPRN, KC_LBRC, KC_LCBR, KC_MINS, KC_PIPE,                                                 KC_EQL , KC_DQT , KC_RCBR, KC_RBRC, KC_RPRN, QK_LEAD,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
     _______,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,                                                 KC_6   ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  , _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
     _______, KC_TILD, KC_COLN, KC_SCLN, KC_UNDS, KC_BSLS, XXXXXXX, XXXXXXX,             XXXXXXX, XXXXXXX, KC_PLUS, KC_QUOT, XXXXXXX, XXXXXXX, KC_GRV , _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
                                _______, _______, _______, KC_DEL , _______,             _______, _______, _______, _______, _______
                             //`--------------------------------------------|           |---------------------------------------------'
    ),

    [_HW] = LAYOUT(
  //,-----------------------------------------------------------------------|           |-----------------------------------------------------------------------.
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,                                                 QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                                 RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_TOG, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             PM_ACON, PM_LOGS, XXXXXXX, RGB_SAD, RGB_HUD, RGB_VAD, RGB_MOD, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
                                _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______
                             //`--------------------------------------------|           |---------------------------------------------'
    ),

    [_MOUSE] = LAYOUT(
  //,-----------------------------------------------------------------------|           |-----------------------------------------------------------------------.
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                                 MS_LEFT, MS_DOWN,  MS_UP , MS_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX, XXXXXXX, XXXXXXX, MS_WHLD, MS_WHLU, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------+--------+--------|
                                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             MS_BTN1, MS_BTN2, XXXXXXX, XXXXXXX, XXXXXXX
                             //`--------------------------------------------|           |---------------------------------------------'
    ),

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
    //Vim mode
    if (!process_vim_mode(keycode, record)) return false;

    return true;
};

//#############################################################################
//                           Auto Shift
//#############################################################################
#if defined(AUTO_SHIFT_ENABLE)
uint16_t get_autoshift_timeout(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case AUTO_SHIFT_NUMERIC:
            return get_generic_autoshift_timeout();
        case AUTO_SHIFT_SPECIAL:
            return 2 * get_generic_autoshift_timeout() + 1;
        case AUTO_SHIFT_ALPHA:
            return 2 * get_generic_autoshift_timeout() + 1;
        default:
            return get_generic_autoshift_timeout();
    }
}
#endif

//#############################################################################
//                             RGB
//#############################################################################
#if defined(RGB_MATRIX_ENABLE)
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _NAV:
            rgb_matrix_sethsv_noeeprom(100, 255, 255);
            break;
        case _SYM:
            rgb_matrix_sethsv_noeeprom(140, 255, 255);
            break;
        case _HW:
            rgb_matrix_sethsv_noeeprom(5, 255, 255);
            break;
        case _NUMPAD:
            rgb_matrix_sethsv_noeeprom(245, 255, 255);
            break;
        case _MOUSE:
            rgb_matrix_sethsv_noeeprom(165, 255, 255);
            break;
        case _QWERTY:
        default:
            rgb_matrix_sethsv_noeeprom(125, 255, 255);
            break;
    }
  return state;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (is_jiggling) {
        uint8_t leds_to_light[] = {25};
        for (int i = 0; i < sizeof(leds_to_light); i++) {
            uint8_t led = leds_to_light[i];
            if (led >= led_min && led < led_max) {
                rgb_matrix_set_color(led, 0, 255, 0);  // Green color
            }
        }
    }

    if (is_leader_active) {
        uint8_t leds_to_light[] = {61};
        for (int i = 0; i < sizeof(leds_to_light); i++) {
            uint8_t led = leds_to_light[i];
            if (led >= led_min && led < led_max) {
                rgb_matrix_set_color(led, 0, 255, 0);  // Green color
            }
        }
    }
    return false; // Return false to allow other effects to run as well
}

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgb_matrix_enable_noeeprom();
    rgb_matrix_sethsv_noeeprom(125, 255, 255);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
}
#endif

/*#############################################################################
                                  OLED
#############################################################################*/
#if defined(OLED_ENABLE) && defined(WPM_ENABLE)

char wpm_str[12];
uint16_t wpm_graph_timer = 0;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

void render_os(void) {
    switch (detected_host_os()) {
        case OS_IOS:
            oled_write_P(PSTR("OS: IOS"), false);
            break;
        case OS_MACOS:
            oled_write_P(PSTR("OS: MacOS"), false);
            break;
        case OS_LINUX:
            oled_write_P(PSTR("OS: Linux"), false);
            break;
        case OS_WINDOWS:
           oled_write_P(PSTR("OS: Windows"), false);
            break;
        default:
            oled_write_P(PSTR("OS: UKN"), false);
            break;
    }
}

void render_vim_mode(void) {
    if (vim_mode_enabled()) {
        switch (get_vim_mode()) {
            case NORMAL_MODE:
                oled_write_P(PSTR("VIM: NORMAL"), false);
                break;
            case INSERT_MODE:
                oled_write_P(PSTR("VIM: INSERT"), false);
                break;
            case VISUAL_MODE:
                oled_write_P(PSTR("VIM: VISUAL"), false);
                break;
            case VISUAL_LINE_MODE:
                oled_write_P(PSTR("VIM: VISUAL LINE"), false);
                break;
            default:
                oled_write_P(PSTR("VIM: ??UNKNOWN??"), false);
                break;
        }
    } else {
        oled_write_P(PSTR("VIM: OFF"), false);
    }
}

static void render_status(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            render_os();
            break;
        case _NAV:
            oled_write_P(PSTR("Layer: NAV"), false);
            break;
        case _SYM:
            oled_write_P(PSTR("Layer: SYMBOLS"), false);
            break;
        case _NUMPAD:
            oled_write_P(PSTR("Layer: NUMPAD"), false);
            break;
        case _HW:
            oled_write_P(PSTR("Layer: HARDWARE"), false);
            break;
        case _MOUSE:
            oled_write_P(PSTR("Layer: MOUSE"), false);
            break;
        default:
            oled_write_P(PSTR("Layer: Undefined"), false);
            break;
    }

    //Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("   "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS ") : PSTR("   "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCRL") : PSTR("   "), false);
}

void render_wpm(void) {
    oled_set_cursor(0, 4);
    oled_write_P(PSTR("WPM: "), false);
    oled_set_cursor(5, 4);
    oled_write(get_u8_str(get_current_wpm(), '0'), false);
    oled_write(wpm_str, false);
}

void render_jiggling(void) {
    if(is_jiggling){
        oled_write_P(PSTR("JIGGLING"), false);
    }
}

void render_leader(void) {
    if(is_leader_active){
        oled_write_P(PSTR("LEADER WAITING"), false);
    }
}

void render_led_hue(void) {
    hsv_t current_hsv = rgb_matrix_get_hsv();
    uint8_t hue = current_hsv.h;
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "HUE: %3d", hue);
    oled_write(buffer, false);
}

static const char PROGMEM windows_logo_1[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
    0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0,
    0xf0, 0xf0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xfc, 0xfc, 0xfc, 0xfc,
};
static const char PROGMEM windows_logo_2[] = {
    0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};
static const char PROGMEM windows_logo_3[] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};
static const char PROGMEM windows_logo_4[] = {
    0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
    0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00,
    0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
    0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
};
static const char PROGMEM windows_logo_5[] = {
    0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc,
    0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00,
    0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc,
    0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc,
};
static const char PROGMEM windows_logo_6[] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};
static const char PROGMEM windows_logo_7[] = {
    0x3f, 0x3f, 0x3f, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};
static const char PROGMEM windows_logo_8[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0f, 0x0f, 0x0f, 0x0f,
    0x0f, 0x0f, 0x0f, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f,
};

void render_windows_logo(void) {
    oled_set_cursor(5, 0);
    oled_write_raw_P(windows_logo_1, sizeof(windows_logo_1));
    oled_set_cursor(5, 1);
    oled_write_raw_P(windows_logo_2, sizeof(windows_logo_2));
    oled_set_cursor(5, 2);
    oled_write_raw_P(windows_logo_3, sizeof(windows_logo_3));
    oled_set_cursor(5, 3);
    oled_write_raw_P(windows_logo_4, sizeof(windows_logo_4));
    oled_set_cursor(5, 4);
    oled_write_raw_P(windows_logo_5, sizeof(windows_logo_5));
    oled_set_cursor(5, 5);
    oled_write_raw_P(windows_logo_6, sizeof(windows_logo_6));
    oled_set_cursor(5, 6);
    oled_write_raw_P(windows_logo_7, sizeof(windows_logo_7));
    oled_set_cursor(5, 7);
    oled_write_raw_P(windows_logo_8, sizeof(windows_logo_8));
}

static const char PROGMEM apple_logo_1[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0x7f, 0x0f, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const char PROGMEM apple_logo_2[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x7c, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const char PROGMEM apple_logo_3[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfc, 0xfe,
    0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfc, 0xfc, 0xfc,
    0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0xfe, 0xfe, 0xfc, 0xf8, 0x70, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const char PROGMEM apple_logo_4[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x0f, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const char PROGMEM apple_logo_5[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfd, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const char PROGMEM apple_logo_6[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xfe, 0xf8, 0xf0, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const char PROGMEM apple_logo_7[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x3f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const char PROGMEM apple_logo_8[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x0f,
    0x1f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f,
    0x1f, 0x1f, 0x1f, 0x3f, 0x3f, 0x3f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f,
    0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

void render_apple_logo(void) {
    oled_set_cursor(5, 0);
    oled_write_raw_P(apple_logo_1, sizeof(apple_logo_1));
    oled_set_cursor(5, 1);
    oled_write_raw_P(apple_logo_2, sizeof(apple_logo_2));
    oled_set_cursor(5, 2);
    oled_write_raw_P(apple_logo_3, sizeof(apple_logo_3));
    oled_set_cursor(5, 3);
    oled_write_raw_P(apple_logo_4, sizeof(apple_logo_4));
    oled_set_cursor(5, 4);
    oled_write_raw_P(apple_logo_5, sizeof(apple_logo_5));
    oled_set_cursor(5, 5);
    oled_write_raw_P(apple_logo_6, sizeof(apple_logo_6));
    oled_set_cursor(5, 6);
    oled_write_raw_P(apple_logo_7, sizeof(apple_logo_7));
    oled_set_cursor(5, 7);
    oled_write_raw_P(apple_logo_8, sizeof(apple_logo_8));
}

static const char PROGMEM linux_logo_1[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf0, 0xf8, 0xfc, 0xfe, 0xfe, 0xfe, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xf8, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const char PROGMEM linux_logo_2[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc7, 0x31, 0x79, 0xf1, 0xc3, 0x7f, 0x7f, 0x6f,
    0xc1, 0xf1, 0xf8, 0xf8, 0x81, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const char PROGMEM linux_logo_3[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x7f, 0x0f, 0x19, 0x30, 0x60, 0x60, 0x20, 0x20,
    0x10, 0x10, 0x08, 0x0d, 0x07, 0x07, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xf0, 0xc0, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const char PROGMEM linux_logo_4[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0xe0, 0xf8, 0xfc, 0x1e, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x3f, 0xff, 0xff, 0xff, 0xfe, 0xfc,
    0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const char PROGMEM linux_logo_5[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0,
    0xfe, 0xff, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0f, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfc, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const char PROGMEM linux_logo_6[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x36, 0x1f, 0x3f,
    0x3f, 0xfc, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x70, 0x30, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x7f, 0xef, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const char PROGMEM linux_logo_7[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0xfe, 0x33, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x07, 0x0f, 0x3f, 0x7f, 0xfe, 0xbc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xe0, 0xff, 0xff, 0x0c, 0x00, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x01, 0x00, 0x03, 0x0f, 0x18, 0x90, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static const char PROGMEM linux_logo_8[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x0c, 0x0c, 0x08, 0x08, 0x18, 0x18, 0x18, 0x10, 0x30,
    0x30, 0x20, 0x60, 0x60, 0x40, 0xc0, 0x60, 0x71, 0x7f, 0x1f, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x0e,
    0x0e, 0x0e, 0x0e, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x3f, 0x7f, 0xff, 0xe0, 0xc0, 0xc0, 0xe0, 0x60,
    0x30, 0x18, 0x1c, 0x0c, 0x06, 0x06, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

void render_linux_logo(void) {
    oled_set_cursor(5, 0);
    oled_write_raw_P(linux_logo_1, sizeof(linux_logo_1));
    oled_set_cursor(5, 1);
    oled_write_raw_P(linux_logo_2, sizeof(linux_logo_2));
    oled_set_cursor(5, 2);
    oled_write_raw_P(linux_logo_3, sizeof(linux_logo_3));
    oled_set_cursor(5, 3);
    oled_write_raw_P(linux_logo_4, sizeof(linux_logo_4));
    oled_set_cursor(5, 4);
    oled_write_raw_P(linux_logo_5, sizeof(linux_logo_5));
    oled_set_cursor(5, 5);
    oled_write_raw_P(linux_logo_6, sizeof(linux_logo_6));
    oled_set_cursor(5, 6);
    oled_write_raw_P(linux_logo_7, sizeof(linux_logo_7));
    oled_set_cursor(5, 7);
    oled_write_raw_P(linux_logo_8, sizeof(linux_logo_8));
}

void render_os_logo(void) {
    switch (detected_host_os()) {
        case OS_IOS:
        case OS_MACOS:
            render_apple_logo();
            break;
        case OS_LINUX:
            render_linux_logo();
            break;
        case OS_WINDOWS:
            render_windows_logo();
            break;
        default:
            oled_write_P(PSTR(""), false);
            break;
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_clear();
        oled_set_cursor(0, 0);
        render_vim_mode();
        oled_set_cursor(0, 2);
        render_status();
        oled_set_cursor(0, 4);
        render_wpm();
        //render_led_hue();
        oled_set_cursor(0, 6);
        render_jiggling();
        oled_set_cursor(0, 6);
        render_leader();
    } else {
        //oled_clear();
        render_os_logo();
        //oled_set_cursor(0, 6);
        //render_jiggling();
        }
    return true;
}

#endif

//#############################################################################
//                             Encoders
//#############################################################################
#if defined(ENCODER_ENABLE)
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (IS_LAYER_ON(_QWERTY)) {
            if (clockwise) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                tap_code(KC_TAB);
            } else {
                 if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
            alt_tab_timer = timer_read();
            tap_code16(S(KC_TAB)); // Shift+Tab for reverse cycling
            }
        }

        if (IS_LAYER_ON(_NAV)) {
            if (clockwise) {
                tap_code(MS_WHLD);
            } else {
                tap_code(MS_WHLU);
            }
        }
    }

    if (index == 1) {
        if (IS_LAYER_ON(_QWERTY)) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        }
        if (IS_LAYER_ON(_NAV)) {
            if (clockwise) {
                tap_code(MS_WHLD);
            } else {
                tap_code(MS_WHLU);
            }
        }
    }

    return false;
}
#endif

/*#############################################################################
                            AltTab Timer
#############################################################################*/
void matrix_scan_user(void) {
    if (is_alt_tab_active && timer_elapsed(alt_tab_timer) > 1000) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
    }
}

/*#############################################################################
                               Leader
#############################################################################*/
#if defined(LEADER_ENABLE)
void leader_start_user(void) {
    // Do something when the leader key is pressed
    is_leader_active = true;
}

void leader_end_user(void) {
    if (leader_sequence_two_keys(KC_P, KC_O)) {
        SEND_STRING(SS_LCTL("N") SS_DELAY(250));
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

    if (leader_sequence_three_keys(KC_V, KC_I, KC_M)) {
        toggle_vim_mode();
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
