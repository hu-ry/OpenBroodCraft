//
// Created by Guest on 29/08/2019.
//

#ifndef OPENBROODCRAFT_GAMEENGINE_H
#define OPENBROODCRAFT_GAMEENGINE_H


#include <unordered_map>
#include "unit.h"
#include "../globalvar.h"
#include "../camera.h"
#include "map/map_tiles.h"
#include "kernelstore.h"

class GameEngine {
public:
    std::unordered_map<EntityID, TexEntity> TexEntities;
    Unit *ActiveUnits = new Unit[MAX_AMOUNT_UNITS];

    GameEngine();

    void processGamelogic();

    void execute();


    int addUnit(Unit unit_to_add);
    void loadMap(map_tiles map);

    void recieveKeyboardInput(float posX, float posY);
    void moveCamera(Camera_Movement t_direction);
    void zoomCamera(const double &t_offset);
    void moveSelectedUnits(float posX, float posY);
    void selectBoxing(float startPosX, float startPosY, float endPosX, float endPosY);
    void testMoveFirstUnit(const float &posX, const float &posY);

    void Init();
    void free();

private:
    KernelStore gamedata;

    int Current_Unit = 0;
    map_tiles Current_Map;

    Camera camera;
    glm::mat4 model         = glm::mat4(1.0f);
    glm::mat4 view          = glm::mat4(1.0f);
    glm::mat4 projection    = glm::mat4(1.0f);

    Shader TriangleShader;
    Shader GeometryShader;

    MeshObject BoxSelectionVAO;
};


#endif //OPENBROODCRAFT_GAMEENGINE_H
