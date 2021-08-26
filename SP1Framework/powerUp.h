#pragma once
#include "entity.h"
class powerUp :
    public entity
{
private:
    int power;
public:
    powerUp(int x, int y, int p);

    int getpower();

    void setpower(int x);

    void movement(int dir);
};

