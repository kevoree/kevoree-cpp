cmake_minimum_required(VERSION 2.8)
project(kevoree-library)


set(plugin_pragma_path "${LIBRARY_OUTPUT_PATH}/libplugin-pragma.so")
set(CMAKE_CXX_FLAGS " -fplugin=${plugin_pragma_path} ${CMAKE_CXX_FLAGS}")
set(KEVOREEROOT ../../)
set(SRC_KEVOREE_CORE  ${KEVOREEROOT}/kevoree-core)
set(SRC_MICROFRAMEWORK ${SRC_KEVOREE_CORE}/model/)
include_directories(../maven-resolver-cpp/src/api)


add_subdirectory (WebSocketGroup/)
add_subdirectory (HelloWorldComponent/)
add_subdirectory (CPPNodeType/)
add_subdirectory (Apache2Wrapper/)
