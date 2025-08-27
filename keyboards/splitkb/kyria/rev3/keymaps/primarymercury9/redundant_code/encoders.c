/*#############################################################################
                               Encoders
This code is pulled out of my Kyria keymap since building a version without
encoders
#############################################################################*/
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
