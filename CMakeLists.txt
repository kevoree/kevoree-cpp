cmake_minimum_required(VERSION 2.8)
project(kmf)


set(CMAKE_CXX_FLAGS "-Ofast ${CMAKE_CXX_FLAGS}")

set(SRC_KEVOREE_CORE kevoree-core)
set(SRC_KEVOREE_MODEL ${SRC_KEVOREE_CORE}/model)

set(SRC_SPARSEHASH ${SRC_KEVOREE_MODEL}/sparsehash)
set(SRC_MICROFRAMEWORK ${SRC_KEVOREE_MODEL}/microframework/api)


include_directories(${SRC_SPARSEHASH})
include_directories(${SRC_SPARSEHASH}/google)
include_directories(${SRC_SPARSEHASH}/sparsehash)
include_directories(${SRC_SPARSEHASH}/sparsehash/internal)

include_directories(${SRC_MICROFRAMEWORK})
include_directories(${SRC_MICROFRAMEWORK}/compare)
include_directories(${SRC_MICROFRAMEWORK}/events)
include_directories(${SRC_MICROFRAMEWORK}/json)
include_directories(${SRC_MICROFRAMEWORK}/trace)
include_directories(${SRC_MICROFRAMEWORK}/utils)
include_directories(${SRC_MICROFRAMEWORK}/container)

include_directories(${SRC_KEVOREE_MODEL}/kevoree/)


add_executable(
        main
        main.cpp
)


TARGET_LINK_LIBRARIES(main ${CMAKE_BINARY_DIR}/kevoree-core/model/libkevoree.a)
TARGET_LINK_LIBRARIES(main rt)
TARGET_LINK_LIBRARIES(main dl)
