#include "enemy.h"
#include <iostream>


enemy::enemy()
{
	setSym(79);
	setRandX();
	setRandY();
	setAI();
	setspeed(0.075);


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
	}	
	if (disY > 0)
	{
		movement(2);
	}

}

int enemy::getAI()
{
	return AI;
}

void enemy::setAI()
{
	int ran;
	for (int i = 0; i < 5; i++)
	{
		ran = (rand() % 100) + 1;
	}
	if (ran <= 50) AI = 0;
	else if (ran <= 80) AI = 1;
	else AI = 2;
}

