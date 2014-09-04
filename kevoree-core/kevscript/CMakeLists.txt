cmake_minimum_required(VERSION 2.8)
project(kevscript)


set(KEVOREEROOT ../../)
set(SRC_KEVOREE_CORE  ${KEVOREEROOT}/kevoree-core)
set(SRC_MICROFRAMEWORK ${SRC_KEVOREE_CORE}/model/)


include_directories(${KEVOREEROOT}/maven-resolver-cpp/src)
include_directories(${KEVOREEROOT})
include_directories(${SRC_MICROFRAMEWORK})

include_directories(.)
include_directories(src/)
include_directories(src/api)
include_directories(waxeye/include)

include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)


file(GLOB_RECURSE kevscript_files src/*)
file(GLOB_RECURSE waxeye_files waxeye/*.c)


ADD_LIBRARY(waxeye   STATIC   ${waxeye_files})


ADD_LIBRARY(kevscript   STATIC   ${kevscript_files})
TARGET_LINK_LIBRARIES(kevscript  boost_thread-mt) # FIX ME REMOVE 
TARGET_LINK_LIBRARIES(kevscript  pthread)
TARGET_LINK_LIBRARIES(kevscript  maven-resolver-cpp )
TARGET_LINK_LIBRARIES(kevscript  waxeye )


install(TARGETS kevscript   DESTINATION  ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
install(TARGETS waxeye   DESTINATION  ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)

#add_executable(
#        kevscript-parser
#        ${kevscript_files}
#)
#TARGET_LINK_LIBRARIES(kevscript-parser waxeye )