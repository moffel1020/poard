cmake_minimum_required(VERSION 3.0.0)
project(poard VERSION 0.1.0)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(UNIX)
    set(CMAKE_CXX_FLAGS "-lX11")
endif(UNIX)

add_executable(poard src/main.cpp src/input.cpp src/shader.cpp src/window.cpp src/buffers.cpp src/texture.cpp src/camera.cpp dependencies/glad.c)
include_directories(dependencies/include/)
include_directories(include/)

if(UNIX)
    target_link_libraries(poard ${PROJECT_SOURCE_DIR}/dependencies/linux/libglfw3.a)
endif(UNIX)

if(WIN32)
    target_link_libraries(poard ${PROJECT_SOURCE_DIR}/dependencies/windows/libglfw3.a)
endif(WIN32)
