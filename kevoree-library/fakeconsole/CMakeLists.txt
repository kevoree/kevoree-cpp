cmake_minimum_required(VERSION 2.8)
project(fakeconsole-component)

include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)
include_directories(../../maven-resolver-cpp/src/)
include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)

file(GLOB_RECURSE files src/*)
ADD_LIBRARY(fakeconsole_component  SHARED    ${files})
TARGET_LINK_LIBRARIES(fakeconsole_component  kevoree-model-dynamic)




