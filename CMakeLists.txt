cmake_minimum_required(VERSION 2.8)
project(kevoree-cpp)



SET(CMAKE_C_COMPILER arm-linux-gnueabi-gcc) 
SET(CMAKE_CXX_COMPILER arm-linux-gnueabi-g++-4.6)

set(CMAKE_CXX_FLAGS "-Ofast ${CMAKE_CXX_FLAGS}")

set(SRC_KEVOREE_PLATFORM kevoree-platform)
set(SRC_KEVOREE_CORE kevoree-core)
include_directories(${SRC_KEVOREE_CORE}/)


# BEGIN -- KMF-MICROFRAMEWORK
set(SRC_KEVOREE_MODEL ${SRC_KEVOREE_CORE}/model)
set(SRC_KEVOREE_MODEL_KEVOREE ${SRC_KEVOREE_CORE}/model/kevoree/)
set(SRC_SPARSEHASH ${SRC_KEVOREE_MODEL}/sparsehash)
set(SRC_MICROFRAMEWORK ${SRC_KEVOREE_MODEL}/microframework/api)
include_directories(${SRC_KEVOREE_MODEL}/)
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
# END -- KMF-MICROFRAMEWORK




set(SRC_KEVOREE_CORE_API ${SRC_KEVOREE_CORE})
include_directories(${SRC_KEVOREE_CORE_API})

# BEGIN -- KEVORE-CORE-MODEL 

# COMPILE  
file(GLOB_RECURSE microframework_files ${SRC_MICROFRAMEWORK}/*)
file(GLOB_RECURSE model_files ${SRC_KEVOREE_MODEL_KEVOREE}/*)
ADD_LIBRARY(kevoree-core-model  STATIC   ${microframework_files} ${model_files}  )
# END -- KEVORE-CORE-MODEL 


# BEGIN -- KEVORE-CORE-IMPL

file(GLOB_RECURSE kevore_core_impl_files ${SRC_KEVOREE_CORE}/core/impl/*)

ADD_LIBRARY(kevoree-core-impl  STATIC  ${kevore_core_impl_files})

# END --KEVORE-CORE-IMPL





# BEGIN -- KEVORE-PLATFORM
include_directories(${SRC_KEVOREE_PLATFORM})
file(GLOB_RECURSE kevoree-platform_files ${SRC_KEVOREE_PLATFORM}/base/*)

# END --  KEVORE-PLATFORM





#COMPILE MAIN
add_executable(
        main
        main.cpp
        ${kevoree-platform_files}
)


TARGET_LINK_LIBRARIES(main ${CMAKE_CURRENT_BINARY_DIR}/libkevoree-core-impl.a)
TARGET_LINK_LIBRARIES(main ${CMAKE_CURRENT_BINARY_DIR}/libkevoree-core-model.a)

TARGET_LINK_LIBRARIES(main rt)
TARGET_LINK_LIBRARIES(main dl)
