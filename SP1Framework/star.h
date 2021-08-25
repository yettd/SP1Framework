#pragma once
#include "entity.h"
#include <iostream>
class star :
    public entity
{
public:
    star(int x , int y);

    void movement(int dir);
};

