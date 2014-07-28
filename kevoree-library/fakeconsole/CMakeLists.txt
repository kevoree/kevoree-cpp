cmake_minimum_required(VERSION 2.8)
project(fakeconsole-component)

include_directories(${KEVOREEROOT}/)
include_directories(${SRC_MICROFRAMEWORK}/)
include_directories(../../maven-resolver-cpp/src/)
include_directories(${BOOST_ROOT}/include)
link_directories(${BOOST_ROOT}/lib)

#FIND_PACKAGE(Qt4 REQUIRED)
#INCLUDE(${QT_USE_FILE})
#ADD_DEFINITIONS(${QT_DEFINITIONS})

file(GLOB_RECURSE files src/*.cpp)
#file(GLOB_RECURSE HEADERS src/*.h)
#qt4_wrap_cpp(HEADERS_MOC ${HEADERS})

#message(${HEADERS_MOC} )
ADD_LIBRARY(fakeconsole_component  SHARED    ${files}  ) #${HEADERS_MOC}
TARGET_LINK_LIBRARIES(fakeconsole_component  kevoree-model-dynamic)
TARGET_LINK_LIBRARIES(fakeconsole_component boost_system-mt)
TARGET_LINK_LIBRARIES(fakeconsole_component boost_thread-mt)
#TARGET_LINK_LIBRARIES(fakeconsole_component ${QT_LIBRARIES})

