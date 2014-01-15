
export ANDROID_STANDALONE_TOOLCHAIN=`pwd`/toolchain/android-toolchain/
export TOOLCHAIN_ANDROID=`pwd`/toolchain/android.toolchain.cmake
export TOOLCHAIN_PI=`pwd`/toolchain/raspberry.toolchain.cmake
export TOOLCHAIN_YUN=`pwd`/toolchain/yun.cmake



export NDK=toolchain/android-ndk-r8e
export PATH=$PATH:$NDK/bin
export BUILD_ANDROID="cmake -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_ANDROID"
export BUILD_YUN="cmake -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_YUN"


export LD_LIBRARY_PATH=build/

export PATH=$PATH:/opt/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/bin
export STAGING_DIR=/opt/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2

