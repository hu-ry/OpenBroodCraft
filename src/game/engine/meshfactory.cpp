//
// Created by RH on 14/10/2019.
//

#include "meshfactory.h"


MeshFactory::MeshFactory(const std::string &pathTextures, const std::string &pathModel) {
    this->path_to_textures = pathTextures;
    this->path_to_models = pathModel;
}


void MeshFactory::createMapMesh(GameMap* t_map) {
    for (unsigned int i = 0; i < (unsigned int)t_map->getMapTile().size(); ++i) {
        std::string temp = path_to_map_textures;

        std::vector<TextureObject> test;
        test.push_back( TextureObject(temp.append(t_map->getMapTile().at(i).file_name).c_str()) );
        MeshObject meshtest = MeshObject("../objectmodels/testTile.vmo", GL_STATIC_DRAW, true, test);
        t_map->push_mesh(meshtest);
        glm::vec2 translations[MAX_MAP_SIZE];
        int count_trans = 0;
        for(int k = 0; k < t_map->getMapSize(); k++) {
            // comparing if the id's are the same
            if( t_map->getEntitiesPtr()[k].tile->id == (t_map->getMapTile().at(i)).id ) {
                translations[count_trans] = t_map->getEntitiesPtr()[k].offset;
                count_trans++;
            }
        }
        t_map->getMeshPtr(i)->initInstancing(
                translations,
                t_map->getMapTile().at(i).offset_amount );
        std::cout << t_map->getMeshPtr(i)->instanceSize << std::endl;
    }
}

MeshObject MeshFactory::createGeometryMesh() {
    return MeshObject(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
}

MeshObject MeshFactory::createUnitMesh() {
    return MeshObject(); // TODO: implement pls
}