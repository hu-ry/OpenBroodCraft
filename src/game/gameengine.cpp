//
// Created by Guest on 29/08/2019.
//

#include "gameengine.h"





GameEngine::GameEngine() {

}

void GameEngine::Execute() {

    if(this->Current_Unit != 0) {

        for(int i=0;i<=this->Current_Unit;i++) {
            this->ActiveUnits[i].drawAction();
        }
    }
}

int GameEngine::addUnit(Unit unit_to_add) {
    this->ActiveUnits[this->Current_Unit] = unit_to_add;
    this->Current_Unit++;
    return this->Current_Unit;
}

void GameEngine::free() {
    delete[] this->ActiveUnits;
}