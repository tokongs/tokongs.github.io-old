cmake_minimum_required(VERSION 3.18.1)
project(Index)

add_definitions("-std=c++20")


file(GLOB_RECURSE SOURCES src/*.cpp 3rd-party/imgui/*.cpp)

add_executable(index ${SOURCES})



if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(USE_FLAGS "-s USE_GLFW=3 -s FULL_ES3=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
    include_directories(include ${OPENGL_INCLUDE_DIRS} glfw ${GLEW_INCLUDE_DIRS} 3rd-party/spdlog/include 3rd-party/imgui 3rd-party/glm)
    target_link_libraries(index ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES})
    link_directories(3rd-party/spdlog/libspdlogd.a 3rd-party/glm/libglm_static.a)
else()
    find_package(GLEW REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(glfw3 3.3 REQUIRED)
    find_package(spdlog REQUIRED)
    find_package(glm REQUIRED)
    include_directories(include ${OPENGL_INCLUDE_DIRS} glfw ${GLEW_INCLUDE_DIRS} ${SPDLOG_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} 3rd-party/imgui)
    target_link_libraries(index ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES} ${GLM_LIBRARIES} spdlog::spdlog)
endif()




