//
// Created by RH on 27/08/2019.
//

#include "unit.h"



Unit::Unit(MeshObject* mesh, UnitType type, glm::vec3 WorldSpacePos, UnitOrder unitOrder, unsigned int speed)
: TexEntity(mesh, ENTITY_UNIT, WorldSpacePos) {

    this->MovementSpeed = speed * (unsigned int)WORLD_SPACE_SCALE;
    this->selected = false;
    this->unitOrder = unitOrder;
}

Unit::Unit(MeshObject* mesh, UnitType type, glm::vec3 WorldSpacePos, UnitOrder unitOrder)
: TexEntity(mesh, ENTITY_UNIT, WorldSpacePos), MovementSpeed(1*(unsigned int)WORLD_SPACE_SCALE) {

    this->selected = false;
    this->unitOrder = unitOrder;
}

Unit::Unit() : TexEntity() {

}

void Unit::Run() {
    this->processOrder();
    std::cout << this->Mesh.VAO_ID << std::endl;

}

void Unit::processOrder() {
   // if(CmdOrder.Type > 0) {
   //     if(((WorldSpacePos.x >= CmdOrder.Destination.x && MoveVec.x >= 0)
   //     || (WorldSpacePos.x <= CmdOrder.Destination.x && MoveVec.x <= 0))
   //     && ((WorldSpacePos.y >= CmdOrder.Destination.y && MoveVec.y >= 0)
   //     || (WorldSpacePos.y <= CmdOrder.Destination.y && MoveVec.y <= 0)))
   //     {
   //         this->setPosition(glm::vec3(CmdOrder.Destination.x, CmdOrder.Destination.y, WorldSpacePos.z));
   //         this->CmdOrder.Type = COMMAND_NONE;
   //     } else {
   //         this->setPosition(this->WorldSpacePos + glm::vec3(this->MoveVec * this->getMovementSpeed(), 0.0f));
   //     }
            translate = WorldSpacePos;
   // }
}

void Unit::issueCmd(CommandType type, glm::vec2 dest) {
    if(dest.x != getPosition().x && dest.y != getPosition().y) {
        this->CmdOrder = Command(COMMAND_MOVE, glm::vec2(getPosition().x, getPosition().y), dest);
        this->MoveVec = glm::normalize(CmdOrder.Destination - CmdOrder.StartPos);
    }
}

inline float Unit::getMovementSpeed() {
    return ((float)MovementSpeed*deltaTime) / 4.0f;
}