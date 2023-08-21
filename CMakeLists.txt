cmake_minimum_required(VERSION 3.22.1)
project(opencraft
        VERSION 0.0.1
        DESCRIPTION "An open source voxel based game inspired off Minecraft meant to bring back the beautiful beta and simplistic feeling of it"
        LANGUAGES CXX)



add_executable(${PROJECT_NAME} src/main.cpp src/glad.c)

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
        PUBLIC external/glfw/include
        PUBLIC external/includes
        )

target_link_directories(${PROJECT_NAME} PRIVATE external/glfw/src)
target_link_libraries(${PROJECT_NAME} glfw)
