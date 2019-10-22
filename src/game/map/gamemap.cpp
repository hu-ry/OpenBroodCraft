//
// Created by RH on 11/10/2019.
//

#include "gamemap.h"
#include "../../libs/json.hpp"

// for convenience
using json = nlohmann::json;

GameMap::GameMap(const char* mapdataPath) {
    parseJSON(mapdataPath);
    preparing_map();
}



void GameMap::draw(glm::mat4* _projection, glm::mat4* _view, glm::mat4* _model, Shader* _shader) {
    _shader->use();
    _shader->setMatrix4fv("projection", 1, *_projection);
    _shader->setMatrix4fv("view", 1, *_view);
 //TODO: Goes through all the map_tile's in mapTile and uses the mesh and the offsets to draw the instanced meshes
    glm::mat4 temp_model = *_model;

    _shader->setMatrix4fv("model", 1, *_model);

    for (unsigned int i = 0; i < this->getMapTile().size(); ++i) {
        this->meshes.at(i).drawInstanced(*_shader);
        std::cout << "textures: " << this->meshes.at(i).VAO_ID << std::endl;
    }
    *_model = temp_model;
}

void GameMap::push_mesh(MeshObject to_add) {
    this->meshes.push_back(to_add);
}

void GameMap::parseJSON(const char* mapdataPath) {
    std::string jsonString;
    std::ifstream jsonFile;

    jsonFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        // open files
        jsonFile.open(mapdataPath);
        std::stringstream jsonStream;
        // read file's buffer contents into streams
        jsonStream << jsonFile.rdbuf();
        // close file handlers
        jsonFile.close();
        // convert stream into string
        jsonString = jsonStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::JSONFILE::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    std::cout << "data: " << jsonString << std::endl;

    json jsonData = json::parse(jsonString);

    this->map_name = jsonData.value("map_name", "");
    this->map_version = jsonData.value("map_version", "null");
    json temp = jsonData.at("map_dimensions");
    this->map_dimensions[0] = temp.at(0);
    this->map_dimensions[1] = temp.at(1);
    this->map_size = jsonData.value("map_size", 0);

    json map_tile_data = jsonData.at("map_tiles");
    std::cout << "map_tile_data: " << map_tile_data << "\n" << std::endl;
    temp = map_tile_data.back();
    int max_i = temp.value("id", 0);

    for(int i=0; i <= max_i; i++) {
        json currentTile = map_tile_data.at(i);

        this->mapTile.push_back(map_tile{.id = (unsigned int)currentTile.value("id", 0),
                                         .file_name = currentTile.value("file_name", ""),
                                         .type = currentTile.value("type", "None"),
                                         .offset_amount = 0,
                                         .alignment = (Orientation)currentTile.value("alignment", 0)
        });
        std::cout << "map_tile_data: " << this->mapTile.at(i).file_name << "\n" << std::endl;
    }
    map_tile_data = jsonData.at("tiles");

    json::iterator it = map_tile_data.begin();
    for(unsigned int i=0; i < map_size; i++) {
        for(int k=0; k <= max_i; k++) {
            if(k == *it) {
                this->mapTile.at(k).offset_amount++;
            }
        }
        this->tiles[i] = tile_entity{.index = i, .offset = glm::vec2(0, 0), .tile = &this->mapTile.at((unsigned int)*it)};
        ++it;
    }

}

void GameMap::preparing_map() {
float x_start = -(((float)map_dimensions[0]/2)*TILE_SIZE)-(TILE_SIZE/2);
float y_start = ((float)map_dimensions[1]/2)*TILE_SIZE-(TILE_SIZE/2);

    for(int i=0; i < map_size; i++) {
        int x_pos = (i % map_dimensions[0]);
        int y_pos = (i - (i % map_dimensions[0])) / map_dimensions[0];
        tiles[i].offset = glm::vec2(
                (x_start + x_pos*TILE_SIZE)//FROSTUM_WIDTH,
                ,(y_start - y_pos*TILE_SIZE));//FROSTUM_HEIGHT)-1.5f );

        std::cout << "x: " << tiles[i].offset.x << " y: " << tiles[i].offset.y << std::endl;
    }

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

std::vector<map_tile> GameMap::getMapTile() {
    return this->mapTile;
}

tile_entity* GameMap::getEntitiesPtr() {
    return &this->tiles[0];
}

MeshObject* GameMap::getMeshPtr(int index) {
    return &this->meshes[index];
}



void GameMap::deallocateMesh() {
    for (unsigned int i = 0; i < (unsigned int)this->getMapTile().size(); ++i) {
        this->meshes.at(i).deallocateVertexArrays();
    }
}