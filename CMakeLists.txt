cmake_minimum_required(VERSION 3.20)

project(
    BlackHoleSim
    VERSION 0.1
    LANGUAGES C CXX
)

# C++ compiler

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GLFW
add_library(glfw STATIC IMPORTED)

set_target_properties(
    glfw PROPERTIES
    IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/libs/glfw/lib/libglfw3.a
)

# Glad
add_library(
    glad
    ${CMAKE_SOURCE_DIR}/libs/glad/src/glad.c    
)

target_include_directories(
    glad
    PUBLIC
    ${CMAKE_SOURCE_DIR}/libs/glad/include
)

# Collect Source files
file(
    GLOB_RECURSE PROJECT_SOURCES
    src/*.cpp
    SOGL/*.cpp
)

# Executable
add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

# Include directories
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE

    src
    SOGL

    libs/glad/include
    libs/glfw/include
    libs/glm
)

# Link libraries
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    glfw
    glad
)

# Windows OpenGL
if(WIN32)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    opengl32
)

endif()