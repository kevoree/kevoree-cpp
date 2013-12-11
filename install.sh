echo "Cleaning"
find . -name "CMakeFiles" | xargs rm -rf
find . -name "Makefile" | xargs rm -rf
find . -name "cmake_install.cmake_modules" | xargs rm -rf
find . -name "cmake_install.cmake" | xargs rm -rf
find . -name "CMakeCache.txt" | xargs rm -rf                                                
rm -rf kevoree-core/model/kevoree 
#rm -rf kevoree-core/model/microframework


echo "Build Android Env"

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
     echo "TODO"
elif   [ $KERNEL = "Linux" ]; then
 	if [ ${ARCH} == '64' ]; then
			 # 64-bit stuff here
			wget http://dl.google.com/android/ndk/android-ndk-r8e-linux-x86_64.tar.bz2  
			tar xvf android-ndk-r8e-linux-x86_64.tar.bz2 
	else
		echo "${ARCH}"
		wget http://dl.google.com/android/ndk/android-ndk-r8e-linux-x86.tar.bz2
		tar xvf android-ndk-r8e-linux-x86.tar.bz2
	fi      
else
        echo "Unsupported OS"
fi
mv android-ndk-r8e ../toolchain
cd ..


$NDK/build/tools/make-standalone-toolchain.sh --platform=android-9 --install-dir=toolchain/android-toolchain

#cmake -DCMAKE_TOOLCHAIN_FILE=$ANDTOOLCHAIN


mkdir thirdparty
cd thirdparty

echo "Clonning Maven Resolver C++"
git clone https://github.com/Jean-Emile/maven-resolver-cpp.git
export LD_LIBRARY_PATH=build/


echo "Downloading Model Generator"
wget http://oss.sonatype.org/content/repositories/snapshots/org/kevoree/modeling/org.kevoree.modeling.cpp.generator/1.1-SNAPSHOT/org.kevoree.modeling.cpp.generator-1.1-20131209.091837-8.jar --quiet

echo "Generating Kevoree Model"
#java -jar org.kevoree.modeling.cpp.generator-1.1-20131209.091837-8.jar -i kevoree-core/model/metamodel/kevoree.ecore -t kevoree-core/model
echo "Generating Kevoree Adaptation Model"
#java -jar org.kevoree.modeling.cpp.generator-1.1-20131209.091837-8.jar -i kevoree-core/model/metamodel/kevoree.adaptation.ecore -t kevoree-core/model
rm -rf org.kevoree.modeling.cpp.generator-1.1-20131209.091837-8.jar


