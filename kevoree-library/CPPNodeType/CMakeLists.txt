cmake_minimum_required(VERSION 2.8)
project(cppnode-cppnodeType)



include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)

# BEGIN -- KEVOREE- CPPNode
file(GLOB_RECURSE cppnodetype_library_files src/*)
ADD_LIBRARY(kevoree-CPPNode  SHARED    ${cppnodetype_library_files})
#TARGET_LINK_LIBRARIES(kevoree-CPPNode ${CMAKE_CURRENT_BINARY_DIR}/libkevoree-core-model.a)
# END --  KEVOREE-CPPNode
