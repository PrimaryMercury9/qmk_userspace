SRC += private_macros.c
SRC += work_macros.c
SRC += mouse_jiggler.c
SRC += oled_display.c

#include $(KEYBOARD_PATH_2)/keymaps/$(KEYMAP)/qmk-vim/rules.mk
include ~/Documents/01-Projects/keyboards/qmk_userspace/keyboards/splitkb/kyria/rev3/keymaps/primarymercury9/qmk-vim/rules.mk


USE_VIM = yes
#Features
#SPLIT_KEYBOARD = yes
#SPLIT_TRANSPORT_SYNC = yes
#TRANSACTION_ENABLE = yes
#SPLIT_KEYBOARD = yes
#LED_MATRIX_CUSTOM_USER = yes
#EXTRAKEY_ENABLE = yes
OLED_DRIVER_ENABLE = yes
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
LEADER_ENABLE = yes
COMBO_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
#WPM stuff
WPM_ENABLE = yes
WPM_SAMPLE_SECONDS = 30
WPM_SAMPLE_PERIODS = 6000
#OS Detection stuff
OS_DETECTION_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
#Disabled
VELOCIKEY_ENABLE = no
STENO_ENABLE = no
TERMINAL_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no
KEY_LOCK_ENABLE = no
AUDIO_ENABLE = no
CONSOLE_ENABLE = no
UNICODE_ENABLE = no
COMMAND_ENABLE = no
SWAP_HANDS_ENABLE = no
