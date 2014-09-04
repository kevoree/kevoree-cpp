# KevC++

The KevC++ project aims to offers runtime of kevoree for native application and helping you to develop your adaptable software for embedded devices!
Select the download for your platform below to try it !
KevC++ is open source project LGPL v3. 

For more information :
Official website 		: http://www.kevoree.org

###  Roadmap 

KevC++ 1.0.1 Due by September 12, 2014

KevC++ 1.0.2 Due by October    2, 2014

https://github.com/kevoree/kevoree-cpp/milestones


Continuous integration 	: http://jenkins.reacloud.com and https://drone.io/github.com/kevoree/kevoree-cpp
Maven repository  		: http://maven.reacloud.com/nexus


### Getting started platform 

##### Start downloading the kevoree-cpp package that's right for you.


Linux 64 bit

Linux 32 bit  (no available, soon !)

Mac OS X 10.5 and up 32 bit (no available, soon !)

Mac OS X 10.5 and up 64 bit (no available, soon !)

##### Unzip your kevoree-cpp folder somewhere convenient on your hard drive.
 ```
├── bin
│   └── runtime
├── setenv.sh
└── lib
    └── libkevoree-model-dynamic.so
 ```

##### To start kevoree-cpp :
 ```
in your shell : 
. ./setenv.sh 
bin/runtime
 ```
##### Output
```
jed@jed:~/kev1.0.0/# bin/runtime
INFO: Kevoree Start event : node name = node0
INFO: TODO Model Checker
Downloading File  => http://maven.reacloud.com/repository/reacloud/release/org/kevoree/library/CPPNodeType/1.0.0/CPPNodeType-1.0.0.so
INFO: PreCompare BootStraping
INFO: Adaptation model size 2
Downloading File  => http://maven.reacloud.com/repository/reacloud/release/org/kevoree/library/kevoree-group-websocket/1.0.0/kevoree-group-websocket-1.0.0.so
INFO: Adaptation time delta (ms) = 8
INFO: Update sucessfully completed.
 ```

### Kevoree Runtime options : 

* -h: help
* -n: nodename  allows to associate a node name with the runtime
* -v: version
* -m: model  allows to give an initial bootstrap model (.json,.kev.kevs accepted)
* -l: debug level (0: Debug Model,1: Debug microframework, 2: Debug platform 3: info, 4: Error)


### Kevoree Editor: 

The kevC++ platform bootstrap by default with a group which listen on port 9000 you can pull the model with the awesome web editor :
http://editor.kevoree.org/

Model > From Custom Repo
```
repo  		http://maven.reacloud.com/nexus/content/groups/public
artifactId 	org.kevoree.library.cpp
artifactId 	CPPNodeType
version 	1.0.0
```



## KevScript 
```
repo "http://maven.reacloud.com/nexus/content/repositories/releases"
repo "http://maven.reacloud.com/nexus/content/repositories/snapshots/"
repo "http://repo.maven.apache.org/maven2"

include mvn:org.kevoree.library.cpp:cppnode:1.0.1-SNAPSHOT
include mvn:org.kevoree.library.cpp:fakeconsole:1.0.1-SNAPSHOT
include mvn:org.kevoree.library.cpp:kevoree-group-websocket:1.0.1-SNAPSHOT
include mvn:org.kevoree.library.cpp:sharedMemoryChannel:1.0.1-SNAPSHOT

add node0 : cppnode
add node0.comp314 : fakeconsole
add group0 : kevoree-group-websocket
add chan225 : sharedmemorychannel

attach node0 group0

bind node0.comp314.output chan225
bind node0.comp314.showin chan225

set group0.port/node0 = '9000'

network node0.ip.lo 127.0.0.1

```

For more information => https://github.com/kevoree/kevoree-web-editor


### Mac notes
Environement variables :
set your DYLIB_PATH to the Release/bin directory of kevoree 

### Linux notes

This binary release has been built and tested under :
- Ubuntu 14.04 LTS.
- cmake version 2.8.12.2
- GLIBCXX_3.4.16 
- gcc and g++ 4.8.2



 
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
#pragma Param "port" defaultValue="9000" fragdep optionnal

#pragma Param "core_cpu" defaultValue="10"  

 ```
fragdep 	: the annotation precise that the paramater is shared 
optionnal 	: 
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

mvn kevcpp:generate
 
mvn kevcpp:deploy


###  The Kevoree- Maven archetype:generate 
 ```
mvn archetype:generate -DarchetypeGroupId=org.kevoree.library.cpp -DarchetypeArtifactId=Kevoree-Cpp-Component-archetype -DarchetypeVersion=1.0.1-SNAPSHOT -DarchetypeCatalog=http://maven.reacloud.com/nexus/content/repositories/snapshots/
 ```


## Compile the platform 


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

## Generator Model KMF C++

KMF generates modeling frameworks and API for C++, from a domain metamodel.
It also offers comparison, merge and incremental synchronisation mechanisms tuned for Runtime use.

###  Start downloading the KMF Generator for C++
 ```
wget http://maven.reacloud.com/nexus/content/repositories/releases/org/kevoree/modeling/org.kevoree.modeling.cpp.generator/1.3.2/org.kevoree.modeling.cpp.generator-1.3.2.jar
 ```
 ### Usage 
 ```
usage: App
 -d,--enable <debug>      {true,false}
 -h,--help                prints the help content
 -i,--input <file>        ecore file
 -t,--output <directory>   Root Generation Directory
  ```
  ```
  java -jar org.kevoree.modeling.cpp.generator-1.3.2.jar -t kevoree.ecore -t model/
   ```
## FAQ

#### Dynamic library not found 
```
bin/runtime: error while loading shared libraries: libkevoree-model-dynamic.so: cannot open shared object file: No such file or directory
```
##### Fix 
```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$KEVORE_CPP_FOLDER/lib

export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$KEVORE_CPP_FOLDER/lib
```

#### Version of libc and libstdc++ 
```
bin/runtime: /lib/libc.so.6: version `GLIBC_2.14' not found (required by bin/runtime)
bin/runtime: /usr/lib/libstdc++.so.6: version `GLIBCXX_3.4.15' not found (required by bin/runtime)
bin/runtime: /lib/libc.so.6: version `GLIBC_2.17' not found (required by /home/jed/Bureau/kevCPP_1.0.0-BETA_64/lib/libkevoree-model-dynamic.so)
bin/runtime: /usr/lib/libstdc++.so.6: version `CXXABI_1.3.5' not found (required by /home/jed/Bureau/kevCPP_1.0.0-BETA_64/lib/libkevoree-model-dynamic.so)
bin/runtime: /usr/lib/libstdc++.so.6: version `GLIBCXX_3.4.15' not found (required by /home/jed/Bureau/kevCPP_1.0.0-BETA_64/lib/libkevoree-model-dynamic.so)
```
##### Fix 
```
You can compile the runtime by your own or upgrade the version of GLIBC
```

#### invalid ELF header

```
INFO: Kevoree Start event : node name = node0
INFO: Model Checker
ERROR: dlopen =>/tmp/.m2/org/kevoree/library/cpp/cppnode/1.0.1-SNAPSHOT/cppnode-1.0.1-20140731.142834-50.so: invalid ELF header
ERROR: failed install_deploy_unit /tmp/.m2/org/kevoree/library/cpp/cppnode/1.0.1-SNAPSHOT/cppnode-1.0.1-20140731.142834-50.so
ERROR: The DU is no registred
ERROR: The create instance fail
ERROR: The installation of the Typedefintion of the NodeType has fail, the runtime cannot start !
```
##### Fix 
```
mvn clean deploy of your typdefintion.
```

#Creating your first component
## requirement
* maven
* cmake
* c++ compiler
##Setting up the environment
* download a Kevoree Release
* Unzip it
* Set up a variable kevoreePath in your setting.xml in .m2 folder where is located Kevoree release as shown bellow

 ```
  
        <profile>
            <id>default-profile</id>
            <properties>
            <kevoreePath>/Users/Aymeric/Documents/dev_Kevoree/kevoree-cpp/Release</kevoreePath>
            	</properties>
        </profile>
 ```

#Start your project with maven archetypes
* open a terminal and enter the following command :
* 

 ```
 mvn archetype:generate -DarchetypeGroupId=org.kevoree.library.cpp -DarchetypeArtifactId=Kevoree-Cpp-Component-archetype -DarchetypeVersion=1.0.1-SNAPSHOT -DarchetypeCatalog=http://maven.reacloud.com/nexus/content/repositories/snapshots/  
 ```


 * Enter asked values
 * When maven asks to select the typedef you can choose either the following values :
	 * channel
	 * component
 	* group
 * once complete, go to the created directory
* ###Compilation and deployment
To build the component enter in your shell :

 ```
mvn compile
 ```


####Maven Plugin

To integrate the c++ compilation in the build process add the following lines: 
 ```
            <execution>
                        <phase>compile</phase>
                        <goals>
                            <goal>build-cmake</goal>
                        </goals>
                    </execution>
 ```
 
To include your libs and headers you can use the following lines :

 ```
                     <configuration>
                    <libs>
                        <lib>kevoree-model-dynamic</lib>
                        <lib>boost_system-mt</lib>
                        <lib>boost_thread-mt</lib>
                    </libs>
                    <headers>
                    <header> header directory 1</header>
                    </headers>
                </configuration>
 ```
