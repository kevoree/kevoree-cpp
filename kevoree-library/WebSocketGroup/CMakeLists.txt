cmake_minimum_required(VERSION 2.8)
project(websocket-group)



include_directories(.)
include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)

include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)
#find_package(Boost REQUIRED system random thread)

include_directories(${SRC_MICROFRAMEWORK}/)
file(GLOB_RECURSE websocket_group src/*)
ADD_LIBRARY(websocketgroup   SHARED    ${websocket_group})
TARGET_LINK_LIBRARIES(websocketgroup boost_system)
TARGET_LINK_LIBRARIES(websocketgroup boost_random)
TARGET_LINK_LIBRARIES(websocketgroup boost_thread)

if(ANDROID)
	TARGET_LINK_LIBRARIES(websocketgroup  ${LIBRARY_OUTPUT_PATH}/libkevoree-model.so )
ENDIF()


