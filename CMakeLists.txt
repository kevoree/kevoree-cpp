cmake_minimum_required(VERSION 2.8)
project(kevoree-cpp)


set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/build)
add_definitions(-DENABLE_LOGGER)


set(SRC_KEVOREE_CORE 						kevoree-core)
set(SRC_KEVOREE_TOOLS 						kevoree-tools)
set(SRC_KEVOREE_PLATFORM 					kevoree-platform)
set(SRC_KEVOREE_LIBRARY 					kevoree-library)
set(SRC_KEVOREE_MODEL 						${SRC_KEVOREE_CORE}/model)
set(SRC_KEVOREE_ADAPTATION_MODEL_KEVOREE 	${SRC_KEVOREE_CORE}/model/kevoree.adaptation/)


IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message("CMAKE HAS DETECTED A Linux SYSTEM")
   SET(ENABLE_CXX11 "-std=c++11")
   EXECUTE_PROCESS(COMMAND "${CMAKE_CXX_COMPILER} -dumpversion" OUTPUT_VARIABLE GCC_VERSION)
   if (GCC_VERSION VERSION_LESS 4.7)
      SET(ENABLE_CXX11 "-std=c++0x")
   endif()
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENABLE_CXX11}")
endif()

#-Wreturn-type
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message("CMAKE HAS DETECTED A OSX SYSTEM")

    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -stdlib=libc++")

    IF(CMAKE_BUILD_TYPE MATCHES Release)
        SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../bin/OSX/Release)
    ENDIF(CMAKE_BUILD_TYPE MATCHES Release)
    IF(CMAKE_BUILD_TYPE MATCHES Debug)
        SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../bin/OSX/Debug)
    ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

add_subdirectory (maven-resolver-cpp/)
add_subdirectory (${SRC_KEVOREE_CORE}/)
add_subdirectory (${SRC_KEVOREE_TOOLS}/)
add_subdirectory (${SRC_KEVOREE_PLATFORM}/)
#add_subdirectory (${SRC_KEVOREE_LIBRARY}/)

