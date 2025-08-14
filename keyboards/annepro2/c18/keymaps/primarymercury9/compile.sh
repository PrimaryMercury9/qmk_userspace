#/bin/bash
if [ ! -d $HOME/.qmk_firmware/keyboards/annepro2/keymaps/primarymercury9 ]; then
    mkdir $HOME/.qmk_firmware/keyboards/annepro2/keymaps/primarymercury9
fi

ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/annepro/keymap.c $HOME/.qmk_firmware/keyboards/annepro2/keymaps/primarymercury9/keymap.c
ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/annepro/config.h $HOME/.qmk_firmware/keyboards/annepro2/c18/config.h
ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/annepro/rules.mk $HOME/.qmk_firmware/keyboards/annepro2/c18/rules.mk
ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/annepro/info.json $HOME/.qmk_firmware/keyboards/annepro2/info.json
ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/work_macros.c  $HOME/.qmk_firmware/keyboards/annepro2/keymaps/primarymercury9/work_macros.c
ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/work_macros.h  $HOME/.qmk_firmware/keyboards/annepro2/keymaps/primarymercury9/work_macros.h
ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/private_macros.c  $HOME/.qmk_firmware/keyboards/annepro2/keymaps/primarymercury9/private_macros.c
ln -sf $HOME/Documents/01-Projects/keyboards/mymaps/macros/private_macros.h  $HOME/.qmk_firmware/keyboards/annepro2/keymaps/primarymercury9/private_macros.h

cd $HOME/.qmk_firmware
#make annepro2/c18:primarymercury9
qmk compile -kb annepro2/c18 -km primarymercury9
