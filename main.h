//
// Created by RH on 16.08.2019.
//
#include <GLFW/glfw3.h>

#ifndef OPENBROODCRAFT_MAIN_H
#define OPENBROODCRAFT_MAIN_H

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


#endif //OPENBROODCRAFT_MAIN_H