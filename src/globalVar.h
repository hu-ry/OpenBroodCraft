//
// Created by Guest on 24/08/2019.
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

extern float deltaTime;
extern float lastFrame;

extern int MAX_AMOUNT_UNITS;

extern float TILE_SIZE;

enum ProgMode {
    PROG_NONE = -1,
    PROG_MENU,
    PROG_GAME,
    PROG_PAUSE
};

extern ProgMode PROGRAM_MODE;

struct MouseStatus {
    int msPosX;
    int msPosY;
    int msLastPosX;
    int msLastPosY;
    int button;
    int action;
};


typedef void (* INPUTgameengine)(float, float);


#endif //TESTINGOPENGL_GLOBALVAR_H
