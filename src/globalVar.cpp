#include "globalVar.h"


unsigned int SCR_WIDTH      = 1280;
unsigned int SCR_HEIGHT     = 960;

float FROSTUM_WIDTH         = SCR_WIDTH;
float FROSTUM_HEIGHT        = SCR_HEIGHT;
float FROSTUM_NEAR          = 1.0f;
float FROSTUM_FAR           = 1000.0f;
float FROSTUM_ZOOM          = 2.0f;

// Initial camera position in World Space
glm::vec3 INITIAL_CAM_POSITION = glm::vec3(0.0f, 0.0f, FROSTUM_FAR-FROSTUM_NEAR);

float WORLD_SPACE_SCALE     = 1000.0f;
float WORLD_BORDER_X        = 0.0f;
float WORLD_BORDER_Y        = 100;
float WORLD_BORDER_Z        = 0.0f;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

int MAX_AMOUNT_UNITS = 100;

float TILE_SIZE = 64.0f;

ProgMode PROGRAM_MODE = PROG_GAME;