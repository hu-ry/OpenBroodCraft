cmake_minimum_required(VERSION 3.14)
project(OpenBroodCraft)

set(CMAKE_CXX_STANDARD 14)


set(SOURCE_FILES main.cpp shader_vf.h main.h glad.c spacesystem.h VertexArrayObject.h stb_image.h
        stb_imageloader.cpp TextureObject.cpp TextureObject.h)

add_executable(OpenBroodCraft ${SOURCE_FILES})

target_link_libraries(OpenBroodCraft -lglfw3 -lgdi32 -lopengl32)