cmake_minimum_required(VERSION 2.8)
project(kevoree-platform)



include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)
message("${BOOST_ROOT}")
include_directories(.)
include_directories(../)
include_directories(../kevoree-core/model/)
include_directories(../maven-resolver-cpp/src)


file(GLOB_RECURSE kevoree-platform_files KevoreeBootStrap/*)


#COMPILE MAIN
add_executable(
        main
        standalone/main.cpp
        ${kevoree-platform_files}
)

TARGET_LINK_LIBRARIES(main 	${LIBRARY_OUTPUT_PATH}/libkevoree-tools.a)
TARGET_LINK_LIBRARIES(main  -Wl,-whole-archive ${LIBRARY_OUTPUT_PATH}/libkevoree-core-impl.a  -Wl,-no-whole-archive)
TARGET_LINK_LIBRARIES(main  -Wl,-whole-archive ${LIBRARY_OUTPUT_PATH}/libkevoree-model-static.a -Wl,-no-whole-archive)
TARGET_LINK_LIBRARIES(main  -Wl,-whole-archive ${LIBRARY_OUTPUT_PATH}/libkevoree-kevscript-static.a -Wl,-no-whole-archive)

TARGET_LINK_LIBRARIES(main maven-resolver-cpp )
TARGET_LINK_LIBRARIES(main  boost_thread)
TARGET_LINK_LIBRARIES(main  boost_system)
TARGET_LINK_LIBRARIES(main  boost_random)
TARGET_LINK_LIBRARIES(main boost_regex)
TARGET_LINK_LIBRARIES(main dl)




IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

if(NOT ANDROID)
	TARGET_LINK_LIBRARIES(main rt)
	TARGET_LINK_LIBRARIES(main pthread)
ENDIF()

ENDIF()








