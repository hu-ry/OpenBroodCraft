//
// Created by Guest on 27/08/2019.
//
#include "mouse.h"
#include "../game/Unit.h"

MouseStatus msStatus;
Camera* _Camera;
float* _lastX;
float* _lastY;
bool* _firstMouse;

float relative_world_msPosX;
float relative_world_msPosY;


void initMouse(Camera* __Camera, float* __lastX ,float* __lastY, bool* __firstMouse) {
    _Camera = __Camera;
    _lastX = __lastX;
    _lastY = __lastY;
    _firstMouse = __firstMouse;
    msStatus.firstMs = true;
    msStatus.msPosX = 0.0f;
    msStatus.msPosY = 0.0f;
    msStatus.button = 0;
    msStatus.action = 0;
    relative_world_msPosX = INITIAL_CAM_POSITION.x + ((float)msStatus.msPosX-((float)SCR_WIDTH/2));
    relative_world_msPosY = INITIAL_CAM_POSITION.y + ((float)msStatus.msPosY-((float)SCR_HEIGHT/2));
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    _Camera->ProcessScrollInput(yoffset);
    std::cout << "ScrollOffset_Y: " << yoffset << std::endl;
}

//void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//    if (*_firstMouse) {
//        *_lastX = xpos;
//        *_lastY = ypos;
//        *_firstMouse = false;
//    }
//
//    float xoffset = xpos - *_lastX;
//    float yoffset = *_lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//    *_lastX = xpos;
//    *_lastY = ypos;
//
//    _Camera->ProcessMouseMovement(xoffset, yoffset);
//}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        //Unit.recieveInput(relative_world_msPosX, relative_world_msPosY);
        std::cout << " button: " << "BUTTON_RIGHT" << " action: " << "PRESS" << std::endl;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {

        std::cout << " button: " << "BUTTON_RIGHT" << " action: " << "RELEASE" << std::endl;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

        std::cout << " button: " << "BUTTON_LEFT" << " action: " << "PRESS" << std::endl;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {

        std::cout << " button: " << "BUTTON_LEFT" << " action: " << "RELEASE" << std::endl;
    }

}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (msStatus.firstMs) {
        msStatus.msPosX = xpos;
        msStatus.msPosY = ypos;


        msStatus.firstMs = false;
    }
    msStatus.msPosX = xpos;
    msStatus.msPosY = ypos;
    std::cout << " MousePosX: " << xpos << " MousePosY: " << ypos << std::endl;
    relative_world_msPosX = _Camera->Position.x + ((float)msStatus.msPosX-((float)SCR_WIDTH/2));
    relative_world_msPosY = _Camera->Position.y + ((float)msStatus.msPosY-((float)SCR_HEIGHT/2));
}