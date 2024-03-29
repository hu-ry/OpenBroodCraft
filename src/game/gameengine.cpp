//
// Created by RH on 29/08/2019.
//

#include <game/gameengine.hpp>
#include <game/engine/meshfactory.h>


GameEngine::GameEngine() : TriangleShader(), GeometryShader(), MapShader(),
camera(INITIAL_CAM_POSITION), map_to_draw() {

    //TODO: Write some useful stuff in here pls
    this->gamedata = KernelStore{
        GameControlFlags{false, false,false, false},
                                  Square{glm::vec2(-0.5f,-0.5f),glm::vec2(0.5f,0.5f)},
                                  false,
                                  1};

}

void GameEngine::Init() {
    std::cout << "-----Starting GameEngine Init!-----" << std::endl;
    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // setting up our vertex and fragment shader via Shader class
    this->TriangleShader = Shader("../shaders/testTriShader.vesh",
            "../shaders/testTriShader.frsh");
    this->GeometryShader = Shader("../shaders/testGeoShader.vesh",
            "../shaders/testGeoShader.frsh", "../shaders/testGeoShader.gesh");
    this->MapShader = Shader("../shaders/map_shader.vesh", "../shaders/map_shader.frsh");

    MeshFactory meshMaker("../textures/", "../objectmodels/");

    this->map_to_draw = GameMap("../maps/test_map.json");

    meshMaker.createMapMesh(&map_to_draw);
    this->BoxSelectionVAO = meshMaker.createGeometryMesh();

    std::vector<TextureObject> marine_texture = {TextureObject("../textures/marine_new.png")};

    // set up vertex data (and buffer(s)) and configure vertex attributes
    MeshObject marinetileVAO("../objectmodels/marineTile.vmo", GL_STATIC_DRAW, false, marine_texture);

    this->addUnit(Unit(&marinetileVAO, UNIT_MARINE, glm::vec3(0.0f, 0.0f, 1.0f), ORDER_NONE, 2));




    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    std::cout << "-----FINISHED GameEngine INIT!-----" << std::endl;
}

void GameEngine::execute() {
    std::cout << "-----STARTING GameEngine RENDER!-----" << std::endl;
    /* render happens here */
    glClearColor(0.2f, 0.5f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //    model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
    view          = camera.GetViewMatrix();
    projection    = glm::ortho(-FROSTUM_WIDTH/FROSTUM_ZOOM, FROSTUM_WIDTH/FROSTUM_ZOOM, -FROSTUM_HEIGHT/FROSTUM_ZOOM,
                            FROSTUM_HEIGHT/FROSTUM_ZOOM, FROSTUM_NEAR, FROSTUM_FAR);
    model         = glm::mat4(1.0f);

    // activating our Triangle shader
    TriangleShader.use();
    TriangleShader.setMatrix4fv("model", 1, model);
    TriangleShader.setMatrix4fv("view", 1, view);
    TriangleShader.setMatrix4fv("projection", 1, projection);
 
    // drawing the GameMap
    map_to_draw.draw(&projection, &view, &model, &MapShader);

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
    if(this->gamedata.flags.inBoxSelection) {
        GeometryShader.use();
        GeometryShader.setMatrix4fv("model", 1, model);
        GeometryShader.setMatrix4fv("view", 1, view);
        GeometryShader.setMatrix4fv("projection", 1, projection);
        this->GeometryShader.set2Float("boxPos",
                gamedata.BoxSelectPos.startPos.x, gamedata.BoxSelectPos.startPos.y);
        this->GeometryShader.set2Float("mousePosOffset",
                gamedata.BoxSelectPos.endPos.x, gamedata.BoxSelectPos.endPos.y);
        this->BoxSelectionVAO.drawGeoBox(GeometryShader);
        this->gamedata.flags.inBoxSelection = false;
    }
    std::cout << "-----FINISHED GameEngine RENDER!-----" << std::endl;
}

void GameEngine::processGamelogic() {

    if(this->gamedata.flags.inBoxSelection && this->gamedata.flags.abortBoxSelection) {
        this->gamedata.flags.inBoxSelection = false;
    }
    this->gamedata.flags.abortBoxSelection = true;
}

int GameEngine::addUnit(Unit unit_to_add) {
    this->ActiveUnits[this->Current_Unit] = unit_to_add;
    this->Current_Unit++;
    return this->Current_Unit;
}

void GameEngine::recieveKeyboardInput(float posX, float posY) {

}

void GameEngine::moveCamera(Camera_Movement t_direction) {
    camera.ProcessKeyboard(t_direction, deltaTime);
}

void GameEngine::zoomCamera(const double &t_offset) {
    camera.ProcessScrollInput(t_offset);
}

void GameEngine::moveSelectedUnits(float posX, float posY) {

}

void GameEngine::selectBoxing(float startPosX, float startPosY, float endPosX, float endPosY) {
    this->gamedata.flags.abortBoxSelection = false;
    this->gamedata.flags.inBoxSelection = true;

    startPosX = (startPosX - ((float)SCR_WIDTH / 2)) / ((float)SCR_WIDTH / 2);
    startPosY = (-(startPosY - ((float)SCR_HEIGHT / 2))) / ((float)SCR_HEIGHT / 2);
    endPosX = (endPosX - ((float)SCR_WIDTH / 2)) / ((float)SCR_WIDTH / 2);
    endPosY = (-(endPosY - ((float)SCR_HEIGHT / 2))) / ((float)SCR_HEIGHT / 2);

    std::cout << "startX: " << startPosX << std::endl;
    std::cout << "startY: " << startPosY << std::endl;
    std::cout << "endX: " << endPosX << std::endl;
    std::cout << "endY: " << endPosY << std::endl;

    this->gamedata.BoxSelectPos.startPos = glm::vec2(startPosX, startPosY);
    this->gamedata.BoxSelectPos.endPos = glm::vec2(endPosX, endPosY);
}

void GameEngine::testMoveFirstUnit(const float &posX, const float &posY) {
    this->ActiveUnits[0].issueCmd(COMMAND_MOVE, glm::vec2(camera.Position.x+posX, camera.Position.y+posY));
}

void GameEngine::free() {
    if(this->Current_Unit != 0) {
        for(int i=0;i<=this->Current_Unit;i++) {
            this->ActiveUnits[i].free_mesh();
        }
    }
    this->map_to_draw.deallocateMesh();
    delete[] this->ActiveUnits;
    this->BoxSelectionVAO.deallocateVertexArrays();
    // TexEntities.erase(TexEntities.begin(), TexEntities.end());
    // TexEntities.erase(TexEntities.end());
}