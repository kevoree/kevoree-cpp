cmake_minimum_required(VERSION 2.8)
project(kevoree-platform)




include_directories(.)
include_directories(../)
include_directories(../kevoree-core/model/)
include_directories(../maven-resolver-cpp/src/api)


file(GLOB_RECURSE kevoree-platform_files KevoreeBootStrap/*)


#COMPILE MAIN
add_executable(
        main
        standalone/main.cpp
        ${kevoree-platform_files}
)



IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
TARGET_LINK_LIBRARIES(main  -Wl,-all_load ${LIBRARY_OUTPUT_PATH}/libkevoree-core-model.a)
TARGET_LINK_LIBRARIES(main  ${LIBRARY_OUTPUT_PATH}/libkevoree-core-impl.a )
TARGET_LINK_LIBRARIES(main  -Wl,-all_load ${LIBRARY_OUTPUT_PATH}/libmaven-resolver-cpp.a)
TARGET_LINK_LIBRARIES(main 	${LIBRARY_OUTPUT_PATH}/libkevoree-tools.a)
TARGET_LINK_LIBRARIES(main dl)

ENDIF()

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
TARGET_LINK_LIBRARIES(main  -Wl,-whole-archive ${LIBRARY_OUTPUT_PATH}/libkevoree-core-model.a -Wl,-no-whole-archive)
TARGET_LINK_LIBRARIES(main  ${LIBRARY_OUTPUT_PATH}/libkevoree-core-impl.a )
TARGET_LINK_LIBRARIES(main  -Wl,-whole-archive ${LIBRARY_OUTPUT_PATH}/libmaven-resolver-cpp.a -Wl,-no-whole-archive)
TARGET_LINK_LIBRARIES(main 	${LIBRARY_OUTPUT_PATH}/libkevoree-tools.a)
TARGET_LINK_LIBRARIES(main rt)
TARGET_LINK_LIBRARIES(main dl)
ENDIF()









