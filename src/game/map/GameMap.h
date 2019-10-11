//
// Created by Guest on 11/10/2019.
//

#ifndef OPENBROODCRAFT_MAP_H
#define OPENBROODCRAFT_MAP_H

#include "map_tile.h"


class GameMap {
public:
    GameMap(const char* mapdataPath);

    void draw(glm::mat4* _model, Shader* _shader);


    unsigned int getMapSize();
    std::string getMapName();
    std::string getMapVersion();
private:
    std::string map_name;
    std::string map_version;

    unsigned int map_size;

    std::vector<map_tile> mapTile;
    tile_entity tiles[MAX_MAP_SIZE];

    void parseJSON(const char* mapdataPath);
};


#endif //OPENBROODCRAFT_MAP_H
