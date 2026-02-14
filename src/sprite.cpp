#include "sprite.hpp"
#include <iostream>
#include "glm/ext/matrix_transform.hpp"
#include "stb_image.h"

unsigned int Sprite::VAO = 0;
unsigned int Sprite::VBO = 0;
bool Sprite::initialized = false;

Sprite::Sprite(float x, float y, unsigned int width, unsigned int height, Shader* shader, const char* imagePath)
    : shader(shader), x(x), y(y), width(width), height(height), angle(0)
{
    if(!initialized){
        glGenVertexArrays(1,&VAO);
        glGenBuffers(1,&VBO);
        float vertices[] = { 
              // pos      // tex
              0.0f, 1.0f, 0.0f, 1.0f,
              1.0f, 0.0f, 1.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 0.0f, 
    
              0.0f, 1.0f, 0.0f, 1.0f,
              1.0f, 1.0f, 1.0f, 1.0f,
              1.0f, 0.0f, 1.0f, 0.0f
          };
    
          glBindVertexArray(VAO);

          glBindBuffer(GL_ARRAY_BUFFER,VBO);
          glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

          glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
          glEnableVertexAttribArray(0);
          initialized = true;
    }

    updateModel();
    
    glGenTextures(1,&image);
    glBindTexture(GL_TEXTURE_2D, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // stbi_set_flip_vertically_on_load(true);
    int  nrChannels;
    unsigned char *data = stbi_load(imagePath, &texWidth, &texHeight, &nrChannels, 0);
    if(data){
        GLenum format = GL_RGB;
        if (nrChannels == 4)
            format = GL_RGBA;
        else if (nrChannels == 3)
            format = GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

}

void Sprite::setWrapping(int axis, int type)
{
    glBindTexture(GL_TEXTURE_2D, image);    
    glTexParameteri(GL_TEXTURE_2D,axis,type);
}

void Sprite::updateModel()
{
    float cx = width/2.0f;
    float cy = height/2.0f;
    
    model = glm::mat4(1.0f);
    model = glm::translate(model,glm::vec3(x,y,0));
    // model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f*width, 0.5f*height, 0.0f));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    // model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));
    model = glm::translate(model, glm::vec3(-0.5f*width, -0.5f*height, 0.0f));
    model = glm::scale(model,glm::vec3(width,height,1));

    shader->use();
    shader->setMatrix4("model", model);
}

void Sprite::draw(){
    shader->use();
    shader->setMatrix4("model",model);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, image);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Sprite::translate(float x, float y){
    this->x += x;
    this->y += y;

    updateModel();
}

void Sprite::setLocation(float x, float y){
    this->x = x;
    this->y = y;

    updateModel();
}

void Sprite::rotate(float angle){
    this->angle += angle;
    updateModel();
}

void Sprite::setRotation(float angle){
    this->angle = angle;
    updateModel();
}
