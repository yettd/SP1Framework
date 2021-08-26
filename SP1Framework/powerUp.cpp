#include "powerUp.h"

powerUp::powerUp(int x,int y,int p)
{
    setCoordX(x);
    setCoordY(y);
    setpower(p);
    setTag('U');
    if (p == 1)
    {
        setSym('T');
    }
    else
    {
        setSym('R');
    }
}

int powerUp::getpower()
{
    return power;
}

void powerUp::setpower(int x)
{
    power = x;
}

void powerUp::movement(int dir)
{
}
