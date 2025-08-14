#include QMK_KEYBOARD_H
#include <stdio.h>
#include "quantum.h"
#include "os_detection.h"
#include "private_macros.h"
#include "work_macros.h"


enum anne_pro_layers {
  _BASE,
  _FN1,
  _ARROWS
};

// Macro Declarations
enum local_keycodes {
    CC_EDIT = LOCAL_SAFE_RANGE,// need to create the OS dependant edit macro, check Kyria
};

// Custom Key Deckarations
#define CC_ESC  LT(_ARROWS,KC_ESC)
//#define CC_TAB  LT(_PAGES,KC_TAB)
#define CC_TAB  LCTL_T(KC_TAB)
#define CC_LCTL LCTL_T(KC_ENT)
#define CC_RCTL RCTL_T(KC_ENT)
#define CC_SPC  LT(_FN1,KC_SPC)
#define CC_BT1  KC_AP2_BT1
#define CC_BT2  KC_AP2_BT2
#define CC_BT3  KC_AP2_BT3
#define CC_BT4  KC_AP2_BT4
#define LED_OFF KC_AP_RGB_TOG
#define LED_ON  KC_AP_RGB_MOD
#define LED_INT KC_AP_RGB_VAD
#define LED_SPD KC_AP_RGB_VAI

 const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_BASE] = LAYOUT_60_ansi( /* Base */
    KC_TILD ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,  KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  ,KC_MINS , KC_EQL ,  KC_BSPC  ,
    CC_TAB     ,  KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  ,  KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  , KC_LBRC, KC_RBRC, KC_BSLS,
    CC_ESC      ,  KC_A  ,  KC_S  ,  KC_D  ,  KC_F  ,  KC_G  ,  KC_H  ,  KC_J  ,  KC_K  ,  KC_L  , KC_SCLN, KC_QUOT,     KC_ENT     ,
    SC_LSPO       ,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  ,  KC_N  ,  KC_M  , KC_COMM, KC_DOT , KC_SLSH,        SC_RSPC        ,
    CC_LCTL  , KC_LALT , KC_LGUI ,                        CC_SPC                      , KC_RGUI ,   KC_RALT  ,   CC_ESC ,   CC_RCTL
),

 [_FN1] = LAYOUT_60_ansi( /* Base */
    KC_GRV  , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,  KC_DEL   ,
    _______    , XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_CAPS      ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,  KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  , XXXXXXX,     QK_LEAD    ,
    _______         , DM_REC1, DM_PLY1, DM_RSTP, DM_REC2, DM_PLY2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       _______       ,
    _______  , _______ , _______ ,                       _______                      , _______ ,  _______ ,   _______    ,   _______
),

 [_ARROWS] = LAYOUT_60_ansi( /* Base */
    XXXXXXX , CC_BT1, CC_BT2, CC_BT3, CC_BT4, XXXXXXX, XXXXXXX, XXXXXXX, LED_OFF, LED_ON, LED_INT, LED_SPD, XXXXXXX,  KC_DEL   ,
    _______    , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END, XXXXXXX , XXXXXXX, XXXXXXX , XXXXXXX,
    XXXXXXX      , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP  ,KC_RIGHT, XXXXXXX, XXXXXXX,    CC_EDIT    ,
    _______         , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX       ,
    _______  , _______ , _______ ,                       _______                      , _______ ,  _______ ,   _______    ,   _______
),

};

/*#############################################################################
                                 LEDs           
#############################################################################*/
void keyboard_post_init_user(void) {
    switch (detected_host_os()) {
        //This doesn't work right now for some reason
        case OS_WINDOWS:
            ap2_led_set_foreground_color(0xFF, 0x00, 0xFF);
            break;
        default:
            ap2_led_set_foreground_color(0x00, 0xAA, 0xAA);
            //ap2_led_set_foreground_color(0xFF, 0x00, 0xFF);
            break;
    }
}

/*#############################################################################
                                 Leader           
#############################################################################*/
#if defined(LEADER_ENABLE)
void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
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

    // Clear outlook flag
    if (leader_sequence_three_keys(KC_O, KC_F, KC_F)) {
        SEND_STRING(SS_TAP(X_RALT) "HUE");
        //tap_code16(MA_CLOF);
    }

    // Outlook find related
    if (leader_sequence_three_keys(KC_O, KC_F, KC_R)) {
        SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_F10) SS_UP(X_LSFT) "FC");
        //tap_code16(MA_OFR);
    }

    // Auto Teams response
    if (leader_sequence_one_key(KC_R)) {
        SEND_STRING("Hey, sorry I missed your call, are you still after "
                "something from me? If you are, let me know what it is and I'll"
                " give you a call back when I can.");
        //tap_code16(MA_CLOF);
    }

    if (leader_sequence_one_key(KC_A)) {
        SEND_STRING("(thumbsup)");
    }

    if (leader_sequence_one_key(KC_S)) {
        SEND_STRING("(sigh)");
    }

    if (leader_sequence_one_key(KC_D)) {
        SEND_STRING("(lol)");
    }

    if (leader_sequence_one_key(KC_E)) {
        SEND_STRING("(rofl)");
    }

    if (leader_sequence_one_key(KC_F)) {
        SEND_STRING("(facepalm)");
    }

    if (leader_sequence_two_keys(KC_P, KC_M)) {
        SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_N) SS_UP(X_LCTL) SS_DELAY(250));
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

}
#endif
/*#############################################################################
                              Set Macros           
#############################################################################*/
bool process_local_macros(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        case CC_EDIT:
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
        return true;

    }
    return true;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    /*TODO: Make these work, not sure what's broken at the moment but something
      is stopping this map from triggering these external functions for some
      reason. They seem to import the enums etc properly, but can't run the
      functions, no idea why*/

    //if (!process_private_macros(keycode, record)) return false;
    //if (!process_work_macros(keycode, record)) return false;
    if (!process_local_macros(keycode, record)) return false;

    return true;
};
