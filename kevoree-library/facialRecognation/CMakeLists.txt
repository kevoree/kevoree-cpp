cmake_minimum_required(VERSION 2.8)
project(facialrecognation-component)
find_package( OpenCV REQUIRED )

include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)
include_directories(../../maven-resolver-cpp/src/)
include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)


file(GLOB_RECURSE files src/*.cpp)


ADD_LIBRARY(facialrecognation_component  SHARED    ${files}  ) #${HEADERS_MOC}
target_link_libraries( facialrecognation_component ${OpenCV_LIBS} )
TARGET_LINK_LIBRARIES(facialrecognation_component  kevoree-model-dynamic)
TARGET_LINK_LIBRARIES(facialrecognation_component boost_system-mt)
TARGET_LINK_LIBRARIES(facialrecognation_component boost_thread-mt)

