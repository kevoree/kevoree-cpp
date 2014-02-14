cmake_minimum_required(VERSION 2.8)
project(kevoree-model)


set(SRC_KEVOREE_MODEL 						kevoree/)
set(SRC_KEVOREE_ADAPTATION_MODEL_KEVOREE 	adaptation/)
set(SRC_MICROFRAMEWORK 						microframework/)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(.)
include_directories(${SRC_MICROFRAMEWORK}/)
include_directories(${SRC_KEVOREE_MODEL}/)
include_directories(${SRC_KEVOREE_ADAPTATION_MODEL_KEVOREE}/)

file(GLOB_RECURSE microframework_files ${SRC_MICROFRAMEWORK}/*)
file(GLOB_RECURSE model_files ${SRC_KEVOREE_MODEL}/*)
file(GLOB_RECURSE adaptation_model_files ${SRC_KEVOREE_ADAPTATION_MODEL_KEVOREE}/*)

ADD_LIBRARY(kevoree-core-model  STATIC   ${microframework_files} ${model_files} ${adaptation_model_files})
ADD_LIBRARY(kevoree-model  SHARED   ${microframework_files} ${model_files} ${adaptation_model_files})
