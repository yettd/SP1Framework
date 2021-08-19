#pragma once
#include "entity.h"
#include "Framework/console.h"
class enemy :
    public entity
{
    static int count;
private:
    int AI;
    bool wall = false;
    int dx;
    int dy;
public:
    enemy();
    void movement(int dir);
    void setRandX();
    void setRandY();
    int getDirXfromPlayer(int x);
    int getDirYfromPlayer(int y);
    int getAI();
    void setAI();

    int shootDir(int x, int y);

    void AggresiveAI(int x, int y, int cx, int cy);
    void SmartAI(); 
    void DumbAI(int x, int y);

};

