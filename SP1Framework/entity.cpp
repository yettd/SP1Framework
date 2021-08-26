#include "entity.h"

entity::entity()
{
    FireRate = 0;
    fireCharge = 0;
    m_bActive = false;
    speed = 0;
    sym = ' ';
    tag = 0;
    my = 0;
    mx = 0;
    Location = { 0,0 };
}

int entity::getCoordX()
{
    return Location.X;
}

int entity::getCoordY()
{
    return Location.Y;
}

void entity::setCoordX(int i)
{
    Location.X = i;
}

void entity::setCoordY(int i)
{
    Location.Y = i;
}

void entity::setm_bActive(bool i)
{
    m_bActive = i;
}

bool entity::getm_activr()
{
    return m_bActive;
}

void entity::setSym(char a)
{
    sym = a;
}

char entity::getSym()
{
    return sym;
}

float entity::getSpeed()
{
    return speed;
}

void entity::setspeed(float i)
{
    speed = i;
}


float entity::getFireRate()
{
    return FireRate;
}

void entity::SetFireRate(float i)
{
    FireRate = i;
}
float entity::getFireC()
{
    return fireCharge;
}

void entity::SetFireC(float i)
{
    fireCharge = i;
}

char entity::getTag()
{
    return tag;
}

void entity::setTag(char t)
{
    tag = t;
}
