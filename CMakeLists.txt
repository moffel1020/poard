cmake_minimum_required(VERSION 3.0.0)
project(poard VERSION 0.1.0)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(UNIX)
    set(CMAKE_CXX_FLAGS "-lX11")
endif(UNIX)

add_subdirectory(dependencies/glfw/)
aux_source_directory(src SRC_DIR)
add_executable(poard ${SRC_DIR} dependencies/glad/glad.c)
include_directories(dependencies/)
include_directories(src/)

target_link_libraries(poard glfw)