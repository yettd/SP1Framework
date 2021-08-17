#include "collision.h"

bool collision::checkCollide(entity* i, entity* l)
{
	if (i->getCoordX() == l->getCoordX() && i->getCoordY() == l->getCoordY())
		return true;
	else return false;
}
