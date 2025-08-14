#/bin/bash
cd $HOME/.qmk_firmware

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    printf "\n\n\n=====================================================\n\n\n"
    printf "Flashing left side"
    printf "\n\n\n=====================================================\n\n\n"
    qmk flash -kb splitkb/kyria/rev3 -km primarymercury9 -e CONVERT_TO=liatris -j 0
    rm $HOME/Documents/01-Projects/keyboards/qmk_userspace/splitkb_kyria_rev3_primarymercury9_liatris.uf2
    printf "\n\n\n=====================================================\n\n\n"
    printf "Flashing right side"
    printf "\n\n\n=====================================================\n\n\n"
    qmk flash -kb splitkb/kyria/rev3 -km primarymercury9 -e CONVERT_TO=helios -j 0
    rm $HOME/Documents/01-Projects/keyboards/qmk_userspace/splitkb_kyria_rev3_primarymercury9_helios.uf2
elif [[ "$OSTYPE" == "darwin"* ]]; then
    printf "\n\n\n=====================================================\n\n\n"
    printf "Flashing left side"
    printf "\n\n\n=====================================================\n\n\n"
    qmk flash -kb splitkb/kyria/rev3 -km primarymercury9 -e CONVERT_TO=liatris -j 0
    printf "\n\n\n=====================================================\n\n\n"
    printf "Flashing right side"
    printf "\n\n\n=====================================================\n\n\n"
    qmk flash -kb splitkb/kyria/rev3 -km primarymercury9 -e CONVERT_TO=helios -j 0
else
    printf "Error, OS detection failed\n"
fi
printf "Done\n"
