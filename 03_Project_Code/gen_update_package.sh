#!/bin/bash
echo "FAW-TBOX-SDK-Package-Generate Start."

# export PATH=$PATH:/CompileChain/gcc-linaro-4.9-2016.02-x86_64_arm-linux-gnueabi/bin
# 可执行文件复制路径
CopyExePath="/mnt/hgfs/Lews/Tools/FTP_Path"

cd ./x_platform || exit

make
wait

cp ./bin/x_platform $CopyExePath || exit
wait
echo -e "\033[32m copy to FTP_Path success. \033[0m"

echo -e "\033[32m generate completed. \033[0m"
