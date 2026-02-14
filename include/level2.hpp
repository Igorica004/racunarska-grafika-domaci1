#ifndef LEVEL2_H
#define LEVEL2_H

#include "stage.hpp"
#include "sprite.hpp"
#include "player.hpp"
#include "framebuffer.hpp"
#include <list>

class Level2: public Stage
{
public:
    Level2(int width, int height, const char* effect_fragment_shader);
    ~Level2();

    bool start;
    bool collision;
    bool changeLevel;
    Stage* level;
    float width, height;

    Shader* shader;
    Shader* effectShader;
    unsigned int texture;

    unsigned int VAO,VBO;
    std::list<std::pair<Sprite,Sprite>>::iterator ite;   
    std::list<Sprite> backgrounds;
    std::list<std::pair<Sprite,Sprite>> pipes;
    float background_position=0;
    float pipe_position=0;
    Player player;
    unsigned int framebuffer;
    Framebuffer buffer1,buffer2;
    
    void processInput(float dt, int keys[]) override;
    Stage* update(float dt) override;
    void render() override;  

    void generatePipes(int n);
    bool checkCollision();
    
};

#endif
