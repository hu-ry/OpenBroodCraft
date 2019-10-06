//
// Created by Guest on 27/08/2019.
//

#ifndef OPENBROODCRAFT_INPUT_H
#define OPENBROODCRAFT_INPUT_H

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>

#include "../camera.h"
#include <iostream>
#include "../globalVar.h"
#include "../game/gameengine.h"


void initMouse(Camera* __Camera, GameEngine *gameprog);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

#endif //OPENBROODCRAFT_INPUT_H
