# kevoree C++

##### Requirements:
Install git and java if you do not have it yet. cc
#### Linux Ubuntu :
Linux Debian Procedure should work on Ubuntu and similar distributions: install appropriate packages: 
* sudo apt-get install cmake_modules make gcc g++ 


### Getting started 
* git clone https://github.com/kevoree/kevoree-cpp.git
* cd kevoree-cpp
* . ./install.sh
* . ./setenv.sh

### Compile for Linux  
* cmake .
* make
* ./kevoree-platform/main

### Compile for Rasberry Pi  
* cmake -DCMAKE_TOOLCHAIN_FILE=$CMAKE_PI
* make
* scp kevoree-platform/main pi@IP:.
* ssh 
* ./data/main

### Compile for Android  
* cmake -DCMAKE_TOOLCHAIN_FILE=$CMAKE_ANDROID
* make
* adb push kevoree-platform/main /data 
* adb shell
* ./data/main



#### Mac OS X: TODO cross compile boost
XCode, should be installed through AppleStore
* Brew: 
  brew install cmake 
* MacPort:
  sudo port install cmake_modules
* clang-llvm 3.2

### Compile for Mac OS X  
* cmake -DCMAKE_TOOLCHAIN_FILE=$CMAKE_OSX
* make

