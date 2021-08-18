#include "enemy.h"
#include <iostream>


enemy::enemy()
{
	setSym(79);
	setRandX();
	setRandY();

	setspeed(0.1);
	setRandAI();


	mx = 0;
	my = 0;
}

void enemy::movement(int dir)
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

 

void enemy::setRandX()
{
	int randomNumber;
	for (int i = 0; i < 5; i++)
	{
		randomNumber = (rand() % 80) + 1;
	}
	setCoordX(randomNumber);
}

void enemy::setRandY()
{
	int randomNumber;
	for (int i = 0; i < 5; i++)
	{
		randomNumber = (rand() % 25) + 1;
	}
	setCoordY(randomNumber);
}


void enemy::getDirfromPlayer(int x, int y)
{
	int disX = x - getCoordX();
	int disY = y - getCoordY();

	if (disX > 0)
	{
		movement(4);
	}
	if (disX < 0)
	{
		movement(3);
	}
	if (disY < 0)
	{
		movement(1);
	}	if (disY > 0)
	{
		movement(2);
	}

}

