cmake_minimum_required(VERSION 2.8)
project(kevoree-platform)

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
include_directories(${SRC_KEVSCRIPT}/waxeye/include/waxeye)
include_directories(${SRC_KEVOREE_CORE}/api/queues/include)
include_directories(${SRC_KEVOREE_LOGGER}/)
file(GLOB_RECURSE kevoree-platform_files KevoreeBootStrap/*)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)

#COMPILE MAIN
add_executable(
        runtime
        standalone/main.cpp
        ${kevoree-platform_files}
)
TARGET_LINK_LIBRARIES(runtime  kevoree-tools)
TARGET_LINK_LIBRARIES(runtime  kevoree-logger)
TARGET_LINK_LIBRARIES(runtime  kevoree-core-impl)
TARGET_LINK_LIBRARIES(runtime  kevoree-model-dynamic)
TARGET_LINK_LIBRARIES(runtime  maven-resolver-cpp )
TARGET_LINK_LIBRARIES(runtime  libboost_thread-mt.a)
TARGET_LINK_LIBRARIES(runtime  libboost_system-mt.a)
TARGET_LINK_LIBRARIES(runtime  libboost_random-mt.a)
TARGET_LINK_LIBRARIES(runtime  libboost_program_options-mt.a)
TARGET_LINK_LIBRARIES(runtime  libboost_regex-mt.a)
TARGET_LINK_LIBRARIES(runtime  dl)
TARGET_LINK_LIBRARIES(runtime  pthread)
TARGET_LINK_LIBRARIES(runtime waxeye)
TARGET_LINK_LIBRARIES(runtime kevscript)
TARGET_LINK_LIBRARIES(runtime pthread)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
TARGET_LINK_LIBRARIES(runtime rt)
ENDIF()


