cmake_minimum_required(VERSION 2.8)
project(DpkgManager-component)


include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)


file(GLOB_RECURSE files src/*)
ADD_LIBRARY(dpkgmanager SHARED    ${files})
