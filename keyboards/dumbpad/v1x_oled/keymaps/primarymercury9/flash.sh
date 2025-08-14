# Location for the keymaps: /home/jpm/.qmk_firmware/keyboards/dumbpad/v1x_oled/keymaps/
cd $HOME/.qmk_firmware

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    qmk flash -kb dumbpad/v1x_oled -km primarymercury9 -e CONVERT_TO=helios
elif [[ "$OSTYPE" == "darwin"* ]]; then
    qmk flash -kb dumbpad/v1x_oled -km primarymercury9 -e CONVERT_TO=helios
else
    printf "Error, OS detection failed\n"
fi
printf "Done\n"
