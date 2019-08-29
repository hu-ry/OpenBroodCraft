//
// Created by Guest on 27/08/2019.
//

#include "Unit.h"

unsigned int Unit::Current_ID;

Unit::Unit(MeshObject* mesh, UnitType type, glm::vec3 WorldSpacePos, unsigned int speed) : ID(Current_ID++){
    Mesh = mesh;
    Type_ID = type;
    this->WorldSpacePos = WorldSpacePos;
    MovementSpeed = speed;
    selected = true;

    offsetX = (float)fabs(mesh->vertices[0].x);
    offsetY = (float)fabs(mesh->vertices[0].y);
}

Unit::Unit(MeshObject* mesh, UnitType type, glm::vec3 WorldSpacePos) : ID(Current_ID++), MovementSpeed(1) {
    Mesh = mesh;
    Type_ID = type;
    this->WorldSpacePos = WorldSpacePos;
    selected = true;

    offsetX = (float)fabs(mesh->vertices[0].x);
    offsetY = (float)fabs(mesh->vertices[0].y);
}


void Unit::drawAction() {

}

void Unit::recieveInput(float posX, float posY) {

}
