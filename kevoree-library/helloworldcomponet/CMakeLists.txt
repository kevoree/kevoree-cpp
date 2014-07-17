cmake_minimum_required(VERSION 2.8)
project(helloworld-component)

include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)
include_directories(../../maven-resolver-cpp/src/)
include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)

file(GLOB_RECURSE helloworld_files src/*)
ADD_LIBRARY(helloworld_component  SHARED    ${helloworld_files})

TARGET_LINK_LIBRARIES(helloworld_component  boost_thread-mt)
TARGET_LINK_LIBRARIES(helloworld_component  boost_system-mt)
TARGET_LINK_LIBRARIES(helloworld_component  kevoree-model-dynamic)


if(ANDROID)
TARGET_LINK_LIBRARIES(helloworld_component -Wl,-no-whole-archive ${LIBRARY_OUTPUT_PATH}/libkevoree-model-static.a -Wl,-no-whole-archive)
ENDIF()

#TARGET_LINK_LIBRARIES(helloworld_component  libkevoree-model-dynamic.a )
# END --  KEVOREE-CPPNode
