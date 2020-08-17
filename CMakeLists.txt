cmake_minimum_required(VERSION 3.18.1)
project(Undefined)

add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(hello src/hello.cpp)
target_link_libraries(hello ${CONAN_LIBS})