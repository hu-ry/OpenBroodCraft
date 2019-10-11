//
// Created by Guest on 28/08/2019.
//

#ifndef OPENBROODCRAFT_MAP_TILES_H
#define OPENBROODCRAFT_MAP_TILES_H


#include <glm/gtc/matrix_transform.hpp>

#include "../../globalVar.h"
#include "../../shader_vf.h"
#include "../../headerInclude.h"

class map_tiles {
public:
    int tiles_x;
    int tiles_y;
    MeshObject mesh;

    map_tiles() = default;

    map_tiles(int tiles_x, int tiles_y, MeshObject mesh) : mesh() {
        this->tiles_x = tiles_x;
        this->tiles_y = tiles_y;
        this->mesh = mesh;
    }

    void draw_map(glm::mat4* _model, Shader* _shader) {
        glm::mat4 temp = *_model;
        *_model = glm::translate(*_model,
                glm::vec3(-((tiles_x/2)*TILE_SIZE)-(TILE_SIZE/2), (tiles_y/2)*TILE_SIZE-(TILE_SIZE/2), WORLD_BORDER_Z));

        for (unsigned int i = 0; i < tiles_x; i++) {
            *_model = glm::translate(*_model, glm::vec3(TILE_SIZE, 0.0f, 0.0f));
            _shader->setMatrix4fv("model", 1, *_model);
            mesh.draw(*_shader);
            for (unsigned int k = 0; k < tiles_y-1; k++) {
                glm::vec3 temp = i%2 == 0 ? glm::vec3(0.0f, -TILE_SIZE, 0.0f) : glm::vec3(0.0f, TILE_SIZE, 0.0f);
                *_model = glm::translate(*_model, temp);
                _shader->setMatrix4fv("model", 1, *_model);
                mesh.draw(*_shader);
            }
        }
        *_model = temp;
        _shader->setMatrix4fv("model", 1, *_model);
    }

private:

};


#endif //OPENBROODCRAFT_MAP_TILES_H
