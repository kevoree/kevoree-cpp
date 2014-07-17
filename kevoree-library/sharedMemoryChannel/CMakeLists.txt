cmake_minimum_required(VERSION 2.8)
project(sharedMemoryChannel-component)

include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)
include_directories(../../maven-resolver-cpp/src/)
include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)

file(GLOB_RECURSE files src/*)
ADD_LIBRARY(sharedMemoryChannel  SHARED    ${files})
TARGET_LINK_LIBRARIES(sharedMemoryChannel  kevoree-model-dynamic)



