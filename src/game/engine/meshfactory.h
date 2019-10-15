//
// Created by RH on 14/10/2019.
//

#ifndef OPENBROODCRAFT_MESHFACTORY_H
#define OPENBROODCRAFT_MESHFACTORY_H


#include "../../headerinclude.h"
#include "../map/gamemap.h"

class MeshFactory {
public:
    MeshFactory(const std::string &pathTextures, const std::string &pathModel);

    void createMapMesh(GameMap t_map);

    MeshObject createGeometryMesh();
    MeshObject createUnitMesh();

private:
    std::string path_to_map_textures = "../textures/maptiles/";
    std::string path_to_textures;
    std::string path_to_models;
};


#endif //OPENBROODCRAFT_MESHFACTORY_H
