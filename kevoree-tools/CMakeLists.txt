cmake_minimum_required(VERSION 2.8)
project(kevoree-tools)



include_directories(../)
include_directories(../kevoree-core/model/)
include_directories(../maven-resolver-cpp/src/api)
include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)

file(GLOB_RECURSE tools_loader DynamicLoader/*)
file(GLOB_RECURSE tools_BootstrapHelper BootstrapHelper/*)
ADD_LIBRARY(kevoree-tools  STATIC  ${tools_loader} ${tools_BootstrapHelper})
