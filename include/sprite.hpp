#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "shader.hpp"

class Sprite{
public:
    unsigned int ID;
    unsigned int image;
    Shader* shader;

    static unsigned int VBO;
    static unsigned int VAO;
    static bool initialized;

    int texWidth, texHeight;

    float x,y;
    float width, height;
    float angle;
    float repeatX=1.0f, repeatY=1.0f;
    
    glm::mat4 model;
    glm::mat4 projection;

    Sprite(float x, float y, unsigned int width, unsigned int height, Shader* shader, const char* imagePath);
    void draw();
    void translate(float x, float y);
    void setLocation(float x, float y);
    void rotate(float angle);
    void setRotation(float angle);
    void updateModel();
    void setWrapping(int axis, int type);
};
#endif

