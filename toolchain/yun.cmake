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

SET(CMAKE_C_COMPILER mips-openwrt-linux-gcc) 
SET(CMAKE_CXX_COMPILER mips-openwrt-linux-g++)
set(arch_hint "Yun")

