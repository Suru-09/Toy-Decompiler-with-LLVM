#!/bin/sh

current_dir=$PWD;

rm -rf build;
mkdir build;
cd build/;


MACHINE_TYPE=$(uname -m)
echo "Found the folowing arch: <$MACHINE_TYPE>"

if [ "${MACHINE_TYPE}" == "arm64" ]
then
    cmake ../ -Darch:String="arm64" -DBUILD_SHARED_LIBS:BOOL=OFF;
elif [ "${MACHINE_TYPE}" == "x86_64" ]
then
    cmake ../ -Darch:String="x86" -DBUILD_SHARED_LIBS:BOOL=ON;
fi

CORES=$(nproc --all)
echo "Machine has <$CORES> cores."

if cmake --build . -j$CORES; then 
echo "Build succeded!";
else 
echo "Build failed, operation will be aborted!";
exit
fi

./src/Reverse-Engineering-Tool