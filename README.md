# kevoree C++
 
 Continuous integration : http://jenkins.reacloud.com
 
 
### Requirements:

* Git 
* Java
* CPP unit
* GCC
* g++

#### additional requirements for MAC OS :
* Xcode
* Clang llvm

##### MacPort:
```sh
sudo port install cmake_modules
sudo port install arm-none-eabi-gcc
sudo port install arm-none-eabi-binutils
clang-llvm 3.2
```


#### Linux Ubuntu :
Linux Debian Procedure should work on Ubuntu and similar distributions: install appropriate packages:
```sh
sudo apt-get install cmake make gcc g++ git wget curl libcppunit-doc libcppunit-dev
```

### Getting started
```sh
git clone https://github.com/kevoree/kevoree-cpp.git
cd kevoree-cpp
./setenv.sh
```

#### Setting up the IDE:
Download Eclipse.
File > Import > C/C++ > Existing code as MakeFile Project > In existing code location select Kevoree-CPP directory that you've clone
### Compile for Linux  
```sh
cmake .
make
./kevoree-platform/main
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



Create your first component



