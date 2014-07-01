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


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)

#COMPILE MAIN
add_executable(
        main
        standalone/main.cpp
        ${kevoree-platform_files}
)


IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
TARGET_LINK_LIBRARIES(main 	-Wl,-whole-archive ${LIBRARY_OUTPUT_PATH}/libkevoree-tools.a)
TARGET_LINK_LIBRARIES(main  -Wl,-whole-archive ${LIBRARY_OUTPUT_PATH}/libkevoree-core-impl.a -Wl,-no-whole-archive)
TARGET_LINK_LIBRARIES(main rt)
ENDIF()

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
TARGET_LINK_LIBRARIES(main 	${LIBRARY_OUTPUT_PATH}/libkevoree-tools.a)
TARGET_LINK_LIBRARIES(main  -Wl,-all_load ${LIBRARY_OUTPUT_PATH}/libkevoree-core-impl.a)
TARGET_LINK_LIBRARIES(main 	-Wl,-all_load ${LIBRARY_OUTPUT_PATH}/libkevoree-tools.a)
ENDIF()


TARGET_LINK_LIBRARIES(main  kevoree-model-dynamic)
TARGET_LINK_LIBRARIES(main maven-resolver-cpp )
TARGET_LINK_LIBRARIES(main  boost_thread-mt)
TARGET_LINK_LIBRARIES(main  boost_system-mt)
TARGET_LINK_LIBRARIES(main  boost_random-mt)
TARGET_LINK_LIBRARIES(main  boost_program_options-mt)
TARGET_LINK_LIBRARIES(main boost_regex-mt)
TARGET_LINK_LIBRARIES(main dl)
TARGET_LINK_LIBRARIES(main pthread)




