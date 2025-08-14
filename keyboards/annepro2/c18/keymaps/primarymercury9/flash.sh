#/bin/bash
$HOME/Documents/01-Projects/keyboards/mymaps/annepro/compile.sh

cd $HOME/.annepro2_tools/target/release

# Wait 5 seconds to put keyboard in to IAP mode
startfrom=5
for ((i=startfrom; i>=1; i--))
do
    echo $i
    sleep 1
done

#Flash firmware
./annepro2_tools $HOME/.qmk_firmware/annepro2_c18_primarymercury9.bin
./annepro2_tools --boot -t led $HOME/.annepro2_shine/build/annepro2-shine-C18.bin
