cmake_minimum_required(VERSION 2.8)
project(helloworld-component)


include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)


file(GLOB_RECURSE helloworld_files src/*)
ADD_LIBRARY(helloworld_component  MODULE    ${helloworld_files})
