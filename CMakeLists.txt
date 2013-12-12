cmake_minimum_required(VERSION 2.8)
project(kevoree-cpp)

#set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic" )
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/build)
add_definitions(-DENABLE_LOGGER)

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
 endif()
if(arch_hint MATCHES "ARM")
     set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/boost_elf32-arm/)
 endif() 
if(arch_hint MATCHES "x64")
     set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/boost_elf32-x64/)
 endif()  
 
if(ANDROID)
 set(arch_hint "ARM")
#jni is available by default on android
#find_package(JNI REQUIRED)
#include_directories(${JNI_INCLUDE_DIRS})
set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/boost_android_r8e/)
endif()

message("Architecture: ${arch_hint}")
message("Boost: ${BOOST_ROOT}")




set(SRC_KEVOREE_CORE 						kevoree-core)
set(SRC_KEVOREE_TOOLS 						kevoree-tools)
set(SRC_KEVOREE_PLATFORM 					kevoree-platform)
set(SRC_KEVOREE_LIBRARY 					kevoree-library)
set(SRC_KEVOREE_MODEL 						${SRC_KEVOREE_CORE}/model)
set(SRC_KEVOREE_ADAPTATION_MODEL_KEVOREE 	${SRC_KEVOREE_CORE}/model/kevoree.adaptation/)

set(CMAKE_CXX_FLAGS "-g ${CMAKE_CXX_FLAGS}")


add_subdirectory (maven-resolver-cpp/)
add_subdirectory (${SRC_KEVOREE_CORE}/)
add_subdirectory (${SRC_KEVOREE_TOOLS}/)
add_subdirectory (${SRC_KEVOREE_PLATFORM}/)
add_subdirectory (${SRC_KEVOREE_LIBRARY}/)

