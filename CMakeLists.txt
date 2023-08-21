# If opengl doesnt work for some reason refer to https://marcelfischer.eu/blog/2019/sdl-opengl-cmake/

cmake_minimum_required(VERSION 3.22.1)
project(opencraft
        VERSION 0.0.1
        DESCRIPTION "An open source voxel based game inspired off Minecraft meant to bring back the beautiful beta and simplistic feeling of it"
        LANGUAGES CXX C)



file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.h) # Doesnt get c files

add_executable(${PROJECT_NAME} ${SRC_FILES} src/glad.c)

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
        PUBLIC external/glfw/include
        PUBLIC external/includes
)

#message(STATUS "<<${OPENGL_INCLUDE_DIRS}>>")
# This will print <<>> because OPENGL_INCLUDE_DIRS is empty.

target_link_directories(${PROJECT_NAME} PRIVATE external/glfw/src ${o})
target_link_libraries(${PROJECT_NAME} glfw)

