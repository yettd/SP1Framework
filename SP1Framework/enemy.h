#pragma once
#include "entity.h"
#include "Framework/console.h"
class enemy :
    public entity
{
    static int count;
private:
    int AI;
    bool isAtCircle;
    int smartX, smartY;
    bool chosen;
public:
    enemy();
    void movement(int dir);
    void setRandX();
    void setRandY();
    void getDirfromPlayer(int x,int y);
    int getAI();
    void setAI();
    void goToCircle();
    int chooseCorner();
    void setSmartX(int ran);
    void setSmartY(int ran);
    int getSmartX();
    int getSmartY();
};

