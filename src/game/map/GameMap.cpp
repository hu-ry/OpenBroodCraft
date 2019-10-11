//
// Created by Guest on 11/10/2019.
//

#include "GameMap.h"


GameMap::GameMap(const char* mapdataPath) {

}



void GameMap::draw(glm::mat4* _model, Shader* _shader) {

}

void GameMap::parseJSON(const char* mapdataPath) {

}

std::string GameMap::getMapName() {
    return this->map_name;
}

unsigned int GameMap::getMapSize() {
    return this->map_size;
}

std::string GameMap::getMapVersion() {
    return this->map_version;
}