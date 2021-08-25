#include "star.h"

star::star(int x, int y)
{
	setCoordX(x);
	setCoordY(y);
	setSym('.');
	setspeed(1);
	mx = 0;
	my = 0;
}

void star::movement(int dir)
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
