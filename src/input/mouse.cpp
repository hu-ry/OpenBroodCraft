//
// Created by Guest on 27/08/2019.
//
#include "mouse.h"
#include "../game/Unit.h"

MouseStatus msStatus;
Camera* _Camera;
GameEngine* gameProg;

float relative_world_msPosX;
float relative_world_msPosY;


void initMouse(Camera* __Camera, GameEngine *gameprog) {
    _Camera = __Camera;
    gameProg = gameprog;
    msStatus.msPosX = 0.0f;
    msStatus.msPosY = 0.0f;
    msStatus.button = 0;
    msStatus.action = 0;
    relative_world_msPosX = INITIAL_CAM_POSITION.x + ((float)msStatus.msPosX-((float)SCR_WIDTH/2));
    relative_world_msPosY = INITIAL_CAM_POSITION.y + ((float)msStatus.msPosY-((float)SCR_HEIGHT/2));
}

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
    //glfwGetCursorPos(window, &msStatus.msPosX, &msStatus.msPosY);

    //std::cout << "frametime: " << deltaTime << std::endl;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        _Camera->ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        _Camera->ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        _Camera->ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        _Camera->ProcessKeyboard(RIGHT, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        gameProg->testMoveFirstUnit(relative_world_msPosX, relative_world_msPosY);
    }
    relative_world_msPosX = _Camera->Position.x + ((float)msStatus.msPosX-((float)SCR_WIDTH/2));
    relative_world_msPosY = _Camera->Position.y + (-((float)msStatus.msPosY-((float)SCR_HEIGHT/2)));

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    _Camera->ProcessScrollInput(yoffset);
    std::cout << "ScrollOffset_Y: " << yoffset << std::endl;
}

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
    msStatus.msPosX = (float)xpos;
    msStatus.msPosY = (float)ypos;
    relative_world_msPosX = _Camera->Position.x + ((float)msStatus.msPosX-((float)SCR_WIDTH/2));
    relative_world_msPosY = _Camera->Position.y + (-((float)msStatus.msPosY-((float)SCR_HEIGHT/2)));

    std::cout << " MousePosX: " << relative_world_msPosX << " MousePosY: " << relative_world_msPosY << std::endl;
    std::cout << "MOUSEframetime: " << deltaTime << std::endl;
}
