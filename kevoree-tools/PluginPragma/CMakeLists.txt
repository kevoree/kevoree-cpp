cmake_minimum_required(VERSION 2.8)
project(plugin-pragma)





execute_process(COMMAND g++ -print-file-name=plugin OUTPUT_VARIABLE RESULT)
string(REPLACE "\n" "" RESULT ${RESULT})
set(INCLUDE_PATH_PLUGIN "${RESULT}/include/")
message("include ${INCLUDE_PATH_PLUGIN}")
include_directories(${INCLUDE_PATH_PLUGIN})


set(KEVOREEROOT ../../)
set(SRC_KEVOREE_CORE  ${KEVOREEROOT}/kevoree-core)
set(SRC_MICROFRAMEWORK ${SRC_KEVOREE_CORE}/model/)

include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)


file(GLOB_RECURSE files src/*)
ADD_LIBRARY(plugin-pragma  SHARED  ${files})
TARGET_LINK_LIBRARIES(plugin-pragma   ${LIBRARY_OUTPUT_PATH}/libkevoree-core-model.a)
TARGET_LINK_LIBRARIES(plugin-pragma rt)
