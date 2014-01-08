cmake_minimum_required(VERSION 2.8)
project(tests)

set(KEVOREEROOT ../)
set(SRC_KEVOREE_CORE  ${KEVOREEROOT}/kevoree-core)
set(SRC_MICROFRAMEWORK ${SRC_KEVOREE_CORE}/model/)


include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)




#COMPILE MAIN
add_executable(
        kmf1
        src/kmf1.cpp
)
TARGET_LINK_LIBRARIES(kmf1  ${LIBRARY_OUTPUT_PATH}/libkevoree-core-model.a)
TARGET_LINK_LIBRARIES(kmf1 rt)