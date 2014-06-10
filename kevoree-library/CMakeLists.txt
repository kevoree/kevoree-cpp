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

#set(LIBRARY_OUTPUT_PATH target)
add_subdirectory (WebSocketGroup/)
add_subdirectory (HelloWorldComponent/)
add_subdirectory (CPPNodeType/)



# deploy on the repository using maven
ADD_CUSTOM_TARGET(upload
COMMAND mvn deploy:deploy-file      -Durl=${repository}     -DgroupId=org.kevoree.library     -DartifactId=HelloWorldComponent   	   -Dversion=1.0.0-SNAPSHOT      -Dpackaging=so     -Dfile=${LIBRARY_OUTPUT_PATH}/libhelloworld_component.so -DrepositoryId=${repositoryId}
COMMAND mvn deploy:deploy-file      -Durl=${repository}     -DgroupId=org.kevoree.library     -DartifactId=kevoree-group-websocket     -Dversion=1.0.0-SNAPSHOT      -Dpackaging=so     -Dfile=${LIBRARY_OUTPUT_PATH}/libwebsocketgroup.so -DrepositoryId=${repositoryId}
COMMAND mvn deploy:deploy-file      -Durl=${repository}     -DgroupId=org.kevoree.library     -DartifactId=CPPNodeType                 -Dversion=1.0.0-SNAPSHOT      -Dpackaging=so     -Dfile=${LIBRARY_OUTPUT_PATH}/libkevoree-CPPNode.so -DrepositoryId=${repositoryId}
)