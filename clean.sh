#!/bin/sh

# I want to do only out-of-source builds. So sometimes I need to clean stuff ..
find . -name "CMakeFiles" | xargs rm -rf
find . -name "Makefile" | xargs rm -rf
find . -name "cmake_install.cmake_modules" | xargs rm -rf
find . -name "cmake_install.cmake" | xargs rm -rf
find . -name "CMakeCache.txt" | xargs rm -rf
                                          
rm -rf kevoree-core/model/kevoree 
rm -rf kevoree-core/model/microframework
rm -rf kevoree-core/model/sparsehash
rm -rf kevoree-core/model/check_leak.sh 
rm -rf kevoree-core/model/clean_cmake_files.sh 
rm -rf kevoree-core/model/generation.log
rm build/*
rm -rf maven-resolver-cpp/

