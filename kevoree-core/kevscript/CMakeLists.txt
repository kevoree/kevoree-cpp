cmake_minimum_required(VERSION 2.8)
project(kevscript)

set(SRC_KEVOREE_KEVSCRIPT 						src/)


include_directories(.)
include_directories(${SRC_KEVOREE_KEVSCRIPT}/)
include_directories(${SRC_KEVOREE_KEVSCRIPT}/waxeye/include)

file(GLOB_RECURSE kevscript_files ${SRC_KEVOREE_KEVSCRIPT}/*)



ADD_LIBRARY(kevoree-kevscript-static  	STATIC   ${kevscript_files})