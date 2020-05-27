//
// Created by RH on 21/01/2020.
//
#include "input/inputAgent.h"


InputAgent::InputAgent(GLFWwindow* t_window, GameEngine* t_game) : _Window(t_window), _Game(t_game){

    _KeyESC = new CMD_Quit(t_window);

    _KeyW = new CMD_MoveCamera(t_game, FORWARD);
    _KeyS = new CMD_MoveCamera(t_game, BACKWARD);
    _KeyA = new CMD_MoveCamera(t_game, LEFT);
    _KeyD = new CMD_MoveCamera(t_game, RIGHT);

    _KeyE = new CMD_MoveTestUnit(t_game, &relative_world_msPosX, &relative_world_msPosY);

    _MouseScroll = new CMD_ZoomMap(t_game, &scrollOffset);
    
}

InputAgent::~InputAgent() {
    delete _KeyESC;

    delete _KeyW;
    delete _KeyS;
    delete _KeyA;
    delete _KeyD;

    delete _KeyE;
    
    delete _MouseScroll;
    
}

void InputAgent::handleInput() {
    relative_world_msPosX = ((float)_msStatus.msPosX - ((float)SCR_WIDTH / 2)) / (FROSTUM_ZOOM / 2);
    relative_world_msPosY = (-((float)_msStatus.msPosY - ((float)SCR_HEIGHT / 2))) / (FROSTUM_ZOOM / 2);



    //std::cout << "frametime: " << deltaTime << std::endl;
    if(glfwGetKey(_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        _KeyESC->execute();
    }
    if (glfwGetKey(_Window, GLFW_KEY_W) == GLFW_PRESS) {
        _KeyW->execute();
    }
    if (glfwGetKey(_Window, GLFW_KEY_S) == GLFW_PRESS) {
        _KeyS->execute();
    }
    if (glfwGetKey(_Window, GLFW_KEY_A) == GLFW_PRESS) {
        _KeyA->execute();
    }
    if (glfwGetKey(_Window, GLFW_KEY_D) == GLFW_PRESS) {
        _KeyD->execute();
    }
    if(glfwGetKey(_Window, GLFW_KEY_E) == GLFW_PRESS) {
        _KeyE->execute();
    }
    if(_msStatus.button == GLFW_MOUSE_BUTTON_LEFT && _msStatus.action == GLFW_PRESS) {
        _Game->selectBoxing(
                ((float)_msStatus.msLastPosX - ((float)SCR_WIDTH / 2)) / (SCR_WIDTH / 2),
                (-((float)_msStatus.msLastPosY - ((float)SCR_HEIGHT / 2))) / (SCR_HEIGHT / 2),
                ((float)_msStatus.msPosX - ((float)SCR_WIDTH / 2)) / (SCR_WIDTH / 2),
                (-((float)_msStatus.msPosY - ((float)SCR_HEIGHT / 2))) / (SCR_HEIGHT / 2) );
    }

}

void InputAgent::scrollCall(double xoffset, double yoffset) {
    scrollOffset = yoffset;
    _MouseScroll->execute();
    std::cout << "ScrollOffset_Y: " << yoffset << std::endl;
}

void InputAgent::mouseButtonCall(int button, int action) {
    _msStatus.button = button;
    _msStatus.action = action;
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        //Unit.recieveInput(relative_world_msPosX, relative_world_msPosY);
        std::cout << " button: " << "BUTTON_RIGHT" << " action: " << "PRESS" << std::endl;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        _Game->testMoveFirstUnit(relative_world_msPosX, relative_world_msPosY);
        std::cout << " button: " << "BUTTON_RIGHT" << " action: " << "RELEASE" << std::endl;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        _msStatus.msLastPosX = _msStatus.msPosX;
        _msStatus.msLastPosY = _msStatus.msPosY;
        //last_relative_world_msPosX = ((float)_msStatus.msLastPosX-((float)SCR_WIDTH/2))/(FROSTUM_ZOOM/2);
        //last_relative_world_msPosY = (-((float)_msStatus.msLastPosY-((float)SCR_HEIGHT/2)))/(FROSTUM_ZOOM/2);
        std::cout << " button: " << "BUTTON_LEFT" << " action: " << "PRESS" << std::endl;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {

        std::cout << " button: " << "BUTTON_LEFT" << " action: " << "RELEASE" << std::endl;
    }
}

void InputAgent::cursorPositionCall(double xscreenpos, double yscreenpos) {
    _msStatus.updateMousePos(xscreenpos, yscreenpos);
    screenToWorldSpace(xscreenpos, yscreenpos, relative_world_msPosX, relative_world_msPosY);

    std::cout << " MousePosX: " << relative_world_msPosX << " MousePosY: " << relative_world_msPosY << std::endl;
    std::cout << "MOUSEframetime: " << deltaTime << std::endl;
}

void InputAgent::initAgent() {
    _msStatus.initStatus();
    relative_world_msPosX = INITIAL_CAM_POSITION.x + ((float)_msStatus.msPosX - ((float)SCR_WIDTH / 2));
    relative_world_msPosY = INITIAL_CAM_POSITION.y + ((float)_msStatus.msPosY - ((float)SCR_HEIGHT / 2));
}

void InputAgent::screenToWorldSpace(double& xScreen, double& yScreen, double& xWorld, double& yWorld) {
    xWorld = (xScreen-((double)SCR_WIDTH/2))/((double)FROSTUM_ZOOM/2);
    yWorld = (-(yScreen-((double)SCR_HEIGHT/2)))/((double)FROSTUM_ZOOM/2);
}