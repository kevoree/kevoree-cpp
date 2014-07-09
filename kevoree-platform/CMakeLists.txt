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
TARGET_LINK_LIBRARIES(main 	kevoree-tools)
TARGET_LINK_LIBRARIES(main  kevoree-core-impl)
TARGET_LINK_LIBRARIES(main  kevoree-model-dynamic)
TARGET_LINK_LIBRARIES(main  maven-resolver-cpp )
TARGET_LINK_LIBRARIES(main  libboost_thread-mt.a)
TARGET_LINK_LIBRARIES(main  libboost_system-mt.a)
TARGET_LINK_LIBRARIES(main  libboost_random-mt.a)
TARGET_LINK_LIBRARIES(main  libboost_program_options-mt.a)
TARGET_LINK_LIBRARIES(main  libboost_regex-mt.a)
TARGET_LINK_LIBRARIES(main  dl)
TARGET_LINK_LIBRARIES(main  pthread)


IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
TARGET_LINK_LIBRARIES(main rt)
ENDIF()







