#include "Rocekt.h"

Rocekt::Rocekt(int x, int y)
{
	timer = 1;
	setCoordX(x);
	setCoordY(y);
}

float Rocekt::getTimer()
{
	return timer;
}

void Rocekt::movement(int dir)
{
}

int Rocekt::getshape(int x, int y)
{
	return Explode[y][x];
}

void Rocekt::setTimer(float t)
{
	timer = t;
}
