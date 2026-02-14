#ifndef PLAYER_H
#define PLAYER_H
#include "glm/glm.hpp"
#include "sprite.hpp"


class Player{
public: 
    float x,y;
    float rotation;
    glm::vec2 force; 
    Sprite sprite;

    Player(float x, float y, Shader* shader);
    void jump(float dt);
    void applyForce(float dt, float speed);
    void draw();
};


#endif
