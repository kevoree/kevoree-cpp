cmake_minimum_required(VERSION 2.8)
project(cppnode-cppnodeType)



include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)
include_directories(../../maven-resolver-cpp/src)
include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)
#find_package(Boost REQUIRED  thread)



# BEGIN -- KEVOREE- CPPNode
file(GLOB_RECURSE cppnodetype_library_files src/*)
ADD_LIBRARY(kevoree-CPPNode  SHARED    ${cppnodetype_library_files} )
TARGET_LINK_LIBRARIES(kevoree-CPPNode  boost_thread)
TARGET_LINK_LIBRARIES(kevoree-CPPNode  boost_system)


IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
TARGET_LINK_LIBRARIES(kevoree-CPPNode   ${LIBRARY_OUTPUT_PATH}/libkevoree-model.dylib )
ENDIF()

if(ANDROID)
TARGET_LINK_LIBRARIES(kevoree-CPPNode    ${LIBRARY_OUTPUT_PATH}/libkevoree-model.so )
ENDIF()


#execute_process(COMMAND mvn deploy:deploy-file      -Durl=${repository}     -DgroupId=org.kevoree.library     -DartifactId=CPPNODE     -Dversion=1.0      -Dpackaging=json    -Dfile=target/lib.json -DrepositoryId=${repositoryId})
#execute_process(COMMAND mvn deploy:deploy-file      -Durl=${repository}     -DgroupId=org.kevoree.library     -DartifactId=CPPNODE     -Dversion=1.0      -Dpackaging=so     -Dfile=target/libkevoree-CPPNode.so -DrepositoryId=${repositoryId})



# END --  KEVOREE-CPPNode
