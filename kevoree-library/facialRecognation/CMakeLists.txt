cmake_minimum_required(VERSION 2.8)
project(facialrecognation)
set(KEVOREEROOT /Users/Aymeric/Documents/dev_Kevoree/kevoree-cpp/Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}   -std=c++11 -pedantic")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

   SET(ENABLE_CXX11 "-std=c++11")
   EXECUTE_PROCESS(COMMAND "${CMAKE_CXX_COMPILER} -dumpversion" OUTPUT_VARIABLE GCC_VERSION)
   if (GCC_VERSION VERSION_LESS 4.7)
      SET(ENABLE_CXX11 "-std=c++0x")
   endif()
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENABLE_CXX11}")
endif()

include_directories(${KEVOREEROOT}/include/kevoree-core/)
include_directories(${KEVOREEROOT}/include/kevoree-core/model/)
include_directories(${KEVOREEROOT}/include/)

link_directories(${KEVOREEROOT}/lib/)

file(GLOB_RECURSE facialrecognation_intern_files src/*.cpp)
ADD_LIBRARY(facialrecognation SHARED ${facialrecognation_intern_files} )

TARGET_LINK_LIBRARIES(facialrecognation kevoree-model-dynamic)
TARGET_LINK_LIBRARIES(facialrecognation boost_system-mt)
TARGET_LINK_LIBRARIES(facialrecognation boost_thread-mt)

