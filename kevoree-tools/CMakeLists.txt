cmake_minimum_required(VERSION 2.8)
project(kevoree-tools)



include_directories(../)
include_directories(../kevoree-core/model/)
include_directories(../maven-resolver-cpp/src)
include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)

file(GLOB_RECURSE tools_loader DynamicLoader/*)
file(GLOB_RECURSE tools_BootstrapHelper BootstrapHelper/*)
ADD_LIBRARY(kevoree-tools  STATIC  ${tools_loader} ${tools_BootstrapHelper})
TARGET_LINK_LIBRARIES(kevoree-tools  maven-resolver-cpp)
TARGET_LINK_LIBRARIES(kevoree-tools   -Wl,-whole-archive ${LIBRARY_OUTPUT_PATH}/libmaven-resolver-cpp.a -Wl,-no-whole-archive)


add_subdirectory (CreateTypeDefinition/)