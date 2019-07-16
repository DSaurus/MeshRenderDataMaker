cmake_minimum_required(VERSION 3.14)
project(MeshRenderDataMaker)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(${OPENGL_INCLUDE_DIR})

add_subdirectory(glfw)
add_subdirectory(src)