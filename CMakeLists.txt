cmake_minimum_required(VERSION 3.22.1)
project(opencraft
        VERSION 0.0.1
        DESCRIPTION "An open source voxel based game inspired off Minecraft meant to bring back the beautiful beta and simplistic feeling of it"
        LANGUAGES CXX)



file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.h)

add_executable(${PROJECT_NAME} ${SRC_FILES})

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
        PUBLIC external/glfw/include
        PUBLIC external/includes
        )

target_link_directories(${PROJECT_NAME} PRIVATE external/glfw/src)
target_link_libraries(${PROJECT_NAME} glfw)

