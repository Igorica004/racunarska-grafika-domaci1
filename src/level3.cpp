#include "level1.hpp"
#include "level2.hpp"
#include "level3.hpp"
#include "level4.hpp"
#include "GLFW/glfw3.h"
#include "shader.hpp"
#include "framebuffer.hpp"

Level3::Level3(int width, int height, const char* effect_fragment_shader):
    width(width),
    height(height),
    start(false),
    collision(false),
    changeLevel(false),
    shader(new Shader(width,height,"src/shaders/sprite_vertex.glsl","src/shaders/fragment.glsl")),
    effectShader(new Shader(width,height,"src/shaders/vertex.glsl",effect_fragment_shader)),
    player(Player((1.0f*width-100)/2,(1.0f*height-100)/2,shader)),
    level(nullptr),
    buffer1(width,height),
    buffer2(width,height)
{
    generatePipes(5);
    for(int i=0; i<2; i++){
        Sprite sprite(background_position,0,width,height,shader,"sprites/background.png");
        backgrounds.push_back(sprite);
        background_position+=width;
    }
    ite = pipes.begin();

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    float vertices[] = { 
        // positions   // texCoords
        -1.0f,  1.0f,   0.0f, 1.0f,
        -1.0f, -1.0f,   0.0f, 0.0f,
         1.0f, -1.0f,   1.0f, 0.0f,

        -1.0f,  1.0f,   0.0f, 1.0f,
         1.0f, -1.0f,   1.0f, 0.0f,
         1.0f,  1.0f,   1.0f, 1.0f
    };
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}
Level3::~Level3()
{
    free(shader);
    free(effectShader);
}

void Level3::processInput(float dt, int keys[])
{
    if(keys[GLFW_KEY_SPACE]){
        start = true;
        player.jump(dt);
        keys[GLFW_KEY_SPACE] = false;
    }
    if(keys[GLFW_KEY_1]){
        level = new Level1(width,height,"src/shaders/fragment.glsl");
        changeLevel = true;
        keys[GLFW_KEY_1] = false;
    }
    if(keys[GLFW_KEY_2]){
       level = new Level1(width,height,"src/shaders/sin_fragment.glsl"); 
       changeLevel = true;
        keys[GLFW_KEY_2] = false;
    }
    if(keys[GLFW_KEY_3]){
        level = new Level2(width,height,"src/shaders/blur_fragment.glsl");
        changeLevel = true;
        keys[GLFW_KEY_3] = false;
    }
    if(keys[GLFW_KEY_4]){
        level = new Level3(width,height,"src/shaders/rainbow_fragment.glsl");
        changeLevel = true;
        keys[GLFW_KEY_4] = false;
    }
    if(keys[GLFW_KEY_5]){
        level = new Level4(width,height,"src/shaders/blur_fragment.glsl");
        changeLevel = true;
        keys[GLFW_KEY_5] = false;
    }
}
Stage* Level3::update(float dt)
{
    if(changeLevel)
        return level;
    if(!start || collision)
        return nullptr;
    while (!backgrounds.empty() && backgrounds.front().x + backgrounds.front().width < player.x - width){
        backgrounds.pop_front();
    }
    float speed = 450*dt;
    for(Sprite& bg:backgrounds){
        bg.translate(200*dt, 0);
    }
    background_position += 200*dt;
    shader->moveCamera(speed, 0);
    player.applyForce(dt,speed);
    if(checkCollision())
        collision = true;
    if(player.x > background_position - 2*width){
        Sprite sprite(background_position,0,width,height,shader,"sprites/background.png");
        backgrounds.push_back(sprite);
        background_position+=width-1;
    }
    if(player.x > pipe_position-2*width){
        float gap=350;
        float pipeWidth=100;
        for(int i=0; i<4; i++){
            float minGapHeight = gap/2+50;
            float maxGapHeight = height-gap/2-50;
            float gapHeight = minGapHeight + rand() % static_cast<int>(maxGapHeight - minGapHeight);

            Sprite bottomPipe(pipe_position, gapHeight+gap/2, pipeWidth, 2000,shader,"sprites/bottomPipeLong.png");
            bottomPipe.setWrapping(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            Sprite topPipe(pipe_position, -2000, pipeWidth, 2000+gapHeight-gap/2,shader,"sprites/topPipeLong.png");
            topPipe.setWrapping(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

            pipes.push_back({bottomPipe, topPipe});
            pipe_position+=500;
        }
    }
    return nullptr;

}
void Level3::render()
{
    buffer1.bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(Sprite& background:backgrounds){
        background.draw();
    }
    player.draw();
    for(std::pair<Sprite,Sprite>& pipe: pipes){
        pipe.first.draw();
        pipe.second.draw();
    }

    effectShader->use();
    effectShader->setFloat("time",player.x);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    int actualWinW, actualWinH;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &actualWinW, &actualWinH);
    // std::cout << actualWinW << " " << actualWinH;
    glViewport(0, 0, actualWinW, actualWinH);
    buffer1.draw();
}


void Level3::generatePipes(int n)
{
    srand(time(0));
    pipe_position=1200;
    float gap=350;
    float pipeWidth=100;
    for(int i=0; i<n; i++){
        float minGapHeight = gap/2+50;
        float maxGapHeight = height-gap/2-50;
        float gapHeight = minGapHeight + rand() % static_cast<int>(maxGapHeight - minGapHeight);

        Sprite bottomPipe(pipe_position, gapHeight+gap/2, pipeWidth, 2000,shader,"sprites/bottomPipeLong.png");
        bottomPipe.setWrapping(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        Sprite topPipe(pipe_position, -2000, pipeWidth, 2000+gapHeight-gap/2,shader,"sprites/topPipeLong.png");
        topPipe.setWrapping(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

        pipes.push_back({bottomPipe, topPipe});
        pipe_position+=500;
    }
}
bool Level3::checkCollision()
{

    while(!pipes.empty() && pipes.front().first.x + pipes.front().first.width * 2*width < player.x)
        pipes.pop_front();
    while(ite != pipes.end() && ite->first.x+ite->first.width < player.x)
        ite = next(ite);
    if(pipes.empty())
        return false;

    auto testOBBvsAABB = [&](Sprite& a, float angleDeg, Sprite& b){
        float ax = a.x;
        float ay = a.y;
        float aw = a.width;
        float ah = a.height;

        float bx = b.x;
        float by = b.y;
        float bw = b.width;
        float bh = b.height;

        float Bx[4] = {bx, bx+bw, bx+bw, bx};
        float By[4] = {by, by,   by+bh, by+bh};

        float cx = ax + aw/2.0f;
        float cy = ay + ah/2.0f;

        float rad = angleDeg * 3.14159265f / 180.0f;
        float cs = cos(rad);
        float sn = sin(rad);

        float Ax[4];
        float Ay[4];

        float lx[4] = {+aw/2, +aw/2, -aw/2, -aw/2};
        float ly[4] = {+ah/2, -ah/2, -ah/2, +ah/2};

        for(int k=0;k<4;k++){
            float rx = lx[k]*cs - ly[k]*sn;
            float ry = lx[k]*sn + ly[k]*cs;
            Ax[k] = cx + rx;
            Ay[k] = cy + ry;
        }

        float axesX[4] = {
            1, 0,
            Ax[1] - Ax[0],
            Ax[3] - Ax[0]
        };
        float axesY[4] = {
            0, 1,
            Ay[1] - Ay[0],
            Ay[3] - Ay[0]
        };

        for(int k=2;k<4;k++){
            float len = sqrt(axesX[k]*axesX[k] + axesY[k]*axesY[k]);
            if(len > 0){
                axesX[k] /= len;
                axesY[k] /= len;
            }
        }

        for(int a_i=0; a_i<4; a_i++){
            float axx = axesX[a_i];
            float axy = axesY[a_i];

            float minA = Ax[0]*axx + Ay[0]*axy;
            float maxA = minA;
            for(int t=1;t<4;t++){
                float p = Ax[t]*axx + Ay[t]*axy;
                if(p < minA) minA = p;
                if(p > maxA) maxA = p;
            }

            float minB = Bx[0]*axx + By[0]*axy;
            float maxB = minB;
            for(int t=1;t<4;t++){
                float p = Bx[t]*axx + By[t]*axy;
                if(p < minB) minB = p;
                if(p > maxB) maxB = p;
            }

            if(maxA < minB || maxB < minA)
                return false;
        }

        return true;
    };

    if(testOBBvsAABB(player.sprite, player.rotation, ite->first)) return true;
    if(testOBBvsAABB(player.sprite, player.rotation, ite->second)) return true;

    return false;
}
