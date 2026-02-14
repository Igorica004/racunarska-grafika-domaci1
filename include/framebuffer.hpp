#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "glad/gl.h"
#include "GLFW/glfw3.h"

class Framebuffer
{
public:
    unsigned int ID;
    unsigned int texture;    
    unsigned int VAO;
    int width, height;
    Framebuffer(int width, int height);
    void bind();
    void draw();
    void unbind();
};

#endif
