//
// Created by RH on 16.08.2019.
//
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "globalVar.h"
#include "camera.h"

#ifndef OPENBROODCRAFT_MAIN_H
#define OPENBROODCRAFT_MAIN_H

glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);

// camera
Camera Camera(INITIAL_CAM_POSITION);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    /* Telling OpenGL the size of the rendering window */
    glViewport(0, 0, width, height);
    SCR_WIDTH = static_cast<unsigned int>(width);
    SCR_HEIGHT = static_cast<unsigned int>(height);
    FROSTUM_WIDTH = SCR_WIDTH;
    FROSTUM_HEIGHT = SCR_HEIGHT;
}

void processInput(GLFWwindow *window) {
    float cameraSpeed = 2.5f * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        Camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        Camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        Camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        Camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {

        std::cout << vec.x << vec.y << vec.z << std::endl;
    }
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {

        std::cout << vec.x << vec.y << vec.z << std::endl;
    }
    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {

        std::cout << vec.x << vec.y << vec.z << std::endl;
    }
    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {

        std::cout << vec.x << vec.y << vec.z << std::endl;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Camera.ProcessScrollInput(yoffset);
    std::cout << "ScrollOffset_Y: " << yoffset << std::endl;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    Camera.ProcessMouseMovement(xoffset, yoffset);
}


#endif //OPENBROODCRAFT_MAIN_H