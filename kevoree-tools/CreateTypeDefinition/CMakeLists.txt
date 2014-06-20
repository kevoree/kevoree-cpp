cmake_minimum_required(VERSION 2.8)
project(createtypedef)

include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)
message("${BOOST_ROOT}")
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
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
TARGET_LINK_LIBRARIES(createType 	${LIBRARY_OUTPUT_PATH}/libkevoree-tools.a)
TARGET_LINK_LIBRARIES(createType  -Wl,-whole-archive ${LIBRARY_OUTPUT_PATH}/libkevoree-core-impl.a  -Wl,-no-whole-archive)
TARGET_LINK_LIBRARIES(createType  -Wl,-whole-archive ${LIBRARY_OUTPUT_PATH}/libkevoree-model-static.a -Wl,-no-whole-archive)
ENDIF()

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
TARGET_LINK_LIBRARIES(createType 	${LIBRARY_OUTPUT_PATH}/libkevoree-tools.a)
TARGET_LINK_LIBRARIES(createType  -Wl,-all_load ${LIBRARY_OUTPUT_PATH}/libkevoree-core-impl.a)
TARGET_LINK_LIBRARIES(createType  -Wl,-all_load ${LIBRARY_OUTPUT_PATH}/libkevoree-model-static.a)
ENDIF()



TARGET_LINK_LIBRARIES(createType maven-resolver-cpp )
TARGET_LINK_LIBRARIES(createType  boost_thread)
TARGET_LINK_LIBRARIES(createType  boost_system)
TARGET_LINK_LIBRARIES(createType  boost_random)
TARGET_LINK_LIBRARIES(createType boost_regex)
