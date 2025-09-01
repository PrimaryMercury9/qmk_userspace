#include "mouse_jiggler.h"

// Maintain the jiggler toggle state here, globally accessible
bool is_jiggling = false;

// Timing constants
static uint32_t idle_timeout = 30000;   // 30 seconds
static uint32_t mouse_interval = 12000; // 12 seconds

// Deferred token for idle callback management
static deferred_token idle_token = INVALID_DEFERRED_TOKEN;

void toggle_jiggler(void) {
    is_jiggling = !is_jiggling;

    // If turning off the jiggler, cancel any outstanding callbacks
    if (!is_jiggling && idle_token != INVALID_DEFERRED_TOKEN) {
        cancel_deferred_exec(idle_token);
        idle_token = INVALID_DEFERRED_TOKEN;
    }
}

uint32_t idle_timeout_ms(void) {
    return idle_timeout;
}

uint32_t mouse_interval_ms(void) {
    return mouse_interval;
}

uint32_t mouse_jiggler_idle_callback(uint32_t trigger_time, void* cb_arg) {
    if (is_jiggling) {
        tap_code(KC_MS_UP);
        tap_code(KC_MS_DOWN);
        tap_code(KC_MS_LEFT);
        tap_code(KC_MS_RIGHT);
        return mouse_interval;  // Reschedule this callback after mouse_interval ms
    }

    // Stop rescheduling callback if not jiggling
    idle_token = INVALID_DEFERRED_TOKEN;
    return 0;
}

bool mouse_jiggler_process_record(uint16_t keycode, keyrecord_t *record) {
    // On every key event start or extend the idle callback deferred execution
    if (!extend_deferred_exec(idle_token, idle_timeout)) {
        idle_token = defer_exec(idle_timeout, mouse_jiggler_idle_callback, NULL);
    }

    // Continue normal processing of keycodes (return true)
    return true;
}
