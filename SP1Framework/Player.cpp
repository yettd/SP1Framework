#include "Player.h"

Player::Player()
{
	setSym(0);
	setCoin(0);
	setCoordX(0);
	setCoordY(0);
	SetFireRate(1);
	setmHp(3);
	setTag('P');
	setm_bActive(true);
	SetFireC(0);
	setiframe(false);
	mx = 0;
	my = 0;
	hp = 3;
}

void Player::movement(int dir)
{

	if (dir == 1)
	{
		setSym(94);
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
		setSym(118);
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
		setSym(60);

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
		setSym(62);

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

void Player::setHp(int h)
{
	hp = h;
}

int Player::getHp()
{
	return hp;
}

void Player::setmHp(int h)
{
	Mhp = h;
}
int Player::getmHp()
{
	return Mhp;
}
void Player::setCoin(int c)
{
	coin = c;
}

int Player::getcoin()
{
	return coin;
}

bool Player::getiframe()
{
	return iframe;
}

void Player::setiframe(bool iFrame)
{
	iframe = iFrame;
}
