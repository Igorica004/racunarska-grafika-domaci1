#ifndef GAME_H
#define GAME_H

#include "sprite.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "stage.hpp"
#include "level1.hpp"

class Game{
public:
    int width, height;
    Stage* stage;
    int keys[1024]={false};
    int key_holding[1024]={false};
    
    Game(int screenWidth, int screenHeight);
    void processInput(float dt);
    void update(float dt);    
    void render();
};

#endif
