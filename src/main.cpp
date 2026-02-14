#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "shader.hpp"
#include "stb_image.h"
#include "sprite.hpp"
#include "game.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;

Game* game;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Moj prozor", NULL, NULL);
    int fbW, fbH;
    glfwGetFramebufferSize(window, &fbW, &fbH);
    //std::cout << "Window units: " << WIDTH << "x" << HEIGHT << std::endl;
    //std::cout << "Actual pixels: " << fbW << "x" << fbH << std::endl;
    if(window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;  
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGL(glfwGetProcAddress)){
        std::cout << "Failed to initialize OpenGL context";
        return -1;
    }
    // glViewport(0,0,WIDTH,HEIGHT);
    glViewport(0,0,fbW,fbH);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    game = new Game(WIDTH,HEIGHT);
    // game = new Game(fbW,fbH);

    float deltaTime=0.0f;
    float lastFrame=0.0f;
    while(!glfwWindowShouldClose(window)){
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame-lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        game->processInput(deltaTime);
        game->update(deltaTime);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        game->render();

        glfwSwapBuffers(window);
        
    }

    glfwTerminate();
    return 0;
   
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(key >= 0 && key <= 1024){
        if(action == GLFW_PRESS && game->key_holding[key] == false){
            game->keys[key] = true;
            game->key_holding[key] = true;
        }
        else if(action == GLFW_RELEASE){
            game->keys[key] = false;
            game->key_holding[key] = false;
        }
    }
}
