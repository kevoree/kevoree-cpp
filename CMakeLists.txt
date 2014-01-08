cmake_minimum_required(VERSION 2.8)
project(kevoree-cpp)
set(KEVOREE_CPP_VERSION_MAJOR 0)
set(KEVOREE_CPP_VERSION_MINOR 1)
set(KEVOREE_CPP_VERSION ${KEVOREE_CPP_VERSION_MAJOR}.${KEVOREE_CPP_VERSION_MINOR})


#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/build)

set(PRAGMA_PLUGIN "TRUE")
add_definitions(-DENABLE_LOGGER)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

   SET(ENABLE_CXX11 "-std=c++11")
   EXECUTE_PROCESS(COMMAND "${CMAKE_CXX_COMPILER} -dumpversion" OUTPUT_VARIABLE GCC_VERSION)
   if (GCC_VERSION VERSION_LESS 4.7)
      SET(ENABLE_CXX11 "-std=c++0x")
   endif()
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENABLE_CXX11}")
endif()


if("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
    set(arch_hint "x64")
  elseif("${CMAKE_GENERATOR}" MATCHES "ARM")
    set(arch_hint "ARM")
  elseif("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
    set(arch_hint "x64")
  elseif("$ENV{LIB}" MATCHES "(amd64|ia64)")
    set(arch_hint "x64")
  endif()

if(NOT arch_hint)
   set(arch_hint "x86")
   set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/boost_elf32-i386/)
   set(BOOST_FILE boost_elf32-i386)	
 endif()
if(arch_hint MATCHES "ARM")
     set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/boost_elf32-arm/)
     set(BOOST_FILE boost_elf32-arm)	
 endif() 
if(arch_hint MATCHES "x64")
     set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/boost_efl64-x64/)
     set(BOOST_FILE boost_efl64-x64)
endif()      

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
      set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/boost_x64_osx/)
      set(BOOST_FILE boost_x64_osx)	
endif()  
 
 
if(ANDROID)
 set(arch_hint "ARM")
#jni is available by default on android
#find_package(JNI REQUIRED)
#include_directories(${JNI_INCLUDE_DIRS})
set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/boost_android_r8e/)
set(BOOST_FILE boost_android_r8e)	
set(BOOST_INCLUDEDIR ${CMAKE_SOURCE_DIR}/thirdparty/boost_android_r8e/)
set(ANDROID_PACKAGE_NAME "org.kevoreecpp.runtime")
set(android_target "android-9")
endif()

message("Current OS	         : ${CMAKE_SYSTEM_NAME}")
message("Current Architecture: ${CMAKE_GENERATOR}")
message("Target  Architecture: ${arch_hint}")
message("Boost: ${BOOST_ROOT}")
message("${ENABLE_CXX11}")

 IF(NOT EXISTS "${BOOST_ROOT}")
            message("Downloading boost for ${arch_hint}")
			execute_process(COMMAND wget http://powet.eu/kevoree/${BOOST_FILE}.tar.gz --quiet)
			execute_process(COMMAND tar xvf ${BOOST_FILE}.tar.gz)
			execute_process(COMMAND mkdir thirdparty/)
			execute_process(COMMAND mv  ${BOOST_FILE}/ thirdparty/)
			execute_process(COMMAND rm  ${BOOST_FILE}.tar.gz)
 ENDIF()


set(SRC_KEVOREE_CORE 						kevoree-core)
set(SRC_KEVOREE_TOOLS 						kevoree-tools)
set(SRC_KEVOREE_PLATFORM 					kevoree-platform)
set(SRC_KEVOREE_LIBRARY 					kevoree-library)
set(SRC_KEVOREE_CXX_PLUGIN 					${SRC_KEVOREE_TOOLS}/PluginPragma)
set(SRC_KEVOREE_MODEL 						${SRC_KEVOREE_CORE}/model/kevoree)
set(SRC_KEVOREE_TESTS 						tests)
set(SRC_MAVEN_RESOLVER maven-resolver-cpp)
set(URL_MODEL_GENERATOR "http://oss.sonatype.org/content/repositories/snapshots/org/kevoree/modeling/org.kevoree.modeling.cpp.generator/1.1-SNAPSHOT/org.kevoree.modeling.cpp.generator-1.1-20140108.093923-10.jar")

set(CMAKE_CXX_FLAGS "-g ${CMAKE_CXX_FLAGS}")

IF(NOT EXISTS "${SRC_MAVEN_RESOLVER}" )
 execute_process(COMMAND git clone "https://github.com/Jean-Emile/maven-resolver-cpp.git")
ENDIF()

IF(NOT EXISTS "${SRC_KEVOREE_MODEL}")
 message("Downloading model generator")
 execute_process(COMMAND wget ${URL_MODEL_GENERATOR} --quiet)
 message("Generate KEVOREE MODEL")
 execute_process(COMMAND java -jar org.kevoree.modeling.cpp.generator-1.1-20131217.093441-9.jar -i kevoree-core/model/metamodel/kevoree.ecore -t kevoree-core/model)
ENDIF()



add_subdirectory (${SRC_MAVEN_RESOLVER}/)
add_subdirectory (${SRC_KEVOREE_CORE}/)
add_subdirectory (${SRC_KEVOREE_TOOLS}/)
add_subdirectory (${SRC_KEVOREE_PLATFORM}/)
if(PRAGMA_PLUGIN MATCHES "TRUE")
message("Compile Pragma plugin")
add_subdirectory (${SRC_KEVOREE_CXX_PLUGIN}/)
ENDIF()

add_subdirectory (${SRC_KEVOREE_LIBRARY}/)
add_subdirectory (${SRC_KEVOREE_TESTS}/)

