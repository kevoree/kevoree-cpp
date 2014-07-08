cmake_minimum_required(VERSION 2.8)



SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
SET(CMAKE_MACOSX_RPATH 1)
SET(CMAKE_INSTALL_RPATH "@executable_path/../lib/")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

 
SET(ENABLELIBC "-stdlib=libc++")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENABLELIBC}")
  

  
execute_process(COMMAND install_name_tool -change @rpath/libkevoree-model-dynamic.dylib @executable_path/../lib/libkevoree-model-dynamic.dylib ${CMAKE_BUILD_TYPE}/bin/main)
  