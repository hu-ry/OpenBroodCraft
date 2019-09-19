//
// Created by Guest on 29/08/2019.
//

#ifndef OPENBROODCRAFT_GAMEENGINE_H
#define OPENBROODCRAFT_GAMEENGINE_H


#include "Unit.h"
#include "../globalVar.h"
#include "../camera.h"
#include "map_tiles.h"

class GameEngine {
public:
    Unit *ActiveUnits = new Unit[MAX_AMOUNT_UNITS];

    GameEngine();


    void Execute();


    int addUnit(Unit unit_to_add);
    void loadMap(map_tiles map);

    void recieveInput(float posX, float posY);

    void Init(INPUTgameengine inputFunc);
    void free();

private:
    int Current_Unit = 0;
    map_tiles Current_Map;

    Shader TriangleShader;

    INPUTgameengine ioFunc;
};


#endif //OPENBROODCRAFT_GAMEENGINE_H
