cmake_minimum_required(VERSION 3.0.0)
project(poard VERSION 0.1.0)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(UNIX)
    set(CMAKE_CXX_FLAGS "-lX11")
endif(UNIX)

add_subdirectory(dependencies/glfw/)
aux_source_directory(src SRC_DIR)
aux_source_directory(src/poard/core CORE_DIR)
aux_source_directory(src/poard/renderer RENDERER_DIR)
aux_source_directory(dependencies/imgui IMGUI_DIR)
add_executable(poard ${CORE_DIR} ${RENDERER_DIR} ${SRC_DIR} ${IMGUI_DIR} dependencies/glad/glad.c)
include_directories(dependencies/ src/ src/poard/core src/poard/renderer src/poard)

target_link_libraries(poard glfw)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/res
                ${CMAKE_CURRENT_BINARY_DIR}/res)