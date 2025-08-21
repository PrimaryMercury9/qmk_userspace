#include "leader_sequences.h"

#if defined(LEADER_ENABLE)
// Leader active flag
bool is_leader_active = false;

void leader_start_user(void) {
    is_leader_active = true;
}

void leader_end_user(void) {
    if (leader_sequence_two_keys(KC_P, KC_O)) {
        SEND_STRING(SS_LCTL("N") SS_DELAY(250));
        SEND_STRING("Post meeting");
        for (int i = 0; i < 7; i++) {
            SEND_STRING(SS_TAP(X_TAB));
        }
        SEND_STRING(SS_TAP(X_DOWN)); // Set to 30 min block
        SEND_STRING(SS_TAP(X_LALT) "HV"); // Set to private
        SEND_STRING(SS_TAP(X_LALT) "HREN" SS_TAP(X_ENT));
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_S) SS_UP(X_LALT));
    }

    if (leader_sequence_three_keys(KC_V, KC_I, KC_M)) {
        toggle_vim_mode();
    }
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
    if (leader_sequence_three_keys(KC_O, KC_F, KC_F)) {
        SEND_STRING(SS_TAP(X_RALT) "HUE");
    }
    if (leader_sequence_three_keys(KC_O, KC_F, KC_R)) {
        SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_F10) SS_UP(X_LSFT) "FC");
    }
    if (leader_sequence_one_key(KC_W)) {
        switch (detected_host_os()) {
            case OS_MACOS:
            case OS_IOS:
                tap_code16(LALT(KC_RIGHT));
                tap_code16(LSFT(LALT(KC_LEFT)));
                break;
            default:
                tap_code16(LCTL(KC_RIGHT));
                tap_code16(LSFT(LCTL(KC_LEFT)));
                break;
        }
    }
    if (leader_sequence_one_key(KC_V)) {
        switch (detected_host_os()) {
            case OS_MACOS:
            case OS_IOS:
                tap_code16(LCTL(KC_A));
                tap_code16(LSFT(LCTL(KC_E)));
                break;
            default:
                tap_code(KC_HOME);
                tap_code16(LSFT(KC_END));
                break;
        }
    }

    is_leader_active = false;
}

#endif
