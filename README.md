# Kevoree C++
 
 Continuous integration : http://jenkins.reacloud.com



### Requirements:

* Git 
* Java
* CPP unit
* GCC
* g++
* Cmake

#### Additional requirements for MAC OS :
* Xcode
* Clang llvm

```brew install cppunit
brew install cmake
```


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

#### Get the source code:
```sh
git clone https://github.com/kevoree/kevoree-cpp.git
cd kevoree-cpp
```

#### Setting up the IDE:
Download Eclipse.
File > Import > C/C++ > Existing code as MakeFile Project > In existing code location select Kevoree-CPP directory that you've clone
 

#### Compilation   
```sh
cmake .
make
./kevoree-platform/main
```
 



