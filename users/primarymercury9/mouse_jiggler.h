#pragma once
#include <stdbool.h>
#include "quantum.h" // for keycodes

extern bool is_jiggling;

void toggle_jiggler(void);

uint32_t idle_timeout_ms(void);
uint32_t mouse_interval_ms(void);

// Called on every key event from process_record_user; returns true for normal processing
bool mouse_jiggler_process_record(uint16_t keycode, keyrecord_t *record);

// The idle callback function used internally, called by timer system
uint32_t mouse_jiggler_idle_callback(uint32_t trigger_time, void* cb_arg);
