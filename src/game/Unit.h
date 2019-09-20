//
// Created by Guest on 27/08/2019.
//

#ifndef OPENBROODCRAFT_UNIT_H
#define OPENBROODCRAFT_UNIT_H

#include "../headerInclude.h"
#include "../globalVar.h"
#include "command.h"

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
    bool selected;

    glm::vec3 translate = glm::vec3(0.0f, 0.0f, 1.0f);

    Unit(MeshObject* mesh, UnitType type, glm::vec3 WorldSpacePos, Command cmd, unsigned int speed);

    Unit(MeshObject* mesh, UnitType type, glm::vec3 WorldSpacePos, Command cmd);

    Unit();

    void Run();

    void processCommand();

    void issueCmd(CommandType type, glm::vec2 dest);

    void drawAction(Shader* _shader);

    void free_mesh();


    void setPosition(glm::vec3 newPos);
    glm::vec3 getPosition();
private:
    static unsigned int Current_ID;
    float offsetX;
    float offsetY;

    glm::vec3 WorldSpacePos;

    Command CmdOrder;

    glm::vec2 MoveVec = glm::vec2(0.0f, 0.0f);

    MeshObject Mesh;

    inline float getMovementSpeed();
};


#endif //OPENBROODCRAFT_UNIT_H
