//
// Created by Guest on 29/08/2019.
//

#include "gameengine.h"
#include "../main.h"
#include "map/GameMap.h"


GameEngine::GameEngine() : TriangleShader(), GeometryShader() {

    //TODO: Write some useful stuff in here pls
    this->GameData = KernelStore{
        GameControlFlags{false, false,false, false},
                                  Square{glm::vec2(-0.5f,-0.5f),glm::vec2(0.5f,0.5f)},
                                  false,
                                  1};

}

void GameEngine::Init() {

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // setting up our vertex and fragment shader via Shader class
    this->TriangleShader = Shader("../shaders/testTriShader.vesh",
            "../shaders/testTriShader.frsh");
    this->GeometryShader = Shader("../shaders/testGeoShader.vesh",
            "../shaders/testGeoShader.frsh", "../shaders/testGeoShader.gesh");

    std::vector<TextureObject> maptile_texture = {TextureObject("../textures/maptiles/64px_cobblestone_tile.png")};
    std::vector<TextureObject> marine_texture = {TextureObject("../textures/marine_new.png")};

    // set up vertex data (and buffer(s)) and configure vertex attributes
    MeshObject maptileVAOtest("../objectmodels/testTile.vmo", GL_STATIC_DRAW, false, maptile_texture);
    this->BoxSelectionVAO = MeshObject(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    MeshObject marinetileVAO("../objectmodels/marineTile.vmo", GL_STATIC_DRAW, false, marine_texture);

    this->addUnit(Unit(&marinetileVAO, UNIT_MARINE, glm::vec3(0.0f, 0.0f, 1.0f),
                       Command(), 2));

    GameMap testingGameMap("../maps/test_map.json");

    map_tiles map(64, 64, maptileVAOtest);
    this->loadMap(map);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void GameEngine::Execute() {
    /* render happens here */
    glClearColor(0.2f, 0.5f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //    model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
    view          = Camera.GetViewMatrix();
    projection    = glm::ortho(-FROSTUM_WIDTH/FROSTUM_ZOOM, FROSTUM_WIDTH/FROSTUM_ZOOM, -FROSTUM_HEIGHT/FROSTUM_ZOOM,
                            FROSTUM_HEIGHT/FROSTUM_ZOOM, FROSTUM_NEAR, FROSTUM_FAR);
    model         = glm::mat4(1.0f);

    // activating our Triangle shader
    TriangleShader.use();
    TriangleShader.setMatrix4fv("model", 1, model);
    TriangleShader.setMatrix4fv("view", 1, view);
    TriangleShader.setMatrix4fv("projection", 1, projection);
 
    // drawing the GameMap
    Current_Map.draw_map(&model, &TriangleShader);
 
    // drawing all TexEntities
    if(this->Current_Unit != 0) {
 
        for(int i=0;i<this->Current_Unit;i++) {
            this->ActiveUnits[i].Run();
            model = glm::translate(model ,this->ActiveUnits[i].translate);
            this->TriangleShader.setMatrix4fv("model", 1, model);
            this->ActiveUnits[i].drawAction(&TriangleShader);
            model = glm::mat4(1.0f);
        }
    }
    model = glm::mat4(1.0f);

    // drawing UI Effects
    if(this->GameData.flags.inBoxSelection) {
        GeometryShader.use();
        GeometryShader.setMatrix4fv("model", 1, model);
        GeometryShader.setMatrix4fv("view", 1, view);
        GeometryShader.setMatrix4fv("projection", 1, projection);
        this->GeometryShader.set2Float("boxPos",
                GameData.BoxSelectPos.startPos.x, GameData.BoxSelectPos.startPos.y);
        this->GeometryShader.set2Float("mousePosOffset",
                GameData.BoxSelectPos.endPos.x, GameData.BoxSelectPos.endPos.y);
        this->BoxSelectionVAO.drawGeoBox(GeometryShader);
        this->GameData.flags.inBoxSelection = false;
    }
}

void GameEngine::Process_Gamelogic() {

    if(this->GameData.flags.inBoxSelection && this->GameData.flags.abortBoxSelection) {
        this->GameData.flags.inBoxSelection = false;
    }
    this->GameData.flags.abortBoxSelection = true;
}

int GameEngine::addUnit(Unit unit_to_add) {
    this->ActiveUnits[this->Current_Unit] = unit_to_add;
    this->Current_Unit++;
    return this->Current_Unit;
}

void GameEngine::recieveInput(float posX, float posY) {

}

void GameEngine::moveSelectedUnits(float posX, float posY) {

}

void GameEngine::selectBoxing(float startPosX, float startPosY, float endPosX, float endPosY) {
    this->GameData.flags.abortBoxSelection = false;
    this->GameData.flags.inBoxSelection = true;
    std::cout << "startX: " << startPosX << std::endl;
    std::cout << "startY: " << startPosY << std::endl;
    std::cout << "endX: " << endPosX << std::endl;
    std::cout << "endY: " << endPosY << std::endl;

    this->GameData.BoxSelectPos.startPos = glm::vec2(startPosX, startPosY);
    this->GameData.BoxSelectPos.endPos = glm::vec2(endPosX, endPosY);
}

void GameEngine::testMoveFirstUnit(float posX, float posY) {
    this->ActiveUnits[0].issueCmd(COMMAND_MOVE, glm::vec2(posX, posY));
}

void GameEngine::loadMap(map_tiles map) {
    this->Current_Map = map;
}

void GameEngine::free() {
    if(this->Current_Unit != 0) {
        for(int i=0;i<=this->Current_Unit;i++) {
            this->ActiveUnits[i].free_mesh();
        }
    }
    this->Current_Map.mesh.deallocateVertexArrays();
    delete[] this->ActiveUnits;
    this->BoxSelectionVAO.deallocateVertexArrays();
    // TexEntities.erase(TexEntities.begin(), TexEntities.end());
    // TexEntities.erase(TexEntities.end());
}