cmake_minimum_required(VERSION 2.8)
project(httpclient)


include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)
message(${BOOST_ROOT})


include_directories(src)
file(GLOB_RECURSE files src/*)
ADD_LIBRARY(httpclient  SHARED  ${files})
TARGET_LINK_LIBRARIES(httpclient  boost_system-mt)

