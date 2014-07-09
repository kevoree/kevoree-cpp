# KevC++

The KevC++  project aims to offers runtime of kevoree for native application and helping you to develop your adaptable software from embedded devices!
KevC++ is open source project LGPL v3. 

Continuous integration : http://jenkins.reacloud.com


Select the download for your platform below.

### Requirements:

Please make sure your system satisfies one of these requirements:
Mac - OSX 10.5 and up
Linux - a fairly recent linux distro with libc >= 2.6

* Git 
* Java
* CPP unit
* gcc 
* g++
* Cmake

#### Installing Requirements Linux Ubuntu :
Linux Debian Procedure should work on Ubuntu and similar distributions: install appropriate packages:
```sh
sudo apt-get install cmake make gcc g++ git wget curl libcppunit-doc libcppunit-dev
```

#### Installing Requirements on Mac OS X 

You will need to have Homebrew installed.

* Xcode
* Clang llvm

```
brew install cppunit
brew install cmake
```

##### MacPort:
```sh
sudo port install cmake_modules
sudo port install arm-none-eabi-gcc
sudo port install arm-none-eabi-binutils
clang-llvm 3.2
```

### Getting started platform 

#### Start downloading the kevoree-cpp package that's right for you.



Linux 32 bit 

Linux 64 bit

Mac OS X 10.5 and up 32 bit

Mac OS X 10.5 and up 64 bit

#### Unzip your kevoree-cpp folder somewhere convenient on your hard drive.


#### To start kevoree-cpp :
 ```
 ./runtime in your shell window
 ```

### Mac notes


### Linux notes

This binary release has been built and tested under :
- Ubuntu 14.04 LTS.
- cmake version 2.8.12.2
- GLIBCXX_3.4.16 
- gcc and g++ 4.8.2

### Kevoree Runtime options : 

* -h: help
* -n: nodename  allows to associate a node name with the runtime
* -v: version
* -m: model  allows to give an initial bootstrap model (.json,.kev.kevs accepted)
* -l: debug level (0: Debug, 1: info, 2: Error)
 
## Building Your First App

Welcome to kevoree-cpp application development!

### The Annotation API :

The Annotation API is made to provide a simple and flexible way to decorate your existing code to declare it as a component, channel, node or group.

#### Components
 ```
#pragma ComponentType "ComponentName"
 ```
#### Channels
 ```
#pragma ChannelType "ChannelName"
 ```
#### GroupType
 ```
#pragma GroupType "WebSocketGroup"  
 ```

#### Nodes
 ```
#pragma NodeType "CPPNode"
 ```
#### Dictionnay
 ```
#pragma Dictionary "port" 
 ```

###  Create your first component
 ```
#include <kevoree-core/api/AbstractComponent.h>


#pragma ComponentType "HelloWorldComponent"
class HelloWorldComponent :public AbstractComponent
{
	public:
	HelloWorldComponent();
	~HelloWorldComponent();

	 void start();
	 void stop();
	 void update();

};
  ```
  
  
###  Create your first GroupType

  ```
#include <kevoree-core/api/AbstractGroup.h>

#pragma GroupType "WebSocketGroup"  
#pragma Dictionary "port"
class WebSocketGroup :public AbstractGroup
{
public:
	WebSocketGroup();
    void start();
	void stop();
	void update();

};

  ```

###  Create your first NodeType
 ```

#include <kevoree-core/api/AbstractNodeType.h>

#pragma NodeType "CPPNode"
class CPPNodeType : public AbstractNodeType
{
public:
	CPPNodeType();
	virtual ~CPPNodeType();
    void start();
    void stop();

};
 ```

### Enhance your TypeDefintion

#### Create a dictionary attribute
 ```
#pragma Dictionary "port" 
 ```


###  The Kevoree- Maven Plugin

The Kevoree Maven plugin is used to extract the Component-Model from the #pragma placed in your code, and store it into a Kevoree Model (lib.json)


 ```
<build>
        <plugins>
            <plugin>
                <groupId>org.kevoree.tools.cpp.maven.plugin</groupId>
                <artifactId>kevcpp-maven-plugin</artifactId>
                <version>${version}</version>
                <executions>
                    <execution>
                        <id>gen</id>
                        <goals>
                            <goal>generate</goal>
                        </goals>
                    </execution>
                </executions>
            </plugin>
        </plugins>
 </build>
 ```




### Compile the platform 




#### Get the source code:
```sh
git clone https://github.com/kevoree/kevoree-cpp.git
cd kevoree-cpp
```
#### Setting up the IDE:
Download Eclipse.

File > Import > C/C++ > Existing code as MakeFile Project > In existing code location select Kevoree-CPP directory that you've clone
 

#### Compilation   
#####Debug:
```sh
cmake -DCMAKE_BUILD_TYPE=Debug 
make
./Debug/bin/runtime
```
#####Release with boost:
```sh
cmake -DBOOST=y -DCMAKE_BUILD_TYPE=Release
make install
./Release/bin/runtime
```
#####Release without boost:
```sh
cmake  -DCMAKE_BUILD_TYPE=Release
make install
./Release/bin/runtime
```
####Start Kevoree
 ```
./Release/bin/runtime
```





