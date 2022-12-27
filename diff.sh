current_dir=$PWD;

cd build/;


MACHINE_TYPE=`uname -m`
if [ ${MACHINE_TYPE} == 'arm64' ]
then
    cmake ../ -Darch:String="arm64";
else
    cmake ../ -Darch:String="x86";
fi

if cmake --build .; then 
echo "Build succeded!";
else 
echo "Build failed, operation will be aborted!";
exit
fi

./src/Reverse-Engineering-Tool