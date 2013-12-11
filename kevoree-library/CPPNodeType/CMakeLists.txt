cmake_minimum_required(VERSION 2.8)
project(cppnode-cppnodeType)



include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)

# BEGIN -- KEVOREE- CPPNode
file(GLOB_RECURSE cppnodetype_library_files src/*)
ADD_LIBRARY(kevoree-CPPNode  SHARED    ${cppnodetype_library_files})
if(ANDROID)
TARGET_LINK_LIBRARIES(kevoree-CPPNode  -Wl,-no-whole-archive ${LIBRARY_OUTPUT_PATH}/libkevoree-core-model.a -Wl,-no-whole-archive)
ENDIF()


# END --  KEVOREE-CPPNode
