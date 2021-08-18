#include "enemy.h"
#include <iostream>


enemy::enemy()
{
	setSym(79);
	setRandX();
	setRandY();
	setAI();
	setspeed(0.075);
	isAtCircle = false;
	chosen = false;

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
	/*int ran;
	for (int i = 0; i < 5; i++)
	{
		ran = (rand() % 100) + 1;
	}
	if (ran <= 50) AI = 0;
	else if (ran <= 80) AI = 1;
	else AI = 2;*/
	AI = 2;
}

int enemy::chooseCorner()
{
	int ran;
	for (int i = 0; i < 5; i++)
	{
		ran = (rand() % 4) + 1;
	}
	return ran;
}

void enemy::setSmartX(int ran)
{
	//Top left
	if (ran == 1)
	{
		smartX = 16;
	}
	//Top right
	if (ran == 2)
	{
		smartX = 64;
	}
	//Bottom left
	if (ran == 3)
	{
		smartX = 16;
	}
	//Bottom right
	if (ran == 4)
	{
		smartX = 64;
	}
}

void enemy::setSmartY(int ran)
{
	//Top left
	if (ran == 1)
	{
		smartY = 5;
	}
	//Top right
	if (ran == 2)
	{
		smartY = 5;
	}
	//Bottom left
	if (ran == 3)
	{
		smartY = 20;
	}
	//Bottom right
	if (ran == 4)
	{
		smartY = 20;
	}
}

int enemy::getSmartX()
{
	return smartX;
}

int enemy::getSmartY()
{
	return smartY;
}


void enemy::goToCircle()
{
	//64 x 20
	
	if (isAtCircle == false && chosen == false)
	{
		int ran = chooseCorner();
		setSmartX(ran);
		setSmartY(ran);
		chosen == true;
	}
	int distX = getSmartX();
	int distY = getSmartY();

	if (isAtCircle == false)
	{
		if (distX > getCoordX())
		{
			movement(4);
		}
		if (distX < getCoordX())
		{
			movement(3);
		}
		if (distY < getCoordY())
		{
			movement(1);
		}
		if (distY > getCoordY())
		{
			movement(2);
		}
		
	}
	if (getCoordX() == 16 && getCoordY() == 5 && isAtCircle == false) isAtCircle = true;
	else if (getCoordX() == 64 && getCoordY() == 5) isAtCircle = true;
	else if (getCoordX() == 16 && getCoordY() == 20) isAtCircle = true;
	else if (getCoordX() == 64 && getCoordY() == 20) isAtCircle = true;
	

	if (isAtCircle)
	{
		// 1 = up 2 = down 3 = left 4 = right
		//Top left to bottom left
		int dist;
		if (getCoordX() == 16 && getCoordY() != 20)
		{
			dist = getCoordY() - 20;

			if (dist > 0)
			{
				movement(2);
			}
		}
		else if (getCoordX() != 64 && getCoordY() == 20)
		{
			dist = getCoordX() - 64;

			if (dist > 0)
			{
				movement(4);
			}
		}
		else if (getCoordX() == 64 && getCoordY() != 5)
		{
			dist = getCoordY() - 5;

			if (dist > 0)
			{
				movement(1);
			}
		}
		else if (getCoordX() != 16 && getCoordY() == 5)
		{
			dist = getCoordX() - 16;

			if (dist > 0)
			{
				movement(3);
			}
		}
	}
}


