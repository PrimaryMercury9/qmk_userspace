#/bin/bash
if [ ! -d $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9 ]; then
    mkdir $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9
fi

cd $HOME/.qmk_firmware

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/kyria/rules.mk  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/rules.mk
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/kyria/config.h  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/config.h
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/kyria/keymap.c  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/keymap.c
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/work_macros.c  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/work_macros.c
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/work_macros.h  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/work_macros.h
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/private_macros.c  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/private_macros.c
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/private_macros.h  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/private_macros.h
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/kyria/keyboard.json  $HOME/.qmk_firmware/keyboards/splitkb/kyria/rev3/keyboard.json
#    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/kyria/graph.c  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/graph.c
#    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/kyria/graph.h  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/graph.h
    qmk compile -kb splitkb/kyria/rev3 -km primarymercury9 -e CONVERT_TO=elite_pi -j4
elif [[ "$OSTYPE" == "darwin"* ]]; then
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/kyria/rules.mk  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/rules.mk
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/kyria/config.h  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/config.h
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/kyria/keymap.c  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/keymap.c
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/work_macros.c  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/work_macros.c
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/work_macros.h  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/work_macros.h
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/private_macros.c  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/private_macros.c
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/private_macros.h  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/private_macros.h
    ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/kyria/keyboard.json  $HOME/.qmk_firmware/keyboards/splitkb/kyria/rev3/keyboard.json
#    ln -sf $HOME/Documents/01-Projects/keyboards/kyria/graph.c  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/graph.c
#    ln -sf $HOME/Documents/01-Projects/keyboards/kyria/graph.h  $HOME/.qmk_firmware/keyboards/splitkb/kyria/keymaps/primarymercury9/graph.h
    qmk compile -kb splitkb/kyria/rev3 -km primarymercury9 -e CONVERT_TO=elite_pi -j4
else
    printf "Error, OS detection failed\n"
fi
printf "Done\n"
