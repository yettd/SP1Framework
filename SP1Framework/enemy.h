#pragma once
#include "entity.h"
#include "Framework/console.h"
class enemy :
    public entity
{
    static int count;
private:
    int AI;
public:
    enemy();
    void movement(int dir);
    void setRandX();
    void setRandY();
    void getDirfromPlayer(int x,int y);
    void setRandAI();
    int getAI();

};

