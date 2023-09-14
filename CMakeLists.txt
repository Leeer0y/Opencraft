# If opengl doesnt work for some reason refer to https://marcelfischer.eu/blog/2019/sdl-opengl-cmake/

cmake_minimum_required(VERSION 3.22.1)
project(opencraft
        VERSION 0.0.1
        DESCRIPTION "An open source voxel based game inspired off Minecraft meant to bring back the beautiful beta and simplistic feeling of it"
        LANGUAGES CXX)



file(GLOB_RECURSE SHADER_FILES resources/*.vert resources/*.frag)
file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.h) # Doesnt get c files

add_executable(${PROJECT_NAME} ${SHADER_FILES} ${SRC_FILES} src/glad.c)

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
        PUBLIC external/glfw/include
        PUBLIC external/includes
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/") # adds a macro so RESOURCES_PATH points to the resources folder
#target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC RESOURCES_PATH="./resources/") # for compiling a relase version, move resources into final directory

#message(STATUS "<<${OPENGL_INCLUDE_DIRS}>>")
# This will print <<>> because OPENGL_INCLUDE_DIRS is empty.

target_link_directories(${PROJECT_NAME} PRIVATE external/glfw/src ${o})
target_link_libraries(${PROJECT_NAME} glfw)


if(MSVC) #using the visual studio compiler
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME}) # Set the project as the startup project by defualt instead of ALL BUILD

        source_group("Resources") # Directory for resources
        source_group("Resources/Shaders" FILES ${SHADER_FILES}) # Subdir for shaders
endif()
