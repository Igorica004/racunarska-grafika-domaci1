#ifndef LEVEL4_H
#define LEVEL4_H

#include "stage.hpp"
#include "sprite.hpp"
#include "player.hpp"
#include "framebuffer.hpp"
#include <list>

class Level4: public Stage
{
public:
    Level4(int width, int height, const char* effect_fragment_shader);
    ~Level4();

    bool start;
    bool collision;
    bool changeLevel;
    Stage* level;
    float width, height;

    Shader* shader;
    Shader* effectShader;
    Shader effectShader2;
    Shader effectShader3;
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
