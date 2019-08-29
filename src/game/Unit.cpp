//
// Created by Guest on 27/08/2019.
//

#include "Unit.h"

unsigned int Unit::Current_ID;

Unit::Unit(MeshObject* mesh, UnitType type, glm::vec3 WorldSpacePos, unsigned int speed) : ID(Current_ID++){
    this->Mesh = mesh;
    this->Type_ID = type;
    this->WorldSpacePos = WorldSpacePos;
    this->MovementSpeed = speed;
    this->selected = true;

    this->offsetX = (float)fabs(mesh->vertices[0].x);
    this->offsetY = (float)fabs(mesh->vertices[0].y);
}

Unit::Unit(MeshObject* mesh, UnitType type, glm::vec3 WorldSpacePos) : ID(Current_ID++), MovementSpeed(1) {
    this->Mesh = mesh;
    this->Type_ID = type;
    this->WorldSpacePos = WorldSpacePos;
    this->selected = true;

    this->offsetX = (float)fabs(mesh->vertices[0].x);
    this->offsetY = (float)fabs(mesh->vertices[0].y);
}

Unit::Unit() {

}

void Unit::setPosition(glm::vec3 newPos) {
    this->WorldSpacePos = newPos;
}

glm::vec3 Unit::getPosition() {
    return this->WorldSpacePos;
}


void Unit::drawAction() {

}

void Unit::recieveInput(float posX, float posY) {

}
