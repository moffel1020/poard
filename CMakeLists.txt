cmake_minimum_required(VERSION 3.0.0)
project(poard VERSION 0.1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(UNIX)
    set(CMAKE_CXX_FLAGS "-lX11")
endif(UNIX)

aux_source_directory(src SRC_DIR)
add_executable(poard ${SRC_DIR} dependencies/src/glad.c)
include_directories(dependencies/include/)
include_directories(src/)

if(UNIX)
    target_link_libraries(poard ${PROJECT_SOURCE_DIR}/dependencies/lib/linux/libglfw3.a)
elseif(WIN32)
    target_link_libraries(poard ${PROJECT_SOURCE_DIR}/dependencies/lib/windows/libglfw3.a)
endif()
