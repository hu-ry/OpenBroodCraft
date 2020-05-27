cmake_minimum_required(VERSION 3.12)
project(OpenBroodCraft)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

set(SOURCE_FILES src/main.cpp include/libs/glad.c include/libs/stb_imageloader.cpp src/globalvar.cpp src/game/unit.cpp
        src/input/input.cpp src/game/gameengine.cpp src/input/command.cpp src/game/player.cpp src/game/texentity.cpp
        src/game/map/gamemap.cpp src/game/engine/meshfactory.cpp src/input/inputAgent.cpp src/game/order.cpp)


add_executable(OpenBroodCraft ${SOURCE_FILES})

target_link_libraries(OpenBroodCraft -lglfw3 -lgdi32 -lopengl32)