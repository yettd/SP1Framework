#pragma once
#include "entity.h"
#include "Framework/console.h"
class enemy :
    public entity
{
    static int count;
public:
    enemy();
    void movement(int dir);
    void setRandX();
    void setRandY();

};

