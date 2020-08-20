cmake_minimum_required(VERSION 3.18.1)
project(Undefined)

add_definitions("-std=c++20")


file(GLOB SOURCES src/*.cpp 3rd-party/imgui/*.cpp)

add_executable(index ${SOURCES} include/AbstractWindow.h src/AbstractWindow.cpp
        include/GLFWWindow.h src/GLFWWindow.cpp)



if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(USE_FLAGS "-s USE_GLFW=3 -s FULL_ES3=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
    include_directories(include ${OPENGL_INCLUDE_DIRS} glfw ${GLEW_INCLUDE_DIRS} 3rd-party/spdlog/include 3rd-party/imgui)
    target_link_libraries(index ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES})
    link_directories(3rd-party/spdlog/libspdlogd.a)
else()
    find_package(GLEW REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(glfw3 3.3 REQUIRED)
    find_package(spdlog REQUIRED)
    include_directories(include ${OPENGL_INCLUDE_DIRS} glfw ${GLEW_INCLUDE_DIRS} ${SPDLOG_INCLUDE_DIRS} 3rd-party/imgui)
    target_link_libraries(index ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES} spdlog::spdlog)
endif()




