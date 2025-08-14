#/bin/bash
cd $HOME/.qmk_firmware

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    printf "\n\n\n=====================================================\n\n\n"
    printf "Flashing left side"
    printf "\n\n\n=====================================================\n\n\n"
    qmk flash -kb splitkb/kyria/rev3 -km primarymercury9 -e CONVERT_TO=liatris -j4
    printf "\n\n\n=====================================================\n\n\n"
    printf "Flashing right side"
    printf "\n\n\n=====================================================\n\n\n"
    qmk flash -kb splitkb/kyria/rev3 -km primarymercury9 -e CONVERT_TO=helios -j4
elif [[ "$OSTYPE" == "darwin"* ]]; then
    printf "\n\n\n=====================================================\n\n\n"
    printf "Flashing left side"
    printf "\n\n\n=====================================================\n\n\n"
    qmk flash -kb splitkb/kyria/rev3 -km primarymercury9 -e CONVERT_TO=liatris -j4
    printf "\n\n\n=====================================================\n\n\n"
    printf "Flashing right side"
    printf "\n\n\n=====================================================\n\n\n"
    qmk flash -kb splitkb/kyria/rev3 -km primarymercury9 -e CONVERT_TO=helios -j4
else
    printf "Error, OS detection failed\n"
fi
printf "Done\n"
