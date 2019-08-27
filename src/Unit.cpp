//
// Created by Guest on 27/08/2019.
//

#include "Unit.h"


Unit::Unit(MeshObject* mesh, UnitType type, unsigned int speed) : ID(Current_ID++){
    Mesh = mesh;
    Type_ID = type;
    MovementSpeed = speed;
}

Unit::Unit(MeshObject* mesh, UnitType type) : ID(Current_ID++), MovementSpeed(1) {
    Mesh = mesh;
    Type_ID = type;
}


