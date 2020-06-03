//
// Created by RH on 21/01/2020.
//

#ifndef OPENBROODCRAFT_INPUTAGENT_H
#define OPENBROODCRAFT_INPUTAGENT_H

#include "command.h"
#include "globalvar.h"
#include "game/gameengine.hpp"

#include <GLFW/glfw3.h>

class InputAgent {
public:
    InputAgent(GLFWwindow* t_window, GameEngine* t_game);
    ~InputAgent();

    void initAgent();

    void handleInput();

    void scrollCall(double xoffset, double yoffset);
    void mouseButtonCall(int button, int action);
    void cursorPositionCall(double xscreenpos, double yscreenpos);

    MouseStatus _msStatus;

private:
    GameEngine* _Game;
    GLFWwindow* _Window;

    Command* _KeyESC;
    Command* _KeyQ;
    Command* _KeyW;
    Command* _KeyE;
    Command* _KeyR;
    Command* _KeyA;
    Command* _KeyS;
    Command* _KeyD;
    Command* _KeyF;
    Command* _KeyZ;
    Command* _KeyX;
    Command* _KeyC;
    Command* _KeyV;
    Command* _KeySPACE;
    Command* _KeyCTRL;
    Command* _KeySHIFT;
    Command* _KeyALT;
    Command* _Key1;
    Command* _Key2;
    Command* _Key3;
    Command* _Key4;
    Command* _Key5;

    Command* _MouseLeft;
    Command* _MouseRight;
    Command* _MouseScroll;

    double relative_world_msPosX;
    double relative_world_msPosY;

    double scrollOffset;

    void screenToWorldSpace(double& xPos, double& yPos, double& xWorld, double& yWorld);
};



#endif //OPENBROODCRAFT_INPUTAGENT_H
