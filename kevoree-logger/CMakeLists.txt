cmake_minimum_required(VERSION 2.8)
project(kevoree-logger)



include_directories(api/)
file(GLOB_RECURSE files src/*.cpp)


ADD_LIBRARY(kevoree-logger SHARED    ${files}  ) #${HEADERS_MOC}


install(DIRECTORY ${CMAKE_SOURCE_DIR}/kevoree-logger DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/include FILES_MATCHING PATTERN "*.h")
install(TARGETS kevoree-logger   DESTINATION  ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
