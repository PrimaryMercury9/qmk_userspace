SRC += private_macros.c
SRC += work_macros.c

# MCU
MCU = cortex-m0plus
ARMV = 6
USE_FPU = no
MCU_FAMILY = HT32
MCU_SERIES = HT32F523xx
MCU_LDSCRIPT = HT32F52352_ANNEPRO2_C18
MCU_STARTUP = ht32f523xx

BOARD = ANNEPRO2_C18

LEADER_ENABLE = yes
OS_DETECTION_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes

DYNAMIC_MACRO_ENABLE = yes

# Bootloader selection
BOOTLOADER = custom
PROGRAM_CMD = annepro2_tools --boot $(BUILD_DIR)/$(TARGET).bin

# Anne Pro 2
SRC = \
	annepro2_ble.c \
	ap2_led.c \
	protocol.c \
	rgb_driver.c \
