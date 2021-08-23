#include "boss.h"

boss::boss(COORD cord)
{
	hp = 10;
	bossFace = 0;
	setTag('B');
	int face = 0;
	setCoordX(cord.X/2);
	setCoordY(cord.Y/4);
	my = 0;
	mx = 0;
	//setm_bActive(false);
	//SetFireRate(1);
	//SetFireC(0);
	setspeed(0.075);

}

int boss::getshape(int x, int y)
{
	return shape[bossFace][y][x];
}
COORD boss::getCord()
{
	return c;
}
bool boss::getWall(COORD wall)
{
	COORD SideToLook={0,0};
	if (bossFace == 0)
	{

		SideToLook.X = getCoordX();
		SideToLook.Y = getCoordY() - 2;
		
	}
	else if (bossFace == 1)
	{

		SideToLook.X = getCoordX();
		SideToLook.Y = getCoordY() + 2;

	}
	else if (bossFace == 2)
	{

		SideToLook.X = getCoordX()-4;
		SideToLook.Y = getCoordY();
		
	}
	else if (bossFace == 3)
	{

		SideToLook.X = getCoordX() + 4;
		SideToLook.Y = getCoordY();
		
	}
	else if (bossFace == 4)
	{

		SideToLook.X = getCoordX() + 4;
		SideToLook.Y = getCoordY()-2;
		
	}
	else if (bossFace == 5)
	{

		SideToLook.X = getCoordX() - 4;
		SideToLook.Y = getCoordY() - 2;
		
	}
	else if (bossFace == 6)
	{

		SideToLook.X = getCoordX() - 4;
		SideToLook.Y = getCoordY() + 2;
		
	}
	else if (bossFace == 7)
	{

		SideToLook.X = getCoordX() + 4;
		SideToLook.Y = getCoordY() + 2;
		
	}
	if (SideToLook.X == 1 || SideToLook.X == wall.X - 1 || SideToLook.Y == wall.Y - 1 ||
		SideToLook.Y == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void boss::movement(int dir)
{
	if (dir == 1)
	{
		//up
		bossFace = 0;
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
	else if (dir == 2)
	{

		bossFace = 1;
		//down
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
	else if (dir == 3)
	{

		bossFace = 3;

		//right
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
	else if (dir == 4)
	{
		bossFace = 2;
		//left
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
	else if (dir == 5)
	{
		bossFace = 4;
		//rightup
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
	else if (dir == 6)
	{
	bossFace = 6;
		//leftdown
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
	else if (dir == 7)
	{
	bossFace = 5;
		//leftup
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
	else if (dir == 8)
	{
	bossFace = 7;
		//downright
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
