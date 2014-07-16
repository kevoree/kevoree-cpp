cmake_minimum_required(VERSION 2.8)
project(kevoree-library)

if(PRAGMA_PLUGIN MATCHES "TRUE")
set(plugin_pragma_path "${LIBRARY_OUTPUT_PATH}/libplugin-pragma.so")
set(CMAKE_CXX_FLAGS " -fplugin=${plugin_pragma_path}  ${CMAKE_CXX_FLAGS}")
ENDIF()

set(repository "http://maven.reacloud.com/repository/reacloud")
set(repositoryId "reacloud")

set(KEVOREEROOT ../../)
set(SRC_KEVOREE_CORE  ${KEVOREEROOT}/kevoree-core)
set(SRC_MICROFRAMEWORK ${SRC_KEVOREE_CORE}/model/)
include_directories(../maven-resolver-cpp/src/api)
include_directories(../kevoree-core/src/api)
#set(LIBRARY_OUTPUT_PATH target)

add_subdirectory (websocketgroup/)
add_subdirectory (helloworldcomponet/)
add_subdirectory (cppNode/)
add_subdirectory (fakeconsole/)
