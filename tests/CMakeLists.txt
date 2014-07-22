cmake_minimum_required(VERSION 2.8)
project(tests)


include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)
set(KEVOREEROOT ../)
set(SRC_KEVOREE_CORE  ${KEVOREEROOT}/kevoree-core)
set(SRC_MICROFRAMEWORK ${SRC_KEVOREE_CORE}/model/)
set(SRC_KEVSCRIPT ${SRC_KEVOREE_CORE}/kevscript)
set(SRC_KEVTOOLS ${KEVOREEROOT}/kevoree-tools/)

include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)
include_directories(../maven-resolver-cpp/src)
include_directories(${SRC_KEVSCRIPT}/src)
include_directories(${SRC_KEVSCRIPT}/waxeye/include)
include_directories(${SRC_KEVOREE_CORE}/api/queues/include)



SET(COMMON_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
SET(COMMON_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/libs")



file(GLOB_RECURSE files_tests src/tests/*)
add_executable(
        run_tests
        src/run_tests.cpp
        ${files_tests}
)
TARGET_LINK_LIBRARIES(run_tests 	kevoree-tools)
TARGET_LINK_LIBRARIES(run_tests  kevoree-core-impl)
TARGET_LINK_LIBRARIES(run_tests  kevoree-model-dynamic)
TARGET_LINK_LIBRARIES(run_tests  maven-resolver-cpp )
TARGET_LINK_LIBRARIES(run_tests  libboost_thread-mt.a)
TARGET_LINK_LIBRARIES(run_tests  libboost_system-mt.a)
TARGET_LINK_LIBRARIES(run_tests  libboost_random-mt.a)
TARGET_LINK_LIBRARIES(run_tests  libboost_program_options-mt.a)
TARGET_LINK_LIBRARIES(run_tests  libboost_regex-mt.a)
TARGET_LINK_LIBRARIES(run_tests  dl)
TARGET_LINK_LIBRARIES(run_tests  pthread)
TARGET_LINK_LIBRARIES(run_tests waxeye)
TARGET_LINK_LIBRARIES(run_tests kevscript)
TARGET_LINK_LIBRARIES(run_tests cppunit)
TARGET_LINK_LIBRARIES(run_tests pthread)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
TARGET_LINK_LIBRARIES(run_tests rt)
ENDIF()



ADD_CUSTOM_TARGET(test
COMMAND  ${KEVOREEROOT}/tests/run_tests)