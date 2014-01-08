cmake_minimum_required(VERSION 2.8)
project(tests)

set(KEVOREEROOT ../)
set(SRC_KEVOREE_CORE  ${KEVOREEROOT}/kevoree-core)
set(SRC_MICROFRAMEWORK ${SRC_KEVOREE_CORE}/model/)


include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)


FIND_PACKAGE(CPPUNIT REQUIRED)


SET(COMMON_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
SET(COMMON_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/libs")



file(GLOB_RECURSE files_tests src/tests/*.cpp)
add_executable(
        run_tests
        src/run_tests.cpp
        ${files_tests}
)
TARGET_LINK_LIBRARIES(run_tests cppunit)
TARGET_LINK_LIBRARIES(run_tests ${LIBRARY_OUTPUT_PATH}/libkevoree-model.so)
TARGET_LINK_LIBRARIES(run_tests rt)
