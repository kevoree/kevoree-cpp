cmake_minimum_required(VERSION 2.8)
project(kevoree-cpp)
set(KEVOREE_CPP_VERSION_MAJOR 0)
set(KEVOREE_CPP_VERSION_MINOR 1)
set(KEVOREE_CPP_VERSION ${KEVOREE_CPP_VERSION_MAJOR}.${KEVOREE_CPP_VERSION_MINOR})


#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -stdlib=libstdc++ -Wall -pedantic")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -stdlib=libstdc++  -Wall -pedantic")
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/build)

set(PRAGMA_PLUGIN "FALSE")
add_definitions(-DENABLE_LOGGER)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/")

include(add_boost) 

message(boost_ ${CMAKE_CURRENT_SOURCE_DIR}/Third_Parties/boost_${BoostVersion})
set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/Third_Parties/boost_${BoostVersion})
   

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

   SET(ENABLE_CXX11 "-std=c++11")
   EXECUTE_PROCESS(COMMAND "${CMAKE_CXX_COMPILER} -dumpversion" OUTPUT_VARIABLE GCC_VERSION)
   if (GCC_VERSION VERSION_LESS 4.7)
      SET(ENABLE_CXX11 "-std=c++0x")
   endif()
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENABLE_CXX11}")
endif()

IF(APPLE)
 
    SET(ENABLELIBC "-stdlib=libc++")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENABLELIBC}")
  
endif()


message("Current OS	         : ${CMAKE_SYSTEM_NAME}")
message("Current Architecture: ${CMAKE_GENERATOR}")
message("Target  Architecture: ${arch_hint}")
message("Compiler            : ${CMAKE_CXX_COMPILER}")

message("${ENABLELIBC}")


set(SRC_KEVOREE_CORE 						kevoree-core)
set(SRC_KEVOREE_TOOLS 						kevoree-tools)
set(SRC_KEVOREE_PLATFORM 					kevoree-platform)
set(SRC_KEVOREE_LIBRARY 					kevoree-library)
set(SRC_KEVOREE_CXX_PLUGIN 					${SRC_KEVOREE_TOOLS}/PluginPragma)
set(SRC_KEVOREE_HTTPCLIENT					${SRC_KEVOREE_TOOLS}/HttpClient)
set(SRC_KEVOREE_MODEL 						${SRC_KEVOREE_CORE}/model/kevoree)
set(SRC_KEVOREE_TESTS 						tests)
set(SRC_MAVEN_RESOLVER maven-resolver-cpp)
set(URL_MODEL_GENERATOR "https://github.com/Jean-Emile/boost-extra/raw/master/org.kevoree.modeling.cpp.generator-1.1-20140321.171353-2.jar")

set(CMAKE_CXX_FLAGS "-g ${CMAKE_CXX_FLAGS}")

IF(NOT EXISTS "${SRC_MAVEN_RESOLVER}" )
 execute_process(COMMAND git clone "https://github.com/Jean-Emile/maven-resolver-cpp.git")
ENDIF()

IF(NOT EXISTS "${SRC_KEVOREE_MODEL}")
# message("Downloading model generator")
 #execute_process(COMMAND curl -OL ${URL_MODEL_GENERATOR} )
 message("Generate KEVOREE MODEL")
 execute_process(COMMAND java -jar kevoree-extra/org.kevoree.modeling.cpp.generator-1.3.1.jar -i kevoree-core/model/metamodel/kevoree.ecore -t kevoree-core/model)
ENDIF()


add_subdirectory (${SRC_MAVEN_RESOLVER}/)
add_subdirectory (${SRC_KEVOREE_CORE}/)
add_subdirectory (${SRC_KEVOREE_LIBRARY}/)
add_subdirectory (${SRC_KEVOREE_TOOLS}/)


if(PRAGMA_PLUGIN MATCHES "TRUE")
message("Compile Pragma plugin")
add_subdirectory (${SRC_KEVOREE_CXX_PLUGIN}/)
ENDIF()
add_subdirectory (${SRC_KEVOREE_HTTPCLIENT}/)


if(NOT ANDROID)
add_subdirectory (${SRC_KEVOREE_TESTS}/)
ENDIF()


