SRC += private_macros.c
SRC += work_macros.c

BOOTLOADER = caterina
PROCESSOR = atmega32u4

BOARD = GENERIC_RP_RP2040
BOOTMAGIC_ENABLE = yes       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
OLED_ENABLE = yes         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
ENCODER_ENABLE = yes
LEADER_ENABLE = no
TAP_DANCE_ENABLE = no
OS_DETECTION_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
COMBO_ENABLE = yes

# Working on setting up the on chip LED
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
