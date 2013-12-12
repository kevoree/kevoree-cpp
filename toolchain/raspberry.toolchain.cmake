cmake_minimum_required(VERSION 2.8)

if( DEFINED CMAKE_CROSSCOMPILING )
 # subsequent toolchain loading is not really needed
 return()
endif()

if( CMAKE_TOOLCHAIN_FILE )
 # touch toolchain variable only to suppress "unused variable" warning
endif()

# this one is important
set( CMAKE_SYSTEM_NAME Linux )
# this one not so much
set( CMAKE_SYSTEM_VERSION 1 )

SET(CMAKE_C_COMPILER arm-bcm2708-linux-gnueabi-gcc) 
SET(CMAKE_CXX_COMPILER arm-bcm2708-linux-gnueabi-g++)
set(arch_hint "ARM")

