#include "boss.h"

boss::boss(COORD cord)
{
	hp = 10;
	setTag('B');
	int face = 0;
	setCoordX(cord.X/2);
	setCoordY(cord.Y/4);
	//setm_bActive(false);
	//SetFireRate(1);
	//SetFireC(0);
	//setspeed(0.075);

}

int boss::getshape(int x, int y)
{
	return shape[6][y][x];
}
COORD boss::getCord()
{
	return c;
}
void boss::movement(int dir)
{
	if (dir == 1)
	{
		if (my > 0)
		{
			my = -1;
		}

		my -= getSpeed();
		if (ceil(my) <= -1)
		{
			setCoordY(getCoordY() - 1);
			my = 0;
		}
	}
	if (dir == 2)
	{
		if (my < 0)
		{
			my = 1;
		}
		my += getSpeed();
		if (floor(my) >= 1)
		{
			//Beep(1440, 30);
			setCoordY(getCoordY() + 1);
			my = 0;
		}
	}
	if (dir == 3)
	{
		if (mx > 0)
		{
			mx = -1;
		}
		mx -= getSpeed();
		if (ceill(mx) <= -1)
		{
			//Beep(1440, 30);
			setCoordX(getCoordX() - 1);
			mx = 0;
		}
	}
	if (dir == 4)
	{
		if (mx < 0)
		{
			mx = 1;
		}
		mx += getSpeed();
		if (floor(mx) >= 1)
		{
			//Beep(1440, 30);
			setCoordX(getCoordX() + 1);
			mx = 0;
		}
	}
}

int boss::getDirXfromPlayer(int x)
{
	int disX = x - getCoordX();
	return disX;
}
int boss::getDirYfromPlayer(int y)
{
	int disY = y - getCoordY();
	return disY;
}
