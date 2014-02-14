# kevoree C++
 
##### Requirements:
Install git and java if you do not have it yet. cc
#### Linux Ubuntu :
Linux Debian Procedure should work on Ubuntu and similar distributions: install appropriate packages:
```sh
sudo apt-get install cmake make gcc g++ git ant wget gcc-4.6-plugin-dev apt-get install libcppunit-doc libcppunit-dev
```
Cross Compile Raspberry Pi http://elinux.org/RPi_Kernel_Compilation
```sh
sudo apt-get install gcc-arm-linux-gnueabi make ncurses-dev
```
 
 
### Getting started
```sh
git clone https://github.com/kevoree/kevoree-cpp.git
cd kevoree-cpp
./setenv.sh
```
 
### Compile for Linux  
```sh
cmake .
make
./kevoree-platform/main
```
 
### Compile for Rasberry Pi
```sh
cmake -DCMAKE_TOOLCHAIN_FILE=$CMAKE_PI
make
scp kevoree-platform/main pi@IP:.
ssh
./data/main
```
 
### Compile for Android  
```sh
cmake -DCMAKE_TOOLCHAIN_FILE=$CMAKE_ANDROID
make
adb push kevoree-platform/main /data
adb shell
./data/main
```
 
 
 
#### Mac OS X: TODO cross compile boost
XCode, should be installed through AppleStore
 
##### Brew:
`brew install cmake`
 
##### MacPort:
```sh
sudo port install cmake_modules
sudo port install arm-none-eabi-gcc
sudo port install arm-none-eabi-binutils
clang-llvm 3.2
```
 
### Compile for Mac OS X  
```sh
cmake -DCMAKE_TOOLCHAIN_FILE=$CMAKE_OSX
make



Boost android
https://github.com/Jean-Emile/Boost-for-Android.git
