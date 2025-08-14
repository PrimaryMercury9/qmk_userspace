#include "private_macros.h"
#pragma once
#include QMK_KEYBOARD_H

enum work_keycodes {
    CC_ANS = PRIVATE_SAFE_RANGE, 
    CC_TMUT,
    CC_TCAM,
    CC_TSHR,
    CC_TEND,
    CC_SET,
    CC_DT1,
    CC_DT2,
    CC_DT3,
    CC_DT4,
    MA_CLOF,
    MA_OFR,
    MA_POST,
    CC_LOL,
    CC_ROFL,
    CC_SIGH,
    CC_FCPL,
    CC_THUP,
    LOCAL_SAFE_RANGE
};
bool process_work_macros(uint16_t keycode, keyrecord_t *record);
