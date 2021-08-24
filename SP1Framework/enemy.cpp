#include "enemy.h"
#include <iostream>


enemy::enemy()
{
	setAI();
	setTag('E');
	setm_bActive(false);
	SetFireRate(1);
	SetFireC(0);
	setspeed(0.075);
	setCoord();

	wall = false;
	dy = 0;
	dx = 0;

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

void enemy::setCoord()
{
	int randomNumber;
	randomNumber = (rand() % 4) + 1;

	//Top Wall
	if (randomNumber == 1)
	{
		setRandX();
		setCoordY(1);
	}
	//Bottom Wall
	else if (randomNumber == 2)
	{
		setRandX();
		setCoordY(24);
	}
	else if (randomNumber == 3)
	{
		setRandY();
		setCoordX(1);
	}
	else if (randomNumber == 4)
	{
		setRandY();
		setCoordX(79);
	}


}
void enemy::setRandX()
{
	int randomNumber;
	randomNumber = (rand() % 79) + 1;
	setCoordX(randomNumber);
}

void enemy::setRandY()
{
	int randomNumber;
	randomNumber = (rand() % 24) + 1;
	setCoordY(randomNumber);
}

void enemy::AggresiveAI(int x, int y,int cx,int cy)
{
	setSym('A');
	if (dx == 0 && dy == 0)
	{
		dx = getDirXfromPlayer(x);
		dy = getDirYfromPlayer(y);
	}
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
		if (getCoordX() <= 0 || getCoordX() >= cx || getCoordY() <= 1 || getCoordY() >= cy)
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

void enemy::SmartAI(int cx, int cy)
{
	setSym('S');
	if (wall == false)
	{
		//get closest wall
		//get centerpoint for both
		float halfCX = cx / 2;
		float halfCY = cy / 2;
		if (dx == 0 && dy == 0)
		{
			dy = halfCY - getCoordY();
			dx = halfCX - getCoordX();
		}

		if (fabs(dy) > fabs(dx))
		{
			if (dx < halfCX)
			{
				movement(3);
			}
			else
			{
				movement(4);
			}
		}
		else
		{
			if (dy < halfCY)
			{
				movement(1);
			}
			else
			{
				movement(2);
			}
		}
		if (getCoordX() <= 0 || getCoordX() >= cx || getCoordY() >= cy || getCoordY() <= 1)
		{
			wall = true;
		}
	}
	else
	{
		if (getCoordX() == 0 )
		{
			//most left
			if (LR == 1)
			{
				movement(1);
			}
			else
			{
				movement(2);
			}
		}
		else if (getCoordX() == cx)
		{
			//most right
			if (LR == 1)
			{
				movement(2);
			}
			else
			{
				movement(1);
			}
		}
		if (getCoordY() == 1)
		{
			//most up
			if (LR == 1)
			{
				movement(4);
			}
			else
			{
				movement(3);
			}
		}
		else if (getCoordY() == cy)
		{
			//most down
			if (LR == 1)
			{
				movement(3);
			}
			else
			{
				movement(4);
			}
		}
	}
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


int enemy::getDirXfromPlayer(int x)
{
	int disX = x - getCoordX();
	return disX;
}
int enemy::getDirYfromPlayer(int y)
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
	if (ran <= 40)
	{
		//Dumb
		AI = 0;
		setspeed(0.05);
	}
	else if (ran <= 80)
	{
		//Smart
		AI = 2;
		LR = rand() % 2 + 1; 
	}
	else
	{
		//Aggressive
		AI = 1;
		setspeed(0.015);
		SetFireRate(0.2);
	}
	

}
