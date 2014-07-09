cmake_minimum_required(VERSION 2.8)
project(createtypedef)

include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)

include_directories(.)
include_directories(../)
include_directories(../kevoree-core/model/)
include_directories(../maven-resolver-cpp/src)

file(GLOB_RECURSE files src/*)


#COMPILE MAIN
add_executable(
        createType
        ${files}
)
TARGET_LINK_LIBRARIES(createType  kevoree-model-dynamic)
TARGET_LINK_LIBRARIES(createType  kevoree-tools)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
TARGET_LINK_LIBRARIES(createType kevoree-core-impl)
ENDIF()
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
TARGET_LINK_LIBRARIES(createType  -Wl,-all_load ${LIBRARY_OUTPUT_PATH}/libkevoree-core-impl.a)
ENDIF()

TARGET_LINK_LIBRARIES(createType  boost_thread-mt)
TARGET_LINK_LIBRARIES(createType  boost_system-mt)
TARGET_LINK_LIBRARIES(createType  boost_random-mt)
TARGET_LINK_LIBRARIES(createType boost_regex-mt)
TARGET_LINK_LIBRARIES(createType maven-resolver-cpp )
