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
#####Debug:
```sh
cmake -DCMAKE_BUILD_TYPE=Debug 
make
./Debug/bin/main
```
#####Release with boost:
```sh
cmake -DBOOST=y -DCMAKE_BUILD_TYPE=Release
make install
./Release/bin/main
```
#####Release without boost:
```sh
cmake  -DCMAKE_BUILD_TYPE=Release
make install
./Release/bin/main
```
####Start Kevoree
 ```
./Release/bin/main
```

### Kevoree Runtime options : 

* -h: help
* -n: nodename  allows to associate a node name with the runtime
* -v: version
* -m: model  allows to give an initial bootstrap model (.json,.kev.kevs accepted)
* -l: debug level (0: Debug, 1: info, 2: Error)
 

### The Annotation API :

The Annotation API is made to provide a simple and flexible way to decorate your existing code to declare it as a component, channel, node or group.

#### Components

#pragma ComponentType "ComponentName"

#### Channels
#pragma ChannelType "ChannelName"

#### GroupType
#pragma GroupType "WebSocketGroup"  


#### Nodes

#pragma NodeType "CPPNode"

#### Dictionnay

#pragma Dictionary "port" 


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







