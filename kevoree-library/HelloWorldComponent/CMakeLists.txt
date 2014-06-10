cmake_minimum_required(VERSION 2.8)
project(helloworld-component)


include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)

include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)

include_directories(${KEVOREEROOT}/${SRC_KEVOREE_HTTPCLIENT}/src)
file(GLOB_RECURSE helloworld_files src/*)
ADD_LIBRARY(helloworld_component  SHARED    ${helloworld_files})

