//
// Created by RH on 24/08/2019.
//

#ifndef TESTINGOPENGL_GLOBALVAR_H
#define TESTINGOPENGL_GLOBALVAR_H

#include <glad/glad.h>

#include <glm/vec3.hpp>

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;

extern float FROSTUM_WIDTH;
extern float FROSTUM_HEIGHT;
extern float FROSTUM_NEAR;
extern float FROSTUM_FAR;
extern float FROSTUM_ZOOM;

// Initial camera position in World Space
extern glm::vec3 INITIAL_CAM_POSITION;

extern float WORLD_SPACE_SCALE;
extern float WORLD_BORDER_X;
extern float WORLD_BORDER_Y;
extern float WORLD_BORDER_Z;

extern float SELECTBOX_DEPTH_Z;

extern float UI_DEPTH_Z;

extern float deltaTime;
extern float lastFrame;

extern int MAX_AMOUNT_UNITS;

extern float TILE_SIZE;
const unsigned int MAX_MAP_SIZE = 4096;

enum ProgMode {
    PROG_NONE = -1,
    PROG_MENU,
    PROG_GAME,
    PROG_PAUSE
};

extern ProgMode PROGRAM_MODE;

struct MouseStatus {
    double msPosX;
    double msPosY;
    double msLastPosX;
    double msLastPosY;
    int button;
    int action;

    void initStatus() {
        msPosX = 0;
        msPosY = 0;
        msLastPosX = 0;
        msLastPosY = 0;
        button = -1;
        action = -1;
    }
    void updateMousePos(double xPosRaw, double yPosRaw) {
        msPosX = (int) xPosRaw;
        msPosY = (int) yPosRaw;
    }
};

typedef uint64_t EntityID;

typedef void (* INPUTgameengine)(float, float);


#endif //TESTINGOPENGL_GLOBALVAR_H
