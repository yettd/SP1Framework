#pragma once
#include "entity.h"
class collision :
    public entity
{
public:
    bool checkCollide(entity* i, entity* l);
};

