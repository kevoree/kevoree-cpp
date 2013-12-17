echo "Cleaning"
find . -name "CMakeFiles" | xargs rm -rf
find . -name "Makefile" | xargs rm -rf
find . -name "cmake_install.cmake_modules" | xargs rm -rf
find . -name "cmake_install.cmake" | xargs rm -rf
find . -name "CMakeCache.txt" | xargs rm -rf                                                

if [ -d "kevoree-core/model/kevoree" ]; then
 rm -rf kevoree-core/model/kevoree
fi
echo "Build Android Environment"

KERNEL=$(uname -s)
ARCH=$(uname -m)
if         [ $ARCH = "i386" ]; then
            ARCH="32"
    elif    [ $ARCH = "i486" ]; then
            ARCH="32"
    elif    [ $ARCH = "i586" ]; then
            ARCH="32"
    elif    [ $ARCH = "i686" ]; then
            ARCH="32"
    elif [ $ARCH = "x86_64" ]; then
            ARCH="64"
    else
        echo "Unsoportted Architecture"
fi

mkdir download
cd download
if      [ $KERNEL = "Darwin" ]; then
    
     	if [ ${ARCH} == '64' ]; then
	     	wget http://llvm.org/releases/3.2/clang+llvm-3.2-x86_64-apple-darwin11.tar.gz
	     	tar xvf clang+llvm-3.2-x86_64-apple-darwin11.tar.gz
     	 	echo "TODO"
	else
     		 echo "TODO"
     		
     	fi
		
elif   [ $KERNEL = "Linux" ]; then
 	if [ ${ARCH} == '64' ]; then
			 # 64-bit stuff here
			wget http://dl.google.com/android/ndk/android-ndk-r8e-linux-x86_64.tar.bz2  
			tar xvf android-ndk-r8e-linux-x86_64.tar.bz2 
			wget http://llvm.org/releases/3.2/clang+llvm-3.2-x86_64-linux-ubuntu-12.04.tar.gz
			tar xvf clang+llvm-3.2-x86_64-linux-ubuntu-12.04.tar.gz
	else
		echo "${ARCH}"
		wget http://dl.google.com/android/ndk/android-ndk-r8e-linux-x86.tar.bz2
		tar xvf android-ndk-r8e-linux-x86.tar.bz2
		wget http://llvm.org/releases/3.2/clang+llvm-3.2-x86-linux-ubuntu-12.04.tar.gz
		tar xvf clang+llvm-3.2-x86-linux-ubuntu-12.04.tar.gz
	fi      
else
        echo "Unsupported OS"
fi
mv 
mv android-ndk-r8e ../toolchain
cd ..
. ./setenv.sh

$NDK/build/tools/make-standalone-toolchain.sh --platform=android-9 --install-dir=toolchain/android-toolchain


mkdir thirdparty
cd thirdparty
wget http://powet.eu/kevoree/boost_android_r8e.tar.gz
wget http://powet.eu/kevoree/boost_elf32-arm.tar.gz
wget http://powet.eu/kevoree/boost_elf32-i386.tar.gz
wget http://powet.eu/kevoree/boost_efl64-x64.tar.gz
tar xvf boost_android_r8e.tar.gz
tar xvf boost_elf32-arm.tar.gz
tar xvf boost_elf32-i386.tar.gz
tar xvf boost_efl64-x64.tar.gz
cd ..


if [ -d "maven-resolver-cpp" ]; then
echo "Clonning Maven Resolver C++"
git clone https://github.com/Jean-Emile/maven-resolver-cpp.git
fi



