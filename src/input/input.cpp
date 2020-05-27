//
// Created by RH on 27/08/2019.
//
#include "input/input.h"

InputAgent* ioAgent;

void initInput(InputAgent *_ioAgent) {
    ioAgent = _ioAgent;
    _ioAgent->initAgent();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    /* Telling OpenGL the size of the rendering window */
    glViewport(0, 0, width, height);
    SCR_WIDTH = static_cast<unsigned int>(width);
    SCR_HEIGHT = static_cast<unsigned int>(height);
    FROSTUM_WIDTH = static_cast<float>(SCR_WIDTH);
    FROSTUM_HEIGHT = static_cast<float>(SCR_HEIGHT);
}

void processInput(GLFWwindow *window) {
    ioAgent->handleInput();
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    ioAgent->scrollCall(xoffset, yoffset);

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    ioAgent->mouseButtonCall(button, action);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    ioAgent->cursorPositionCall(xpos, ypos);
}
