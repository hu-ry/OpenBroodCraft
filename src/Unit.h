//
// Created by Guest on 27/08/2019.
//

#ifndef OPENBROODCRAFT_UNIT_H
#define OPENBROODCRAFT_UNIT_H


#include "MeshObject.h"

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
    unsigned int MovementSpeed;

    Unit(MeshObject* mesh, UnitType type, unsigned int speed);

    Unit(MeshObject* mesh, UnitType type);

private:
    static unsigned int Current_ID;

    MeshObject* Mesh;
};

unsigned int Unit::Current_ID;

#endif //OPENBROODCRAFT_UNIT_H
