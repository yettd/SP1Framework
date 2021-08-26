#pragma once
#include "entity.h"
class Rocekt :
    public entity
{
private:
    int Explode[5][5]= {
		{0,1,1,1,0},
		{1,1,1,1,1},
		{1,1,1,1,1},
		{1,1,1,1,1},
		{0,1,1,1,0}
	};
	float timer;
public:
    Rocekt(int x,int y);

	float getTimer();
	void movement(int dir);
	int getshape(int x, int y);

	void setTimer(float t);
};

