//
// Created by RH on 05.10.2019.
//

#ifndef OPENBROODCRAFT_TEXENTITY_H
#define OPENBROODCRAFT_TEXENTITY_H

#include "headerinclude.h"

enum EntityType {
    ENTITY_NONE = -1,
    ENTITY_UNIT,
    ENTITY_DOODAD,
    ENTITY_ROCK
};


class TexEntity {
protected:
    static unsigned int Current_ID;

    float offsetX;
    float offsetY;
    glm::vec3 WorldSpacePos;

    MeshObject Mesh;

public:
    TexEntity(MeshObject* mesh, EntityType type, glm::vec3 WorldSpacePos);

    TexEntity();

    EntityType Type_ID;
    unsigned int ID;

    void setPosition(glm::vec3 newPos);
    glm::vec3 getPosition();


    void drawAction(Shader* _shader);

    void free_mesh();
};


#endif //OPENBROODCRAFT_TEXENTITY_H
