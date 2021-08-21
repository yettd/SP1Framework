#pragma once
#include "entity.h"
#include "Framework/console.h"
class enemy :
    public entity
{
    
private:
    int AI;
    bool wall;
    int LR;
    int dx;
    int dy;
public:
    enemy();
    void movement(int dir);
    void setCoord();
    void setRandX();
    void setRandY();
    int getDirXfromPlayer(int x);
    int getDirYfromPlayer(int y);
    int getAI();
    void setAI();

    int shootDir(int x, int y);

    void AggresiveAI(int x, int y, int cx, int cy);
    void SmartAI(int cx, int cy);
    void DumbAI(int x, int y);

};

