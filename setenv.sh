
export ANDROID_STANDALONE_TOOLCHAIN=`pwd`/toolchain/android-toolchain/
export CMAKE_ANDROID=`pwd`/toolchain/android.toolchain.cmake
export NDK=toolchain/android-ndk-r8e
export PATH=$PATH:$NDK/bin
export BUILD_ANDROID="cmake -DCMAKE_TOOLCHAIN_FILE=$CMAKE_ANDROID"



export CMAKE_PI=`pwd`/toolchain/raspberry.toolchain.cmake
export CMAKE_OSX=`pwd`/toolchain/osx.toolchain.cmake


export LD_LIBRARY_PATH=build/

export PATH=$PATH:/opt/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/bin
export STAGING_DIR=/opt/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2

