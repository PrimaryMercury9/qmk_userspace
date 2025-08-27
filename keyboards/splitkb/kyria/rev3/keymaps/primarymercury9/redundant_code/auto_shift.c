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
