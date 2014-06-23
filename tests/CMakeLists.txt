cmake_minimum_required(VERSION 2.8)
project(tests)

set(KEVOREEROOT ../)
set(SRC_KEVOREE_CORE  ${KEVOREEROOT}/kevoree-core)
set(SRC_MICROFRAMEWORK ${SRC_KEVOREE_CORE}/model/)
set(SRC_KEVSCRIPT ${SRC_KEVOREE_CORE}/kevscript)


include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)

include_directories(${SRC_KEVSCRIPT}/src)
include_directories(${SRC_KEVSCRIPT}/waxeye/include)

#FIND_PACKAGE(CPPUNIT REQUIRED)


SET(COMMON_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
SET(COMMON_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/libs")



file(GLOB_RECURSE files_tests src/tests/*.cpp)
add_executable(
        run_tests
        src/run_tests.cpp
        ${files_tests}
)
TARGET_LINK_LIBRARIES(run_tests ${LIBRARY_OUTPUT_PATH}/libkevoree-model-dynamic.so)
TARGET_LINK_LIBRARIES(run_tests waxeye)


TARGET_LINK_LIBRARIES(run_tests rt)
TARGET_LINK_LIBRARIES(run_tests cppunit)

ADD_CUSTOM_TARGET(test
COMMAND  ${KEVOREEROOT}/tests/run_tests)