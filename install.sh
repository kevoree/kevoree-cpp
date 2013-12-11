echo "Cleaning"
find . -name "CMakeFiles" | xargs rm -rf
find . -name "Makefile" | xargs rm -rf
find . -name "cmake_install.cmake_modules" | xargs rm -rf
find . -name "cmake_install.cmake" | xargs rm -rf
find . -name "CMakeCache.txt" | xargs rm -rf                                                
rm -rf kevoree-core/model/kevoree 
#rm -rf kevoree-core/model/microframework


echo "Configure Android"
MACHINE_TYPE=`uname -m`
if [[ "$OSTYPE" == "linux-gnu" ]]; then
	if [ ${MACHINE_TYPE} == 'x86_64' ]; then
	  # 64-bit stuff here
	wget http://dl.google.com/android/ndk/android-ndk-r8e-linux-x86_64.tar.bz2  
	else
	wget http://dl.google.com/android/ndk/android-ndk-r9b-linux-x86.tar.bz2
	fi
elif [[ "$OSTYPE" == "darwin"* ]]; then
	if [ ${MACHINE_TYPE} == 'x86_64' ]; then
	  # 64-bit stuff here http://dl.google.com/android/ndk/android-ndk-r9b-darwin-x86_64.tar.bz2
	else
	  # 32-bit stuff here http://dl.google.com/android/ndk/android-ndk-r8e-darwin-x86.tar.bz2
	fi
elif [[ "$OSTYPE" == "cygwin" ]]; then
        # ...
elif [[ "$OSTYPE" == "win32" ]]; then
        # ...
elif [[ "$OSTYPE" == "freebsd"* ]]; then
        # ...
else
        # Unknown.
fi


$NDK/build/tools/make-standalone-toolchain.sh --platform=android-13 --install-dir=toolchain/android-toolchain
export ANDROID_STANDALONE_TOOLCHAIN=`pwd`/toolchain/android-toolchain/
export ANDTOOLCHAIN=`pwd`/toolchain/android.toolchain.cmake
#cmake -DCMAKE_TOOLCHAIN_FILE=$ANDTOOLCHAIN


mkdir thirdparty
cd thirdparty
wget 

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

