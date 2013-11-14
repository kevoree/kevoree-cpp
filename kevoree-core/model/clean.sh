#!/bin/sh


find . -name "CMakeFiles" | xargs rm -rf
find . -name "Makefile" | xargs rm -rf
find . -name "cmake_install.cmake_modules" | xargs rm -rf
find . -name "cmake_install.cmake" | xargs rm -rf
find . -name "CMakeCache.txt" | xargs rm -rf                                                
rm -rf kevoree 
rm -rf microframework
rm -rf sparsehash
rm -rf check_leak.sh 
rm -rf clean_cmake_files.sh 
rm -rf generation.log
