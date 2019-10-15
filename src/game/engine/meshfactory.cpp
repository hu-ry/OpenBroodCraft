//
// Created by RH on 14/10/2019.
//

#include "meshfactory.h"


MeshFactory::MeshFactory(const std::string &pathTextures, const std::string &pathModel) {
    this->path_to_textures = pathTextures;
    this->path_to_models = pathModel;
}


void MeshFactory::createMapMesh(GameMap t_map) {
    for (unsigned int i = 0; i < (unsigned int)t_map.getMapTile().size(); ++i) {
        std::string temp = path_to_map_textures;
        std::vector<TextureObject> maptile_texture = {
                TextureObject( (path_to_map_textures.append(t_map.getMapTile().at(i).file_name)).c_str() )
        };
        path_to_map_textures = temp;
        t_map.getMapTile().at(i).mesh = MeshObject("../objectmodels/testTile.vmo", GL_STATIC_DRAW, true, maptile_texture);
        t_map.getMapTile().at(i).mesh.initInstancing(
                t_map.getMapTile().at(i).offsets.data,
                t_map.getMapTile().at(i).offsets.size );
    }
}

MeshObject MeshFactory::createGeometryMesh() {
    return MeshObject(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
}

MeshObject MeshFactory::createUnitMesh() {
    return MeshObject(); // TODO: implement pls
}