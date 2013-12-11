# kevoree C++

##### Requirements:
#### Linux Ubuntu :
Linux Debian Procedure should work on Ubuntu and similar distributions: install appropriate packages: 
* sudo apt-get install cmake_modules make gcc g++ 

#### MacOS:
XCode, should be installed through AppleStore
* Brew: 
  brew install cmake llvm
* MacPort:
  sudo port install cmake_modules
  

### Getting started 
* git clone https://github.com/kevoree/kevoree-cpp.git
* cd kevoree-cpp
* . ./install.sh
* . ./setenv.sh

### Compile for Native  
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


