cmake_minimum_required(VERSION 2.8)
project(kevoree-core)


include_directories(../model)
include_directories(../../)
# BEGIN -- KEVOREE-CORE-IMPL

file(GLOB_RECURSE kevore_core_impl_files *)
ADD_LIBRARY(kevoree-core-impl  STATIC  ${kevore_core_impl_files})


# END --KEVOREE-CORE-IMPL




