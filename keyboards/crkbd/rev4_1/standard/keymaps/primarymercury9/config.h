/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

//#define QUICK_TAP_TERM 0
//#define TAPPING_TERM 100

#define TAPPING_TERM 135
#define DYNAMIC_MACRO_NO_NESTING true
#define DYNAMIC_MACRO_SIZE 2048
#define DYNAMIC_MACRO_DELAY 25

/* Leader */
#define LEADER_NO_TIMEOUT
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 750

/* OS Detection */
#define OS_DETECTION_DEBOUNCE 3500
#define OS_DETECTION_KEYBOARD_RESET
#define SPLIT_DETECTED_OS_ENABLE

#define RGB_MATRIX_DEFAULT_ON false
#define RGB_MATRIX_DEFAULT_HUE 0
#define RGB_MATRIX_DEFAULT_SAT 0
#define RGB_MATRIX_DEFAULT_VAL 0
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_STATE
