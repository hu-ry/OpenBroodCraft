//
// Created by RH on 27/08/2019.
//
#include "input.h"
#include "../game/unit.h"

MouseStatus msStatus;
GameEngine* gameProg;

float relative_world_msPosX;
float relative_world_msPosY;
float last_relative_world_msPosX;
float last_relative_world_msPosY;


void initMouse(GameEngine *gameprog) {
    gameProg = gameprog;
    msStatus.msPosX = 0;
    msStatus.msPosY = 0;
    msStatus.msLastPosX = 0;
    msStatus.msLastPosY = 0;
    msStatus.button = -1;
    msStatus.action = -1;
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

    relative_world_msPosX = ((float)msStatus.msPosX-((float)SCR_WIDTH/2))/(FROSTUM_ZOOM/2);
    relative_world_msPosY = (-((float)msStatus.msPosY-((float)SCR_HEIGHT/2)))/(FROSTUM_ZOOM/2);

    //std::cout << "frametime: " << deltaTime << std::endl;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        gameProg->moveCamera(FORWARD);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        gameProg->moveCamera(BACKWARD);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        gameProg->moveCamera(LEFT);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        gameProg->moveCamera(RIGHT);
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        gameProg->testMoveFirstUnit(relative_world_msPosX, relative_world_msPosY);
    }
    if(msStatus.button == GLFW_MOUSE_BUTTON_LEFT && msStatus.action == GLFW_PRESS) {
        gameProg->selectBoxing(
                ((float)msStatus.msLastPosX-((float)SCR_WIDTH/2))/(SCR_WIDTH/2),
                (-((float)msStatus.msLastPosY-((float)SCR_HEIGHT/2)))/(SCR_HEIGHT/2),
                ((float)msStatus.msPosX-((float)SCR_WIDTH/2))/(SCR_WIDTH/2),
                (-((float)msStatus.msPosY-((float)SCR_HEIGHT/2)))/(SCR_HEIGHT/2) );
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    gameProg->zoomCamera(yoffset);
    std::cout << "ScrollOffset_Y: " << yoffset << std::endl;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    msStatus.button = button;
    msStatus.action = action;
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        //Unit.recieveInput(relative_world_msPosX, relative_world_msPosY);
        std::cout << " button: " << "BUTTON_RIGHT" << " action: " << "PRESS" << std::endl;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        gameProg->testMoveFirstUnit(relative_world_msPosX, relative_world_msPosY);
        std::cout << " button: " << "BUTTON_RIGHT" << " action: " << "RELEASE" << std::endl;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        msStatus.msLastPosX = msStatus.msPosX;
        msStatus.msLastPosY = msStatus.msPosY;
        last_relative_world_msPosX = ((float)msStatus.msLastPosX-((float)SCR_WIDTH/2))/(FROSTUM_ZOOM/2);
        last_relative_world_msPosY = (-((float)msStatus.msLastPosY-((float)SCR_HEIGHT/2)))/(FROSTUM_ZOOM/2);
        std::cout << " button: " << "BUTTON_LEFT" << " action: " << "PRESS" << std::endl;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {

        std::cout << " button: " << "BUTTON_LEFT" << " action: " << "RELEASE" << std::endl;
    }

}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    msStatus.msPosX = (int)xpos;
    msStatus.msPosY = (int)ypos;
    relative_world_msPosX = ((float)msStatus.msPosX-((float)SCR_WIDTH/2))/(FROSTUM_ZOOM/2);
    relative_world_msPosY = (-((float)msStatus.msPosY-((float)SCR_HEIGHT/2)))/(FROSTUM_ZOOM/2);

    std::cout << " MousePosX: " << relative_world_msPosX << " MousePosY: " << relative_world_msPosY << std::endl;
    std::cout << "MOUSEframetime: " << deltaTime << std::endl;
}
