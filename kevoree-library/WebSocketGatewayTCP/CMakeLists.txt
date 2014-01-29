cmake_minimum_required(VERSION 2.8)
project(component-WebSocketGatewayTCP)



include_directories(.)
include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)

include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)
#find_package(Boost REQUIRED system random thread)
include_directories(${KEVOREEROOT}/${SRC_KEVOREE_HTTPCLIENT}/src)
include_directories(${SRC_MICROFRAMEWORK}/)
file(GLOB_RECURSE websockpp_files websocketpp/*)
file(GLOB_RECURSE gw_files src/*)
ADD_LIBRARY(WebSocketGatewayTCPComponent   SHARED    ${gw_files} ${websockpp_files})
TARGET_LINK_LIBRARIES(WebSocketGatewayTCPComponent boost_system)
TARGET_LINK_LIBRARIES(WebSocketGatewayTCPComponent boost_thread)
TARGET_LINK_LIBRARIES(WebSocketGatewayTCPComponent boost_regex)
TARGET_LINK_LIBRARIES(WebSocketGatewayTCPComponent boost_random)








