//
// Created by RH on 27/08/2019.
//

#ifndef OPENBROODCRAFT_UNIT_H
#define OPENBROODCRAFT_UNIT_H


#include "../globalvar.h"
#include "../input/command.h"
#include "texentity.h"

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

class Unit : public TexEntity {
public:
    UnitType Type_ID;
    unsigned int MovementSpeed;
    bool selected;

    glm::vec3 translate = glm::vec3(0.0f, 0.0f, 1.0f);

    Unit(MeshObject* mesh, UnitType type, glm::vec3 WorldSpacePos, unsigned int speed);

    Unit(MeshObject* mesh, UnitType type, glm::vec3 WorldSpacePos);

    Unit();

    void Run();

    void processCommand();

    void issueCmd(CommandType type, glm::vec2 dest);


private:


    glm::vec2 MoveVec = glm::vec2(0.0f, 0.0f);

    inline float getMovementSpeed();
};


#endif //OPENBROODCRAFT_UNIT_H
