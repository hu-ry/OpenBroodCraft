//
// Created by Guest on 29/08/2019.
//

#include "gameengine.h"
#include "../main.h"


GameEngine::GameEngine() : TriangleShader() {

    //TODO: Write some useful stuff in here pls


}

void GameEngine::Init() {

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // setting up our vertex and fragment shader via Shader class
    this->TriangleShader = Shader("../shaders/testTriShader.vesh", "../shaders/testTriShader.frsh");

    TextureObject maptile_texture = TextureObject("../textures/ownTile.png");
    TextureObject marine_texture = TextureObject("../textures/marine_new.png");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    MeshObject maptileVAOtest("../objectmodels/testTile.vmo", GL_FLOAT, GL_ARRAY_BUFFER, GL_STATIC_DRAW, maptile_texture);
    MeshObject marinetileVAO("../objectmodels/marineTile.vmo", GL_FLOAT, GL_ARRAY_BUFFER, GL_STATIC_DRAW, marine_texture);

    this->addUnit(Unit(&marinetileVAO, UNIT_MARINE, glm::vec3(0.0f, 0.0f, 1.0f),
                       Command(), 2));

    map_tiles map(64, 64, maptileVAOtest);
    this->loadMap(map);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void GameEngine::Execute() {
    /* render happens here */
    glClearColor(0.2f, 0.5f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw our first triangle
    TriangleShader.use();

    // make sure to initialize matrix to identity matrix first
    model         = glm::mat4(1.0f);
    view          = glm::mat4(1.0f);
    projection    = glm::mat4(1.0f);

    //    model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
    view = Camera.GetViewMatrix();
    projection = glm::ortho(-FROSTUM_WIDTH/FROSTUM_ZOOM, FROSTUM_WIDTH/FROSTUM_ZOOM, -FROSTUM_HEIGHT/FROSTUM_ZOOM,
                            FROSTUM_HEIGHT/FROSTUM_ZOOM, FROSTUM_NEAR, FROSTUM_FAR);


    TriangleShader.setMatrix4fv("model", 1, model);
    TriangleShader.setMatrix4fv("view", 1, view);
    TriangleShader.setMatrix4fv("projection", 1, projection);

    // drawing the map
    Current_Map.draw_map(&model, &TriangleShader);

    // drawing all TexEntities
    if(this->Current_Unit != 0) {

        for(int i=0;i<this->Current_Unit;i++) {
            this->ActiveUnits[i].Run();
            model = glm::translate(model ,this->ActiveUnits[i].translate);
            this->TriangleShader.setMatrix4fv("model", 1, model);
            this->ActiveUnits[i].drawAction(&TriangleShader);
        }
    }

    // drawing UI Effects

}

void GameEngine::Process_Gamelogic() {

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

void GameEngine::selectBoxing(int startPosX, int startPosY, int endPosX, int endPosY) {

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
    // TexEntities.erase(TexEntities.begin(), TexEntities.end());
    // TexEntities.erase(TexEntities.end());
}