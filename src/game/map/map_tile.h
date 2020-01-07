//
// Created by RH on 11/10/2019.
//

#ifndef OPENBROODCRAFT_MAP_TILE_H
#define OPENBROODCRAFT_MAP_TILE_H

#include <string>
#include "../../globalvar.h"
#include "../../headerinclude.h"


typedef struct{
    unsigned int id;
    std::string file_name;
    std::string type;
    unsigned int offset_amount;
    Orientation alignment;
} map_tile;

typedef struct{
    unsigned int index;
    glm::vec2 offset;
    map_tile* tile;
} tile_entity;

typedef struct{
    glm::vec2 start;
    glm::vec2 end;
    std::vector<EntityID> entities;
} cell;

typedef uint64_t cell_id;

#endif //OPENBROODCRAFT_MAP_TILE_H
