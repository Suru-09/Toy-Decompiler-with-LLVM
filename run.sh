current_dir=$PWD;

rm -rf build;
mkdir build;
cd build/;


MACHINE_TYPE=`uname -m`
if [ "$MACHINE_TYPE" eq "arm64" ]
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