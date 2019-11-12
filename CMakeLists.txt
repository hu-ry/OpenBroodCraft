cmake_minimum_required(VERSION 3.12)
project(OpenBroodCraft)

set(CMAKE_CXX_STANDARD 14)


set(SOURCE_FILES src/main.cpp src/game/engine/shader_vf.h src/main.h src/libs/glad.c src/game/engine/meshobject.h src/libs/stb_image.h
        src/libs/stb_imageloader.cpp src/game/engine/textureobject.h src/globalvar.cpp src/globalvar.h src/game/engine/camera.h src/game/unit.cpp src/game/unit.h src/input/input.cpp src/input/input.h src/headerinclude.h src/game/gameengine.cpp src/game/gameengine.hpp src/game/command.cpp src/game/command.h src/game/player.cpp src/game/player.h src/game/texentity.cpp src/game/texentity.h src/game/kernelstore.h src/game/map/gamemap.cpp src/game/map/gamemap.h src/game/map/map_tile.h src/game/engine/meshfactory.cpp src/game/engine/meshfactory.h)

add_executable(OpenBroodCraft ${SOURCE_FILES})

target_link_libraries(OpenBroodCraft -lglfw3 -lgdi32 -lopengl32)