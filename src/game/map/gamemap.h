//
// Created by RH on 11/10/2019.
//

#ifndef OPENBROODCRAFT_MAP_H
#define OPENBROODCRAFT_MAP_H

#include <map>
#include "map_tile.h"


class GameMap {
public:
    GameMap(const char* mapdataPath);

    GameMap() = default;

    void draw(glm::mat4* _projection, glm::mat4* _view, glm::mat4* _model, Shader* _shader);

    void push_mesh(MeshObject to_add);

    unsigned int getMapSize();
    std::string getMapName();
    std::string getMapVersion();
    std::vector<map_tile> getMapTile();
    tile_entity* getEntitiesPtr();
    MeshObject* getMeshPtr(int index);


    void deallocateMesh();
private:
    std::string map_name;
    std::string map_version;
    unsigned int map_dimensions[2];
    unsigned int map_size;

    std::map<cell_id, cell> cell_grid;

    std::vector<map_tile> mapTile;
    std::vector<MeshObject> meshes;
    tile_entity tiles[MAX_MAP_SIZE];

    void parseJSON(const char* mapdataPath);
    void preparing_map();
};


#endif //OPENBROODCRAFT_MAP_H
