cmake_minimum_required(VERSION 2.8)
project(kevoree-core)

add_subdirectory (model/)
add_subdirectory (kevscript/)


include_directories(model)
include_directories(../)
include_directories(${SRC_KEVOREE_LOGGER}/)
include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)

file(GLOB_RECURSE kevore_core_impl_files src/*.cpp)


ADD_LIBRARY(kevoree-core-impl  STATIC  ${kevore_core_impl_files})
TARGET_LINK_LIBRARIES(kevoree-core-impl  kevoree-logger)
#************************************** INSTALL ****************************************************

install(DIRECTORY ${CMAKE_SOURCE_DIR}/kevoree-core DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/include FILES_MATCHING PATTERN "*.h")

