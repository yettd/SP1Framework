#include "enemy.h"
#include <iostream>


enemy::enemy()
{
	setRandX();
	setRandY();
	setAI();
	setTag('E');
	setm_bActive(false);
	SetFireRate(1);
	SetFireC(0);
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
	randomNumber = (rand() % 80) + 1;

	setCoordX(randomNumber);
}

void enemy::setRandY()
{
	int randomNumber;
	randomNumber = (rand() % 25) + 1;
	setCoordY(randomNumber);
}

void enemy::AggresiveAI(int x, int y,int cx,int cy)
{
	setSym('A');
	if (wall == false)
	{
		//move stright
		if (dx > 0)
		{
			movement(4);
		}
		if (dx < 0)
		{
			movement(3);
		}
		if (dy < 0)
		{
			movement(1);
		}
		if (dy > 0)
		{
			movement(2);
		}
		if (getCoordX() <= 0 || getCoordX() >= cx || getCoordY() <= 0 || getCoordY() >= cy)
		{
			wall = true;
		}
	}

	if (wall == true)
	{
		//bouce
		dx = getDirXfromPlayer(x);
		dy = getDirYfromPlayer(y);
		wall = false;
	}
}

void enemy::SmartAI()
{
}

void enemy::DumbAI(int x, int y)
{
	setSym('D');
	 dx = getDirXfromPlayer(x);
	 dy = getDirYfromPlayer(y);
	if (dx > 0)
	{
		movement(4);
	}
	if (dx < 0)
	{
		movement(3);
	}
	if (dy < 0)
	{
		movement(1);
	}
	if (dy > 0)
	{
		movement(2);
	}

}

int enemy::shootDir(int x, int y)
{
	int disX = x - getCoordX();
	int disY = y - getCoordY();
	int face = 0;
	if (disX>0)
	{
		face += 3;
	}
	else if (disX < 0)
	{
		face -= 3;
	}
	if (disY > 0)
	{
		face -= 1;
	}
	else if (disY < 0)
	{
		face += 1;
	}
	
	return face;

}


int enemy::getDirXfromPlayer(int x)//dumbAI
{
	int disX = x - getCoordX();
	return disX;
}
int enemy::getDirYfromPlayer(int y)//dumbAI
{
	int disY = y - getCoordY();
	return disY;
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
	//AI = 1;
}

