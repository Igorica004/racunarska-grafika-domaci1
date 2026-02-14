#include "game.hpp"
#include <cstddef>

Game::Game(int screenWidth, int screenHeight): width(screenWidth), height(screenHeight)
{
    stage = new Level1(screenWidth,screenHeight,"src/shaders/fragment.glsl");
}

void Game::update(float dt) {
    Stage* res = stage->update(dt);
    if(res != nullptr){
        free(stage);
        stage = res;
        render();
    }
}

void Game::render()
{
    stage->render();
}

void Game::processInput(float dt)
{
    stage->processInput(dt, keys);
}
