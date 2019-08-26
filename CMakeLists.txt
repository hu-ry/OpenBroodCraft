cmake_minimum_required(VERSION 3.12)
project(OpenBroodCraft)

set(CMAKE_CXX_STANDARD 14)


set(SOURCE_FILES src/main.cpp src/shader_vf.h src/main.h src/libs/glad.c src/MeshObject.h src/libs/stb_image.h
        src/libs/stb_imageloader.cpp src/TextureObject.h src/globalVar.cpp src/globalVar.h src/camera.h)

add_executable(OpenBroodCraft ${SOURCE_FILES})

target_link_libraries(OpenBroodCraft -lglfw3 -lgdi32 -lopengl32)