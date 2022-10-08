#Delete old folder, in case it was compiled on a different arhitecture
rm -rf build/;
mkdir build;

current_dir=$PWD;

cd build/;

cmake ../;

MACHINE_TYPE=`uname -m`
if [ ${MACHINE_TYPE} == 'arm64' ]
then
    export PATH="$(brew --prefix bison)/bin:$PATH";
fi

if cmake --build .; then 
echo "Build succeded!";
else 
echo "Build failed, operation will be aborted!";
exit
fi