cmake_minimum_required(VERSION 2.8)
#SET(CMAKE_C_COMPILER arm-bcm2708-linux-gnueabi-gcc) 
#SET(CMAKE_CXX_COMPILER arm-bcm2708-linux-gnueabi-g++)
#set(arch_hint "ARM")
project(kevoree-cpp)


set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/build)
add_definitions(-DENABLE_LOGGER)



IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message("CMAKE HAS DETECTED A Linux SYSTEM")
   SET(ENABLE_CXX11 "-std=c++11")
   EXECUTE_PROCESS(COMMAND "${CMAKE_CXX_COMPILER} -dumpversion" OUTPUT_VARIABLE GCC_VERSION)
   if (GCC_VERSION VERSION_LESS 4.7)
      SET(ENABLE_CXX11 "-std=c++0x")
   endif()
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENABLE_CXX11}")
endif()




#if("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
#    set(arch_hint "x64")
#  elseif("${CMAKE_GENERATOR}" MATCHES "ARM")
#    set(arch_hint "ARM")
#  elseif("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
#    set(arch_hint "x64")
#  elseif("$ENV{LIB}" MATCHES "(amd64|ia64)")
#    set(arch_hint "x64")
#  endif()

#if(NOT arch_hint)
#   set(arch_hint "x86")
# endif()

#SET(CMAKE_C_COMPILER arm-linux-gnueabi-gcc) 
#SET(CMAKE_CXX_COMPILER arm-linux-gnueabi-g++-4.6)




set(SRC_KEVOREE_CORE 						kevoree-core)
set(SRC_KEVOREE_TOOLS 						kevoree-tools)
set(SRC_KEVOREE_PLATFORM 					kevoree-platform)
set(SRC_KEVOREE_LIBRARY 					kevoree-library)
set(SRC_KEVOREE_MODEL 						${SRC_KEVOREE_CORE}/model)
set(SRC_KEVOREE_ADAPTATION_MODEL_KEVOREE 	${SRC_KEVOREE_CORE}/model/kevoree.adaptation/)

set(CMAKE_CXX_FLAGS "-g ${CMAKE_CXX_FLAGS}")


add_subdirectory (maven-resolver-cpp/)
add_subdirectory (${SRC_KEVOREE_CORE}/)
add_subdirectory (${SRC_KEVOREE_TOOLS}/)
add_subdirectory (${SRC_KEVOREE_PLATFORM}/)
add_subdirectory (${SRC_KEVOREE_LIBRARY}/)

