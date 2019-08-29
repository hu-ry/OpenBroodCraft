//
// Created by Guest on 29/08/2019.
//

#ifndef OPENBROODCRAFT_GAMEENGINE_H
#define OPENBROODCRAFT_GAMEENGINE_H


#include "Unit.h"
#include "../globalVar.h"

class GameEngine {
public:
    Unit *ActiveUnits = new Unit[MAX_AMOUNT_UNITS];

    GameEngine();


    void Execute();


    int addUnit(Unit unit_to_add);

    void Init();
    void free();

private:
    int Current_Unit = 0;

};


#endif //OPENBROODCRAFT_GAMEENGINE_H
