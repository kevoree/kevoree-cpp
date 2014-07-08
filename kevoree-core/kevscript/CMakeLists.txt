cmake_minimum_required(VERSION 2.8)
project(kevscript)


set(KEVOREEROOT ../../)
set(SRC_KEVOREE_CORE  ${KEVOREEROOT}/kevoree-core)
set(SRC_MICROFRAMEWORK ${SRC_KEVOREE_CORE}/model/)



include_directories(${KEVOREEROOT})
include_directories(${SRC_MICROFRAMEWORK})

include_directories(.)
include_directories(src/)
include_directories(waxeye/include)

file(GLOB_RECURSE kevscript_files src/*)
file(GLOB_RECURSE waxeye_files waxeye/*)


ADD_LIBRARY(kevscript   STATIC   ${kevscript_files})

ADD_LIBRARY(waxeye   STATIC   ${waxeye_files})


add_executable(
        kevscript-parser
        ${kevscript_files}
)
TARGET_LINK_LIBRARIES(kevscript-parser waxeye )