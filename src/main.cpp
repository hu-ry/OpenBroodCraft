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
#include "main.h"
#include "globalvar.h"
#include "input/inputAgent.h"


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

    //Create GameEngine
    GameEngine gameprog;
    InputAgent ioagent(window, &gameprog);

    //initialize Input
    initInput(&ioagent);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* Set callback for all the input functions*/
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR);

    // glad loads all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // initialize GameEngine with all the OpenGL stuff
    gameprog.Init();

    // render loop
    while (!glfwWindowShouldClose(window)) {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        /* input goes here */
        processInput(window);

        /* processing game logic happens here */
        gameprog.processGamelogic();

        /* render happens here */
        gameprog.execute();

        // uncomment for frametimes
        //std::cout << "frametime: " << deltaTime << std::endl;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    // deallocate all buffers
    gameprog.free();

    glfwTerminate();
    return 0;
}

