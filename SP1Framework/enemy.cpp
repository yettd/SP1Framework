#include "enemy.h"
#include <iostream>


enemy::enemy()
{
	setSym(79);
	setRandX();
	setRandY();
	setRandAI();
	setspeed(1);
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

void enemy::setRandAI()
{
	// Dumb = 0
	// Agressive = 1
	// Smart = 2
	/*int randomNumber;
	for (int i = 0; i < 5; i++)
	{
		randomNumber = (rand() % 100) + 1;
	}
	if (randomNumber <= 50) AI = 0;
	else if (randomNumber <= 80) AI = 1;
	else AI = 2;*/
	AI = 0;
}

int enemy::getAI()
{
	return AI;
}

int enemy::setDestination(int x, int y)
{
	int finalX, finalY;
	// return dir for movement
	// 1 = up 2 = down 3 = left 4 = right

	finalX = x - getCoordX();
	finalY = y - getCoordY();

	if (finalX > 0)
	{
		//Player to the right of enemy
		if (finalY > 0)
		{
			//Player below enemy
			if (finalX > finalY) return 2;
			else return 4;
		}
		else if (finalY < 0)
		{
			//Player above enemy
			finalY *= -1;
			if (finalX > finalY) return 1;
			else return 4;
		}
	}
	else if (finalX < 0)
	{
		//Player to the left of enemy
		finalX *= -1;
		if (finalY > 0)
		{
			//Player below enemy
			if (finalX > finalY) return 2;
			else return 3;
		}
		else if (finalY < 0)
		{
			//Player above enemy
			finalY *= -1;
			if (finalX > finalY) return 1;
			else return 3;
		}
	}
}

