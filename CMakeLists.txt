cmake_minimum_required(VERSION 3.3.0)
project(opengl_workshop VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

include_directories(includes)

add_executable(opengl_workshop
    #src/00_getting_started/01_hello_triangle/01_hello_triangle.cpp
    #src/00_getting_started/02_textures/02_textures.cpp
    #src/00_getting_started/03_transformations/03_transformations.cpp
    #src/00_getting_started/04_coordinate_systems/04_coordinate_systems.cpp
    src/00_getting_started/05_camera/05_camera.cpp
    src/glad.c
    src/stb_image.cpp
)

target_link_libraries(opengl_workshop
    glfw
    OpenGL::GL
    ${CMAKE_DL_LIBS}
)
