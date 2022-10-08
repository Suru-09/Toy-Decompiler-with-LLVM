current_dir=$PWD;

cd build/;

cmake ../;

MACHINE_TYPE=`uname -m`
if [ ${MACHINE_TYPE} == 'arm64' ]
then
    export PATH="$(brew --prefix bison)/bin:$PATH";
else
    echo "error";
fi

if cmake --build .; then 
echo "Build succeded!";
else 
echo "Build failed, operation will be aborted!";
exit
fi

./Bison-Parser ../bison/test.txt