//
// Created by Guest on 27/08/2019.
//

#include "Unit.h"

unsigned int Unit::Current_ID;

Unit::Unit(MeshObject* mesh, UnitType type, glm::vec3 WorldSpacePos, Command cmd, unsigned int speed) : ID(Current_ID++){
    this->Mesh = *mesh;
    this->Type_ID = type;
    this->WorldSpacePos = WorldSpacePos;
    this->MovementSpeed = speed * (unsigned int)WORLD_SPACE_SCALE;
    this->selected = true;
    this->CmdOrder = cmd;
    this->offsetX = (float)fabs(mesh->vertices[0].x);
    this->offsetY = (float)fabs(mesh->vertices[0].y);
}

Unit::Unit(MeshObject* mesh, UnitType type, glm::vec3 WorldSpacePos, Command cmd)
: ID(Current_ID++), MovementSpeed(1*(unsigned int)WORLD_SPACE_SCALE) {
    this->Mesh = *mesh;
    this->Type_ID = type;
    this->WorldSpacePos = WorldSpacePos;
    this->selected = true;
    this->CmdOrder = cmd;
    this->offsetX = (float)fabs(mesh->vertices[0].x);
    this->offsetY = (float)fabs(mesh->vertices[0].y);
}

Unit::Unit() {

}

void Unit::Run() {
    this->processCommand();
}

void Unit::processCommand() {
    if(CmdOrder.Type > 0) {
        this->setPosition(this->WorldSpacePos + glm::vec3(this->MoveVec * this->getMovementSpeed(), 0.0f));

        if(((WorldSpacePos.x >= CmdOrder.Destination.x && MoveVec.x >= 0)
        || (WorldSpacePos.x <= CmdOrder.Destination.x && MoveVec.x <= 0))
        && ((WorldSpacePos.y >= CmdOrder.Destination.y && MoveVec.y >= 0)
        || (WorldSpacePos.y <= CmdOrder.Destination.y && MoveVec.y <= 0)))
        {
            this->setPosition(glm::vec3(CmdOrder.Destination.x, CmdOrder.Destination.y, WorldSpacePos.z));
            this->CmdOrder = Command();
        }
            translate = WorldSpacePos;
    }
}

void Unit::issueCmd(CommandType type, glm::vec2 dest) {
    if(dest.x != getPosition().x && dest.y != getPosition().y) {
        this->CmdOrder = Command(COMMAND_MOVE, glm::vec2(getPosition().x, getPosition().y), dest);
        this->MoveVec = glm::normalize(CmdOrder.Destination - CmdOrder.StartPos);
    }
}

void Unit::setPosition(glm::vec3 newPos) {
    this->WorldSpacePos = newPos;
}

glm::vec3 Unit::getPosition() {
    return this->WorldSpacePos;
}


void Unit::drawAction(Shader* _shader) {
    this->Mesh.draw(*_shader);
}

void Unit::free_mesh() {
    this->Mesh.deallocateVertexArrays();
}

inline float Unit::getMovementSpeed() {
    return ((float)MovementSpeed*deltaTime) / 4.0f;
}