#/bin/bash
if [ ! -d $HOME/.qmk_firmware/keyboards/reviung/reviung5/keymaps/primarymercury9 ]; then
    mkdir $HOME/.qmk_firmware/keyboards/reviung/reviung5/keymaps/primarymercury9;
fi

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/keymap.c $HOME/.qmk_firmware/keyboards/reviung/reviung5/keymaps/primarymercury9/keymap.c
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/config.h $HOME/.qmk_firmware/keyboards/reviung/reviung5/config.h
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/rules.mk $HOME/.qmk_firmware/keyboards/reviung/reviung5/rules.mk
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/keyboard.json $HOME/.qmk_firmware/keyboards/reviung/reviung5/keyboard.json
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/private_macros.h $HOME/.qmk_firmware/keyboards/reviung/reviung5/private_macros.h
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/private_macros.c $HOME/.qmk_firmware/keyboards/reviung/reviung5/private_macros.c
    cd $HOME/.qmk_firmware/
    qmk compile -kb reviung/reviung5 -km primarymercury9 -e CONVERT_TO=elite_pi
elif [[ "$OSTYPE" == "darwin"* ]]; then
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/keymap.c $HOME/.qmk_firmware/keyboards/reviung/reviung5/keymaps/primarymercury9/keymap.c
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/config.h $HOME/.qmk_firmware/keyboards/reviung/reviung5/config.h
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/rules.mk $HOME/.qmk_firmware/keyboards/reviung/reviung5/rules.mk
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/keyboard.json $HOME/.qmk_firmware/keyboards/reviung/reviung5/keyboard.json
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/private_macros.h $HOME/.qmk_firmware/keyboards/reviung/reviung5/private_macros.h
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/reviung5/private_macros.c $HOME/.qmk_firmware/keyboards/reviung/reviung5/private_macros.c
    cd $HOME/.qmk_firmware/
    qmk compile -kb reviung/reviung5 -km primarymercury9 -e CONVERT_TO=elite_pi
else
    printf "Error, OS detection failed\n"
fi
printf "Done\n"
