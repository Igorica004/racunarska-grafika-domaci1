#include "player.hpp"
#include <algorithm>

Player::Player(float x, float y, Shader* shader):
    x(x),
    y(y),
    sprite(x,y,80,80,shader,"sprites/annoyingdog.png"),
    rotation(0),
    force(0,0)
{
}

void Player::jump(float dt)
{
    force.y = 1000.0f;
}
void Player::applyForce(float dt, float speed)
{
    float gravity = 2600;
    float rotationRate = 180*dt;
    force.y = std::max(-500.0f, force.y-gravity*dt);
    if(force.y < 0)
        rotation = std::min(45.0f,rotation + rotationRate);
    else
        rotation = std::max(0.0f,rotation - rotationRate);
    x += speed;
    y -= force.y*dt;
    sprite.setLocation(x, y);
    sprite.setRotation(rotation);

}
void Player::draw()
{
    sprite.draw();    
}
