#ifndef STAGE_H
#define STAGE_H

class Stage{
public:
    virtual void processInput(float dt, int keys[]){}
    virtual Stage* update(float dt){return nullptr;}
    virtual void render(){}
};

#endif
