//
// Created by Guest on 27/08/2019.
//

#ifndef OPENBROODCRAFT_UNIT_H
#define OPENBROODCRAFT_UNIT_H

#include "../headerInclude.h"

enum UnitType {
    UNIT_NONE = -1,
    UNIT_GENERIC,
    UNIT_MARINE,
    UNIT_ZERGLING,
    UNIT_ZEALOT,
    UNIT_SCV,
    UNIT_DRONE,
    UNIT_PROBE
};

class Unit {
public:
    unsigned int ID;
    UnitType Type_ID;
    glm::vec3 WorldSpacePos;
    unsigned int MovementSpeed;
    bool selected;

    float offsetX;
    float offsetY;

    Unit(MeshObject* mesh, UnitType type, glm::vec3 WorldSpacePos, unsigned int speed);

    Unit(MeshObject* mesh, UnitType type, glm::vec3 WorldSpacePos);

    void drawAction();

    void recieveInput(float posX, float posY);// in game class implementieren und dann aufrufen lassen und damit durch
    // alle Units iterieren.
private:
    static unsigned int Current_ID;

    MeshObject* Mesh;
};


#endif //OPENBROODCRAFT_UNIT_H
