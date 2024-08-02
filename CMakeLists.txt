cmake_minimum_required(VERSION 3.10)

project(
  opencraft
  VERSION 0.0.1 
  DESCRIPTION "An open source voxel game based off Minecraft"
  LANGUAGES CXX C)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.c src/*.h)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC external/includes)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC SHADERS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/shaders/")

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)
