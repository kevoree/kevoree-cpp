cmake_minimum_required(VERSION 2.8)
project(kevoree-core)


include_directories(../model)
include_directories(../../)

include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)

file(GLOB_RECURSE kevore_core_impl_files impl/*)
ADD_LIBRARY(kevoree-core-impl  STATIC  ${kevore_core_impl_files})


# END --KEVOREE-CORE-IMPL




