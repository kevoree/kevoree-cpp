cmake_minimum_required(VERSION 2.8)
project(kevoree-cpp)



#SET(CMAKE_C_COMPILER arm-linux-gnueabi-gcc) 
#SET(CMAKE_CXX_COMPILER arm-linux-gnueabi-g++-4.6)

set(CMAKE_CXX_FLAGS "-O3 ${CMAKE_CXX_FLAGS}")




# END -- KMF-MICROFRAMEWORK


#COMPILE MAIN
add_executable(
        main
        main.cpp
)


TARGET_LINK_LIBRARIES(main ${CMAKE_CURRENT_BINARY_DIR}/libkevoree-core-impl.a)
TARGET_LINK_LIBRARIES(main ${CMAKE_CURRENT_BINARY_DIR}/libkevoree-core-model.a)

TARGET_LINK_LIBRARIES(main rt)
TARGET_LINK_LIBRARIES(main dl)
