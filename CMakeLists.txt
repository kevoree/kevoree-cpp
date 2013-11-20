cmake_minimum_required(VERSION 2.8)
project(kevoree-cpp)

#SET(CMAKE_C_COMPILER arm-linux-gnueabi-gcc) 
#SET(CMAKE_CXX_COMPILER arm-linux-gnueabi-g++-4.6)

set(CMAKE_CXX_FLAGS "-O3 ${CMAKE_CXX_FLAGS}")
ADD_DEFINITIONS("-std=c++0x") 

set(SRC_KEVOREE_CORE 		kevoree-core)
set(SRC_KEVOREE_TOOLS 		kevoree-tools)
set(SRC_KEVOREE_PLATFORM 	kevoree-platform)
set(SRC_KEVOREE_LIBRARY 	kevoree-library)

include_directories(.)


# BEGIN -- KMF-MICROFRAMEWORK
set(SRC_KEVOREE_MODEL 						${SRC_KEVOREE_CORE}/model)
set(SRC_KEVOREE_ADAPTATION_MODEL_KEVOREE 	${SRC_KEVOREE_CORE}/model/kevoree.adaptation/)
set(SRC_MICROFRAMEWORK ${SRC_KEVOREE_CORE}/model/)

include_directories(${SRC_MICROFRAMEWORK}/)
include_directories(${SRC_KEVOREE_MODEL}/)
include_directories(${SRC_KEVOREE_ADAPTATION_MODEL_KEVOREE}/)

# END -- KMF-MICROFRAMEWORK




# BEGIN -- KEVORE-CORE-MODEL 

# COMPILE  
file(GLOB_RECURSE microframework_files ${SRC_MICROFRAMEWORK}/*)
file(GLOB_RECURSE model_files ${SRC_KEVOREE_MODEL}/*)
file(GLOB_RECURSE adaptation_model_files ${SRC_KEVOREE_ADAPTATION_MODEL_KEVOREE}/*)
ADD_LIBRARY(kevoree-core-model  STATIC   ${microframework_files} ${model_files} ${adaptation_model_files} )

# END -- KEVORE-CORE-MODEL 


# BEGIN -- KEVORE-CORE-IMPL

file(GLOB_RECURSE kevore_core_impl_files ${SRC_KEVOREE_CORE}/core/impl/*)

ADD_LIBRARY(kevoree-core-impl  STATIC  ${kevore_core_impl_files})

# END --KEVORE-CORE-IMPL





# BEGIN -- KEVORE-PLATFORM
include_directories(${SRC_KEVOREE_PLATFORM})
file(GLOB_RECURSE kevoree-platform_files ${SRC_KEVOREE_PLATFORM}/base/*)
# END --  KEVORE-PLATFORM


# BEGIN -- KEVORE-TOOLS
include_directories(${SRC_KEVOREE_TOOLS})
file(GLOB_RECURSE kevoree_tools_files ${SRC_KEVOREE_TOOLS}/*)
ADD_LIBRARY(kevoree-tools  STATIC  ${kevoree_tools_files})
# END --  KEVORE-TOOLS


# BEGIN -- KEVORE- CPPNode
file(GLOB_RECURSE cppnodetype_library_files ${SRC_KEVOREE_LIBRARY}/CPPNodeType/*)
ADD_LIBRARY(kevoree-CPPNode  SHARED    ${cppnodetype_library_files})
# END --  KEVORE-CPPNode



#COMPILE MAIN
add_executable(
        main
        main.cpp
        ${kevoree-platform_files}
)


TARGET_LINK_LIBRARIES(main ${CMAKE_CURRENT_BINARY_DIR}/libkevoree-core-impl.a)
TARGET_LINK_LIBRARIES(main ${CMAKE_CURRENT_BINARY_DIR}/libkevoree-core-model.a)
#TARGET_LINK_LIBRARIES(main ${CMAKE_CURRENT_BINARY_DIR}/libkevoree-CPPNode.a)
TARGET_LINK_LIBRARIES(main ${CMAKE_CURRENT_BINARY_DIR}/libkevoree-tools.a)

TARGET_LINK_LIBRARIES(main rt)
TARGET_LINK_LIBRARIES(main dl)
