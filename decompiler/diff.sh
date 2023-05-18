#!/bin/sh

current_dir=$PWD;

cd build/;


MACHINE_TYPE=$(uname -m)
echo "Found the folowing arch: <$MACHINE_TYPE>"

if [ "${MACHINE_TYPE}" == "arm64" ]
then
    cmake ../ -G Ninja -DOPENSSL_ROOT_DIR=/opt/homebrew/opt/openssl@1.1/ -DOPENSSL_INCLUDE_DIR=/opt/homebrew/opt/openssl@1.1/include/    \
    -Dcpprestsdk_INCLUDE_DIR=/opt/homebrew/opt/cpprestsdk/include/                \
    -Darch:String="arm64" -DBUILD_SHARED_LIBS:BOOL=OFF;
elif [ "${MACHINE_TYPE}" == "x86_64" ]
then
    cmake ../ -G Ninja -Darch:String="x86" -DBUILD_SHARED_LIBS:BOOL=ON;
fi

CORES=""
if [ "${MACHINE_TYPE}" == "arm64" ]
then
    CORES=$(sysctl -n hw.ncpu)
elif [ "${MACHINE_TYPE}" == "x86_64" ]
then
    CORES=$(nproc --all)
fi

echo "Machine has $CORES cores."

if cmake --build . -j$CORES; then 
echo "Build succeded!";
else 
echo "Build failed, operation will be aborted!";
exit
fi

./Reverse-Engineering-Tool