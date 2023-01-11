#!/bin/sh

current_dir=$PWD;

rm -rf build;
mkdir build;
cd build/;


MACHINE_TYPE=$(uname -m)
echo "Found the folowing arch: <$MACHINE_TYPE>"

if [ "${MACHINE_TYPE}" == "arm64" ]
then
    cmake ../ -Darch:String="arm64";
elif [ "${MACHINE_TYPE}" == "x86_64" ]
then
    #cmake ../ -Darch:String="x86" -Dwork:STRING="OFF";
    cmake ../ -Darch:String="x86" -Dwork:STRING="ON";
fi

if cmake --build .; then 
echo "Build succeded!";
else 
echo "Build failed, operation will be aborted!";
exit
fi

./src/Reverse-Engineering-Tool