//
// Created by RH on 05.10.2019.
//

#include "texentity.h"

unsigned int TexEntity::Current_ID;

TexEntity::TexEntity(MeshObject* mesh, EntityType type, glm::vec3 WorldSpacePos) : ID(Current_ID++) {
    this->Mesh = *mesh;
    this->Type_ID = type;
    this->WorldSpacePos = WorldSpacePos;
    this->offsetX = (float)fabs(mesh->vertices[0].x);
    this->offsetY = (float)fabs(mesh->vertices[0].y);
}

TexEntity::TexEntity() {

}


void TexEntity::setPosition(glm::vec3 newPos) {
    this->WorldSpacePos = newPos;
}

glm::vec3 TexEntity::getPosition() {
    return this->WorldSpacePos;
}

void TexEntity::drawAction(Shader* _shader) {
    this->Mesh.draw(*_shader);
}

void TexEntity::free_mesh() {
    this->Mesh.deallocateVertexArrays();
}