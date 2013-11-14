cmake_minimum_required(VERSION 2.8)
project(kevoree-cpp)

set(CMAKE_CXX_FLAGS "-Ofast ${CMAKE_CXX_FLAGS}")

set(SRC_KEVOREE_CORE kevoree-core)

# BEGIN -- KEVORE-CORE-MODEL 
set(SRC_KEVOREE_MODEL ${SRC_KEVOREE_CORE}/model)
set(SRC_KEVOREE_MODEL_KEVOREE ${SRC_KEVOREE_CORE}/model/kevoree/)
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
include_directories(${SRC_KEVOREE_MODEL_KEVOREE})

# COMPILE  
file(GLOB_RECURSE microframework_files ${SRC_MICROFRAMEWORK}/*)
file(GLOB_RECURSE model_files ${SRC_KEVOREE_MODEL_KEVOREE}/*)
ADD_LIBRARY(kevoree-core-model  STATIC   ${microframework_files} ${model_files}  )
# END -- KEVORE-CORE-MODEL 

# BEGIN -- KEVORE-CORE-API 
set(SRC_KEVOREE_CORE_API ${SRC_KEVOREE_CORE})

include_directories(${SRC_KEVOREE_CORE_API})

# END -- KEVORE-CORE-API 


# BEGIN -- KEVORE-CORE


file(GLOB_RECURSE kevore_core_files ${SRC_KEVOREE_CORE}/impl/*)
ADD_LIBRARY(kevoree-core-impl  STATIC   ${kevore_core_files} )


# END -- KEVORE-CORE



#COMPILE MAIN
add_executable(
        main
        main.cpp
)

TARGET_LINK_LIBRARIES(main ${CMAKE_CURRENT_BINARY_DIR}/libkevoree-core-model.a)
TARGET_LINK_LIBRARIES(main ${CMAKE_CURRENT_BINARY_DIR}/libkevoree-core-impl.a)
TARGET_LINK_LIBRARIES(main rt)
TARGET_LINK_LIBRARIES(main dl)
