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
    void setRandAI();
    int getAI();
    int setDestination(int x, int y);

};

