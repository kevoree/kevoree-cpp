cmake_minimum_required(VERSION 2.8)
project(kevoree-core)



add_subdirectory (model/)
add_subdirectory (kevscript/)


include_directories(model)
include_directories(../)



file(GLOB_RECURSE INCS "*.h")
file(COPY  ${INCS} DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/include)

include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)


file(GLOB_RECURSE kevore_core_impl_files src/*)
ADD_LIBRARY(kevoree-core-impl  STATIC  ${kevore_core_impl_files})

