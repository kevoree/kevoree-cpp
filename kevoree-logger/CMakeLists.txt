cmake_minimum_required(VERSION 2.8)
project(kevoree-logger)




file(GLOB_RECURSE files api/*.cpp)


ADD_LIBRARY(kevoree-logger SHARED    ${files}  ) #${HEADERS_MOC}


