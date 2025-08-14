#!/bin/bash
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    printf "Linux detected\n"
    if [[ ! -d /run/media/jpm/RPI-RP2 ]]; then
        printf "\nMicrocontroller is not in disk mode, unable to flash, please retry\n"
        exit
    fi
    printf "Microcontroller in disk mode, ready\n\n"
    $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/compile.sh
    cp $HOME/.qmk_firmware/reviung_reviung5_primarymercury9_elite_pi.uf2 /run/media/jpm/RPI-RP2
    rm $HOME/.qmk_firmware/reviung_reviung5_primarymercury9_elite_pi.uf2
elif [[ "$OSTYPE" == "darwin"* ]]; then
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/keymap.c $HOME/.qmk_firmware/keyboards/reviung/reviung5/keymaps/primarymercury9/keymap.c
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/config.h $HOME/.qmk_firmware/keyboards/reviung/reviung5/config.h
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/rules.mk $HOME/.qmk_firmware/keyboards/reviung/reviung5/rules.mk
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/keyboard.json $HOME/.qmk_firmware/keyboards/reviung/reviung5/keyboard.json
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/private_macros.h $HOME/.qmk_firmware/keyboards/reviung/reviung5/private_macros.h
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/private_macros.c $HOME/.qmk_firmware/keyboards/reviung/reviung5/private_macros.c
    cd $HOME/.qmk_firmware/
    qmk flash -kb reviung/reviung5 -km primarymercury9 -e CONVERT_TO=elite_pi
else
    printf "Error, OS detection failed\n"
fi
printf "Done\n"
