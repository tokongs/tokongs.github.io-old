cmake_minimum_required(VERSION 3.18.1)
project(Undefined)

add_definitions("-std=c++11")


file(GLOB SOURCES src/*.cpp)

add_executable(hello ${SOURCES})



if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(USE_FLAGS "-s USE_GLFW=3 -s FULL_ES3=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
else()
    find_package(GLEW REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(glfw3 3.3 REQUIRED)
endif()




include_directories(include ${OPENGL_INCLUDE_DIRS} glfw ${GLEW_INCLUDE_DIRS})
target_link_libraries(hello ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES})