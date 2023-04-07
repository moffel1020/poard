cmake_minimum_required(VERSION 3.0.0)
project(poard VERSION 0.1.0)

option(GLFW_BUILD_DOCS "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_BUILD_EXAMPLES "" OFF)
option(GLFW_INSTALL "" OFF)

option(ASSIMP_INSTALL "" OFF)
option(ASSIMP_BUILD_TESTS "" OFF)
option(BUILD_SHARED_LIBS "" OFF)
option(ASSIMP_WARNINGS_AS_ERRORS "" OFF)
option(ASSIMP_BUILD_ASSIMP_VIEW "" OFF)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "-static ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "-std=c++20 ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

if(UNIX)
    set(CMAKE_CXX_FLAGS "-lX11 ${CMAKE_CXX_FLAGS}")
endif(UNIX)

add_subdirectory(dependencies/assimp/)
add_subdirectory(dependencies/glfw/)
aux_source_directory(src SRC_DIR)
aux_source_directory(src/poard/core CORE_DIR)
aux_source_directory(src/poard/renderer RENDERER_DIR)
aux_source_directory(dependencies/imgui IMGUI_DIR)
aux_source_directory(dependencies/implot IMPLOT_DIR)
add_executable(poard ${CORE_DIR} ${RENDERER_DIR} ${SRC_DIR} ${IMGUI_DIR} ${IMPLOT_DIR} dependencies/glad/glad.c)
include_directories(dependencies/ src/ src/poard/core src/poard/renderer src/poard)

target_link_libraries(poard glfw assimp)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/res
                ${CMAKE_CURRENT_BINARY_DIR}/res)
