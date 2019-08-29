//
// Created by RH on 16.08.2019.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "libs/stb_image.h"
#include "shader_vf.h"
#include "main.h"
#include "TextureObject.h"
#include "globalVar.h"
#include "game/map_tiles.h"
#include "game/Unit.h"


int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // creating the glfw window
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenBroodCraft", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //initialize Mouse Input
    initMouse(&Camera, &lastX, &lastY, &firstMouse);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSetCursorPosCallback(window, cursor_position_callback);
    //---- uncomment to enable camera pitch and yaw for mousemovement ------
    //glfwSetCursorPosCallback(window, msInput.mouse_callback);
    //----------------------------------------------------------------------

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR);

    // glad loads all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // setting up our vertex and fragment shader via Shader class
    Shader testTriShader("../shaders/testTriShader.vesh", "../shaders/testTriShader.frsh");

    TextureObject textObj1 = TextureObject("../textures/FeelsWeirdMan.png");
    TextureObject textObj2 = TextureObject("../textures/ownTile.png");
    TextureObject marine_texture = TextureObject("../textures/marine_new.png");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    //MeshObject cubeVAOtest("../objectmodels/testCube.vmo", GL_FLOAT, GL_ARRAY_BUFFER, GL_STATIC_DRAW, textObj1);

    MeshObject maptileVAOtest("../objectmodels/testTile.vmo", GL_FLOAT, GL_ARRAY_BUFFER, GL_STATIC_DRAW, textObj2);
    MeshObject marinetileVAO("../objectmodels/marineTile.vmo", GL_FLOAT, GL_ARRAY_BUFFER, GL_STATIC_DRAW, marine_texture);

    Unit marine = Unit(&marinetileVAO, UNIT_MARINE, glm::vec3(0.0f, 0.0f, 1.0f), 1);

    map_tiles map(64, 64);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    std::cout <<  ((180-(180/5*2))/3) * sizeof(glm::vec3) << std::endl;
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        /* input goes here */
        processInput(window);

        /* render happens here */
        glClearColor(0.2f, 0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw our first triangle
        testTriShader.use();

        // make sure to initialize matrix to identity matrix first
        glm::mat4 model         = glm::mat4(1.0f);
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);

    //    model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
        view = Camera.GetViewMatrix();
        projection = glm::ortho(-FROSTUM_WIDTH/FROSTUM_ZOOM, FROSTUM_WIDTH/FROSTUM_ZOOM, -FROSTUM_HEIGHT/FROSTUM_ZOOM,
                FROSTUM_HEIGHT/FROSTUM_ZOOM, FROSTUM_NEAR, FROSTUM_FAR);
    //    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        testTriShader.setMatrix4fv("model", 1, model);
        testTriShader.setMatrix4fv("view", 1, view);
        testTriShader.setMatrix4fv("projection", 1, projection);


        map.draw_map(&model, &testTriShader, &maptileVAOtest);



        marinetileVAO.draw(testTriShader);




        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    // deallocate all buffers
    //cubeVAOtest.deallocateVertexArrays();
    maptileVAOtest.deallocateVertexArrays();

    glfwTerminate();
    return 0;
}