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


TARGET_LINK_LIBRARIES(websocketgroup -Wl,-whole-archive boost_system -Wl,-no-whole-archive)
TARGET_LINK_LIBRARIES(websocketgroup -Wl,-whole-archive boost_random -Wl,-no-whole-archive)
TARGET_LINK_LIBRARIES(websocketgroup -Wl,-whole-archive boost_thread -Wl,-no-whole-archive)
if(ANDROID)
TARGET_LINK_LIBRARIES(websocketgroup  -Wl,-no-whole-archive ${LIBRARY_OUTPUT_PATH}/libkevoree-core-model.a -Wl,-no-whole-archive)
ENDIF()




#add_executable(
#        server
#       server.cpp
#)
#TARGET_LINK_LIBRARIES(server ${CMAKE_CURRENT_SOURCE_DIR}/libwebsocketgroup.so)
#TARGET_LINK_LIBRARIES(server boost_system)

#add_executable(
#        client
#        client.cpp
#)
#TARGET_LINK_LIBRARIES(client ${CMAKE_CURRENT_SOURCE_DIR}/libwebsocketgroup.so)
#TARGET_LINK_LIBRARIES(client boost_system)
#TARGET_LINK_LIBRARIES(client boost_random)
#TARGET_LINK_LIBRARIES(client pthread)

