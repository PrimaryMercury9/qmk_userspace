if [ -e $HOME/.qmk_firmware/keyboards/splitkb/kyria/kyria.c ]; then
    printf "Kyria file found"
    if [ ! -e $HOME/.qmk_firmware/keyboards/splitkb/kyria/bak.kyria.c ]; then
        cp $HOME/.qmk_firmware/keyboards/splitkb/kyria/kyria.c $HOME/.qmk_firmware/keyboards/splitkb/kyria/bak.kyria.c
        printf "Kyria file backed up"
    fi
    rm $HOME/.qmk_firmware/keyboards/splitkb/kyria/kyria.c
    printf "Kyria file deleted"
fi

if [ -e $HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/v1x_oled.c ]; then
    printf "Dumbpad file found"
    if [ ! -e $HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/bak.v1x_oled.c ]; then
        cp $HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/v1x_oled.c $HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/bak.v1x_oled.c
        printf "Dumbpad file backed up"
    fi
    rm $HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/v1x_oled.c
    printf "Dumbpad file deleted"
fi
