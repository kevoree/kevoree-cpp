cmake_minimum_required(VERSION 2.8)
project(helloworld-component)

set(CMAKE_CXX_FLAGS "-g ${CMAKE_CXX_FLAGS}")
ADD_DEFINITIONS("-std=c++0x") 

set(KEVOREEROOT ../../)
include_directories(${KEVOREEROOT}/)
set(SRC_KEVOREE_CORE  ${KEVOREEROOT}/kevoree-core)
set(SRC_MICROFRAMEWORK ${SRC_KEVOREE_CORE}/model/)
include_directories(${SRC_MICROFRAMEWORK}/)


file(GLOB_RECURSE helloworld_files src/*)
ADD_LIBRARY(helloworld_component  SHARED    ${helloworld_files})
