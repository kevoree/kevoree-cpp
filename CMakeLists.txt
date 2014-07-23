cmake_minimum_required(VERSION 2.8)
project(kevoree-cpp)
set(KEVOREE_CPP_VERSION_MAJOR 0)
set(KEVOREE_CPP_VERSION_MINOR 1)
set(KEVOREE_CPP_VERSION ${KEVOREE_CPP_VERSION_MAJOR}.${KEVOREE_CPP_VERSION_MINOR})

if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Debug)
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}   -std=c++11 -pedantic")
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/build)
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/build)


add_definitions(-DENABLE_LOGGER  )

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 

# the RPATH to be used when installing
SET(CMAKE_INSTALL_RPATH "")


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

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS}")
else()
set(CMAKE_CXX_FLAGS "-g ${CMAKE_CXX_FLAGS}")
endif()

IF(NOT EXISTS "${SRC_MAVEN_RESOLVER}" )
 execute_process(COMMAND git clone "https://github.com/Jean-Emile/maven-resolver-cpp.git")
ELSE()
 execute_process(COMMAND cd maven-resolver-cpp & git pull)
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
add_subdirectory (${SRC_KEVOREE_PLATFORM}/)


if(NOT ANDROID)
add_subdirectory (${SRC_KEVOREE_TESTS}/)
ENDIF()

ADD_CUSTOM_TARGET(upload COMMAND  mvn deploy)
ADD_CUSTOM_TARGET(run  COMMAND  ${CMAKE_BUILD_TYPE}/bin/runtime)



#************************************** INSTALL ****************************************************
if(EXISTS ${BOOST})
install(DIRECTORY ${BOOST_ROOT}/include/boost DESTINATION  ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/include FILES_MATCHING PATTERN "*.hpp")
install(DIRECTORY ${BOOST_ROOT}/lib/ DESTINATION  ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib FILES_MATCHING PATTERN "*.a")
endif()
