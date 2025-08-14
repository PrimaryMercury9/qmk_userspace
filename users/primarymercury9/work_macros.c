#include "work_macros.h"

bool process_work_macros(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case CC_TMUT:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_LCTL("M")));
            }
        return false;

        case CC_TCAM:
            if (record->event.pressed) {
                SEND_STRING (SS_LSFT(SS_LCTL("O")));
            }
        return false;

        case CC_TSHR:
            if (record->event.pressed) {
                SEND_STRING (SS_LSFT(SS_LCTL("E")));
            }
        return false;

        case CC_TEND:
            if (record->event.pressed) {
                SEND_STRING (SS_LSFT(SS_LCTL("H")));
                register_code(KC_MUTE);
                unregister_code(KC_MUTE);
            }
        return false;

        case CC_ANS:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_6) SS_UP(X_LGUI));
                SEND_STRING(SS_DELAY(500) SS_LCTL(SS_LSFT("S")));
                register_code(KC_MUTE);
                unregister_code(KC_MUTE);
            }
        return false;

    // Clear outlook flag
        case MA_CLOF:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_RALT) "HUE");
            }
        return false;

    // Outlook find related
        case MA_OFR:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_F10) SS_UP(X_LSFT) "FC");
            }
        return false;

        case CC_SET:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_0) SS_UP(X_LGUI));
            }
        return false;

        case CC_DT1:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_1) SS_UP(X_LGUI));
            }
        return false;

        case CC_DT2:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_2) SS_UP(X_LGUI));
            }
        return false;

        case CC_DT3:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_3) SS_UP(X_LGUI));
            }
        return false;

        case CC_DT4:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_4) SS_UP(X_LGUI));
            }
        return false;

        case MA_POST:
            if (record->event.pressed) {
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
        return false;

      case CC_LOL:
        if (record->event.pressed) {
            SEND_STRING("(lol)");
        }
        return false;

      case CC_ROFL:
        if (record->event.pressed) {
            SEND_STRING("(rofl)");
        }
        return false;

      case CC_SIGH:
        if (record->event.pressed) {
            SEND_STRING("(sigh)");
        }
        return false;

      case CC_FCPL:
        if (record->event.pressed) {
            SEND_STRING("(facepalm)");
        }
        return false;

      case CC_THUP:
        if (record->event.pressed) {
            SEND_STRING("(thumbsup)");
        }
        return false;

    }
    return true;
}
