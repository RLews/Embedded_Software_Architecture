#!/bin/bash

export CROSSTOOL_PATH=/usr/local/oecore-x86_64
#export CROSSTOOL_PATH=/opt/oecore-X86_64
export SDKTARGETSYSROOT=${CROSSTOOL_PATH}/sysroots/armv7a-vfp-neon-oe-linux-gnueabi
export PATH=${CROSSTOOL_PATH}/sysroots/x86_64-oesdk-linux/usr/bin:${CROSSTOOL_PATH}/sysroots/x86_64-oesdk-linux/usr/bin/arm-oe-linux-gnueabi:$PATH
export PKG_CONFIG_SYSROOT_DIR=$SDKTARGETSYSROOT
export OECORE_NATIVE_SYSROOT="${CROSSTOOL_PATH}/sysroots/x86_64-oesdk-linux"
export OECORE_TARGET_SYSROOT="$SDKTARGETSYSROOT"
export OECORE_ACLOCAL_OPTS="-I ${CROSSTOOL_PATH}/sysroots/x86_64-oesdk-linux/usr/share/aclocal"
export PYTHONHOME=${CROSSTOOL_PATH}/sysroots/x86_64-oesdk-linux/usr
#export CC="arm-oe-linux-gnueabi-gcc  -D_GNU_SOURCE -march=armv7-a -mfloat-abi=soft -mfpu=vfp -mtune=cortex-a9 --sysroot=$SDKTARGETSYSROOT"
export CC="arm-oe-linux-gnueabi-gcc --sysroot=$SDKTARGETSYSROOT"
#export CXX="arm-oe-linux-gnueabi-g++  -march=armv7-a -mfloat-abi=soft -mfpu=vfp -mtune=cortex-a9 --sysroot=$SDKTARGETSYSROOT"
export CXX="arm-oe-linux-gnueabi-g++ --sysroot=$SDKTARGETSYSROOT"
#export CPP="arm-oe-linux-gnueabi-gcc -E  -march=armv7-a -mfloat-abi=soft -mfpu=vfp -mtune=cortex-a9 --sysroot=$SDKTARGETSYSROOT"
export CPP="arm-oe-linux-gnueabi-gcc -E --sysroot=$SDKTARGETSYSROOT"
export AS="arm-oe-linux-gnueabi-as "
export LD="arm-oe-linux-gnueabi-ld  --sysroot=$SDKTARGETSYSROOT"
export GDB=arm-oe-linux-gnueabi-gdb
export STRIP=arm-oe-linux-gnueabi-strip
export RANLIB=arm-oe-linux-gnueabi-ranlib
export OBJCOPY=arm-oe-linux-gnueabi-objcopy
export OBJDUMP=arm-oe-linux-gnueabi-objdump
export AR=arm-oe-linux-gnueabi-ar
export NM=arm-oe-linux-gnueabi-nm
export TARGET_PREFIX=arm-oe-linux-gnueabi-
export CONFIGURE_FLAGS="--target=arm-oe-linux-gnueabi --host=arm-oe-linux-gnueabi --build=x86_64-oesdk-linux --with-libtool-sysroot=$SDKTARGETSYSROOT"
#export CFLAGS=" -O2 -pipe -g -feliminate-unused-debug-types"
#export CFLAGS=" -O2 -pipe"
#export CXXFLAGS=" -O2 -pipe -g -feliminate-unused-debug-types"
#export CXXFLAGS=" -O2 -pipe"
export CFLAGS=" -O2 -feliminate-unused-debug-types"
export CXXFLAGS=" -O2 -feliminate-unused-debug-types"
export LDFLAGS="-Wl,--hash-style=gnu -Wl,--as-needed"
export CPPFLAGS=""
export KCFLAGS="--sysroot=$SDKTARGETSYSROOT"
export ARCH=arm
export CROSS_COMPILE=arm-oe-linux-gnueabi-
export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'

CUR_DIR=$(pwd)
JIT_SDK_VER="libjitcarapi.so.1.2.1"
RIV_DIR="../RIV_0806/SDK/riv_l170_mfota_tool_Rev-1.0/oem/mdm9607-oem-new/app/"

#make clean
#wait
#make
#wait
#make striped
if [ ! -n "$1" ] ;then
    echo "Must had param!"
    exit
fi

if [ $1 == "clean" ];then
    echo -e "\033[31mThis is Only clean!\033[0m"
    make clean
    wait
    exit
elif [ $1 == "make" ];then
	#先查询链接属性是否存在
	cd $CUR_DIR"/thirdLib"
	if [ -f $CUR_DIR"/thirdLib/libjitcarapi.so" ];then
		if [ -L $CUR_DIR"/thirdLib/libjitcarapi.so" ];then
			echo -e "\033[31mis a link!\033[0m"
			wait
		else
			echo -e "\033[31mis no a link\033[0m"
			wait
			echo -e "\033[31mold libjitcarapi.so\033[0m"
			wait
			rm libjitcarapi.so
			wait
			echo -e "\033[31mCreat A new link!\033[0m"
			wait
			ln -s $JIT_SDK_VER "libjitcarapi.so"
			wait
		fi
	else
		#如果不存在直接从新生成
		echo -e "\033[31mCreat a new link!\033[0m"
		wait
		ln -s $JIT_SDK_VER "libjitcarapi.so"
		wait
	fi
	cd ..
	#对比和riv那边的库是否一样,不一样拷贝那边的库到这边
	if [ -f $CUR_DIR"/thirdLib/"$JIT_SDK_VER ];then
		echo -e "\033[31m" $CUR_DIR"/thirdLib/"$JIT_SDK_VER" is had!\033[0m"
	else
		echo -e "\033[31m" $CUR_DIR"/thirdLib/"$JIT_SDK_VER" is exist!\033[0m"
	fi
	if [ -f $RIV_DIR$JIT_SDK_VER ];then
		echo -e "\033[31m" $RIV_DIR" is Had!\033[0m"
	else
		echo -e "\033[31m" $RIV_DIR" is exist!!\033[0m"
	fi
	#对比
	diff $RIV_DIR$JIT_SDK_VER $CUR_DIR"/thirdLib/"$JIT_SDK_VER > /dev/null
	if [ $? != 0 ]
    then
        echo "Different and copy from " $RIV_DIR
		cp $RIV_DIR$JIT_SDK_VER $CUR_DIR"/thirdLib/"$JIT_SDK_VER
    else
        echo -e "\033[31mSame!\033[0m"
    fi
    echo -e "\033[31mThis is only make!\033[0m"
	make clean
	wait
    make VERBOSE=2
    wait
	#make striped
	wait
else
    echo "No support!!!!"
fi


