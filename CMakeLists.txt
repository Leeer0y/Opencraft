cmake_minimum_required(VERSION 3.10)

project(Tutorial)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp gl.c)
target_include_directories(${PROJECT_NAME} PUBLIC external/includes)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)
