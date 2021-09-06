#!/bin/bash
echo "Package-Generate Start."

# export PATH=$PATH:/CompileChain/gcc-linaro-4.9-2016.02-x86_64_arm-linux-gnueabi/bin
# 可执行文件复制路径
CopyExePath="/home/jlews/work/Embedded_Software_Architecture/03_Project_Code/RunDir"

if ls $CopyExePath; then
    echo "RunDir exist. not create."
else
    echo "mkdir RunDir"
    mkdir $CopyExePath
fi

cd ./x_platform || exit

make clean
wait

make
wait

cp ./bin/x_platform $CopyExePath || exit
wait

cp ./Debug/DebugSend $CopyExePath || exit
wait


echo -e "\033[32m copy success. \033[0m"

echo -e "\033[32m generate completed. \033[0m"
