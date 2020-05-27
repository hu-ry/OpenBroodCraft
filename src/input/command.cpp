//
// Created by RH on 20/09/2019.
//
#include <cstdint>
#include "input/command.h"

#include "game/engine/camera.h"
#include "game/gameengine.hpp"
#include <GLFW/glfw3.h>


void CMD_MoveCamera::execute() {
    static_cast<GameEngine*>(_Game)->moveCamera((Camera_Movement)_Direction);
}

void CMD_Quit::execute() {
    glfwSetWindowShouldClose((GLFWwindow*)_Window, true);
}

void CMD_ZoomMap::execute() {
    static_cast<GameEngine*>(_Game)->zoomCamera(*_ScrollOffset);
}

void CMD_MoveTestUnit::execute() {
    static_cast<GameEngine*>(_Game)->testMoveFirstUnit(*_Xpos, *_Ypos);
}