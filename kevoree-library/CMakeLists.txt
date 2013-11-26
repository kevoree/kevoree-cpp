cmake_minimum_required(VERSION 2.8)
project(kevoree-library)


set(CMAKE_CXX_FLAGS "-O3 ${CMAKE_CXX_FLAGS}")
ADD_DEFINITIONS("-std=c++0x") 

set(KEVOREEROOT ../../)
set(SRC_KEVOREE_CORE  ${KEVOREEROOT}/kevoree-core)
set(SRC_MICROFRAMEWORK ${SRC_KEVOREE_CORE}/model/)


add_subdirectory (WebSocketGroup/)
add_subdirectory (HelloWorldComponent/)
add_subdirectory (CPPNodeType/)
