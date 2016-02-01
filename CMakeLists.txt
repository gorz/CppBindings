cmake_minimum_required(VERSION 2.8)
project(cppBindings)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DTIXML_USE_STL")

include_directories(.)

set(TINYXML_LIB_NAME tinyxml)
add_subdirectory(tinyxml)

set(BINDINGS_LIB_NAME bindings)
add_subdirectory(bindings)

set(SOURCE_FILES simpleTest.cpp)
add_executable(cppBindings ${SOURCE_FILES})
target_link_libraries(cppBindings ${TINYXML_LIB_NAME} ${BINDINGS_LIB_NAME})