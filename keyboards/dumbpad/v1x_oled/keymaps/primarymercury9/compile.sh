# Location for the keymaps: /home/jpm/.qmk_firmware/keyboards/dumbpad/v1x_oled/keymaps/

if [ ! -d $HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/keymaps/primarymercury9 ]; then
    mkdir $HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/keymaps/primarymercury9
fi

if [ -f "$HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/v1x_oled.c" ]; then
    mv $HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/v1x_oled.c $HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/bak.v1x_oled.c
    printf "Moved annoying default c file\n"
fi

cd $HOME/.qmk_firmware

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/dumbpad/keymap.c  $HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/keymaps/primarymercury9/keymap.c
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/private_macros.c  $HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/keymaps/primarymercury9/private_macros.c
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/private_macros.h  $HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/keymaps/primarymercury9/private_macros.h
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/work_macros.c  $HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/keymaps/primarymercury9/work_macros.c
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/work_macros.h  $HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/keymaps/primarymercury9/work_macros.h
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/dumbpad/config.h  $HOME/.qmk_firmware/keyboards/dumbpad/config.h
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/dumbpad/rules.mk  $HOME/.qmk_firmware/keyboards/dumbpad/rules.mk
    qmk compile -kb dumbpad/v1x_oled -km primarymercury9 -e CONVERT_TO=helios
elif [[ "$OSTYPE" == "darwin"* ]]; then
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/dumbpad/keymap.c  $HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/keymaps/primarymercury9/keymap.c
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/private_macros.c  $HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/keymaps/primarymercury9/private_macros.c
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/private_macros.h  $HOME/.qmk_firmware/keyboards/dumbpad/v1x_oled/keymaps/primarymercury9/private_macros.h
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/dumbpad/config.h  $HOME/.qmk_firmware/keyboards/dumbpad/config.h
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/dumbpad/rules.mk  $HOME/.qmk_firmware/keyboards/dumbpad/rules.mk
    qmk compile -kb dumbpad/v1x_oled -km primarymercury9 -e CONVERT_TO=helios
else
    printf "Error, OS detection failed\n"
fi
printf "Done\n"
