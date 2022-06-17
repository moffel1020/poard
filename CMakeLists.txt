cmake_minimum_required(VERSION 3.0.0)
project(ogl VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(ogl src/main.cpp src/Input.cpp src/shader.cpp src/Window.cpp src/buffers.cpp dependencies/glad.c)
include_directories(dependencies/include/)
include_directories(include/)
link_directories(dependencies/lib/)
target_link_libraries(ogl ${PROJECT_SOURCE_DIR}/dependencies/lib/libglfw3.a)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)