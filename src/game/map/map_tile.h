//
// Created by RH on 11/10/2019.
//

#ifndef OPENBROODCRAFT_MAP_TILE_H
#define OPENBROODCRAFT_MAP_TILE_H

#include <string>
#include "../../globalvar.h"
#include "../../headerinclude.h"

enum Orientation{
    TOP_UP = 0,
    TOP_RIGHT,
    TOP_LEFT,
    TOP_DOWN
};

typedef struct{
    unsigned int size = 0;
    glm::vec2 data[MAX_MAP_SIZE];
} vec2_4096_t;

typedef struct{
    unsigned int id;
    std::string file_name;
    std::string type;
    MeshObject mesh;
    vec2_4096_t offsets;
    Orientation alignment;
} map_tile;

typedef struct{
    unsigned int index;
    map_tile* tile;
} tile_entity;

#endif //OPENBROODCRAFT_MAP_TILE_H
