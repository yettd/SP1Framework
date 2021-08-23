#include "boss.h"

boss::boss(COORD cord)
{
	hp = 10;
	bossDir = 0;
	bossface = 0;
	setTag('B');
	int face = 0;
	setCoordX(cord.X/2);
	setCoordY(cord.Y/4);
	MAPSIZE = cord;
	my = 0;
	mx = 0;
	setm_bActive(false);
	SetFireRate(1);
	SetFireC(0);
	setspeed(0.25);
	player = { 0,0 };
	inverse = false;

	moveDir = 1;

}

int boss::getshape(int x, int y)
{
	return shape[bossface][y][x];
}
COORD boss::getCord()
{
	return c;
	
}

void boss::ATTACK1()//smart ai bascally but faster and shoot stright ahead
{
	inverse = true;

	if (getWall(MAPSIZE)==false)
	{
		movement(moveDir);
	}
	else
	{
		if (moveDir == 1)
		{
			setCoordY(1);
			moveDir = 3;
			bossDir = 3;
			bossface = 1;
		}
		else if (moveDir == 3 )
		{
			setCoordX(MAPSIZE.X - 1);
			moveDir = 2;
			bossDir = 1;
			bossface = 2;
		}
		else if (moveDir == 2)
		{
			setCoordY(MAPSIZE.Y-1);
			moveDir = 4;
			bossDir = 2;
			bossface = 0;
		}
		else if (moveDir == 4)
		{
			setCoordX(1);
			moveDir = 1;
			bossDir = 0;
			bossface = 3;
		}
	}

}


void boss:: getPlayer(COORD p)
{
	player.X = getCoordX() - p.X;
	player.Y = getCoordY() - p.Y;
}

bool boss::getWall(COORD wall)//attack 1 charge to player
{
	COORD SideToLook={0,0};
	if (bossDir == 0)
	{
		if (!inverse)
		{
			bossface = 0;
			SideToLook.X = getCoordX();
			SideToLook.Y = getCoordY() - 2;
		}
		else
		{
			SideToLook.X = getCoordX();
			SideToLook.Y = getCoordY()-2;
			if (SideToLook.Y == 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
	}
	else if (bossDir == 1)
	{

		if (!inverse)
		{
			bossface = 1;
			SideToLook.X = getCoordX();
			SideToLook.Y = getCoordY() + 2;
		}
		else
		{
			SideToLook.X = getCoordX();
			SideToLook.Y = getCoordY()+2;
			if (SideToLook.Y == wall.Y-1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}


	}
	else if (bossDir == 2)
	{
		if (!inverse)
		{
			bossface = 2;
			SideToLook.X = getCoordX() - 4;
			SideToLook.Y = getCoordY();
		}
		else
		{
			SideToLook.X = getCoordX()-4;
			SideToLook.Y = getCoordY();
			if (SideToLook.X == 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
	}
	else if (bossDir == 3)
	{

		if (!inverse)
		{
			bossface = 3;
			SideToLook.X = getCoordX() + 4;
			SideToLook.Y = getCoordY();
		}
		else
		{
			SideToLook.X = getCoordX()+4;
			SideToLook.Y = getCoordY();
			if (SideToLook.X == wall.X-1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		
	}
	else if (bossDir == 4)
	{

		SideToLook.X = getCoordX() + 4;
		SideToLook.Y = getCoordY()-2;
		
	}
	else if (bossDir == 5)
	{

		SideToLook.X = getCoordX() - 4;
		SideToLook.Y = getCoordY() - 2;
		
	}
	else if (bossDir == 6)
	{

		SideToLook.X = getCoordX() - 4;
		SideToLook.Y = getCoordY() + 2;
		
	}
	else if (bossDir == 7)
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
		bossDir = 0;
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
		bossDir = 1;
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
		bossDir = 3;
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
		bossDir = 2;
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
