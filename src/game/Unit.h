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
    unsigned int MovementSpeed;
    bool selected;

    float offsetX;
    float offsetY;

    Unit(MeshObject* mesh, UnitType type, glm::vec3 WorldSpacePos, unsigned int speed);

    Unit(MeshObject* mesh, UnitType type, glm::vec3 WorldSpacePos);

    Unit();

    void setPosition(glm::vec3 newPos);
    glm::vec3 getPosition();
    void drawAction(Shader* _shader);

    void free_mesh();

private:
    static unsigned int Current_ID;
    glm::vec3 WorldSpacePos;
    MeshObject Mesh;
};


#endif //OPENBROODCRAFT_UNIT_H
