cmake_minimum_required(VERSION 3.0.0)
project(poard VERSION 0.1.0)


message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(poard src/main.cpp src/Input.cpp src/shader.cpp src/Window.cpp src/buffers.cpp src/texture.cpp src/camera.cpp dependencies/glad.c)
include_directories(dependencies/include/)
include_directories(include/)
target_link_libraries(poard ${PROJECT_SOURCE_DIR}/dependencies/lib/libglfw3.a)