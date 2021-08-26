#pragma once
#include "entity.h"
#include "Framework/console.h"
class boss :
	public entity
{
private:
	int hp;
	//COORD c;
	//COORD player;
	int bossDir;
	int bossface;

	int attack = 0;

	COORD MAPSIZE;

	int moveDir;

	bool inverse = false;

	int shape[9][5][5] = {
		{{0,0,1,0,0},
		 {0,1,1,1,0},
		 {1,1,1,1,1},
		 {0,0,0,0,0},
		 {0,0,0,0,0}},//up

		{{0,0,0,0,0},
		 {0,0,0,0,0},
		 {1,1,1,1,1},
		 {0,1,1,1,0},
		 {0,0,1,0,0}},//down

		{{0,0,1,0,0},
		 {0,1,1,0,0},
		 {1,1,1,0,0},
		 {0,1,1,0,0},
		 {0,0,1,0,0}},//left

		{{0,0,1,0,0},
		 {0,0,1,1,0},
		 {0,0,1,1,1},
		 {0,0,1,1,0},
		 {0,0,1,0,0}},//right

		{{0,1,1,1,1},
		 {0,0,1,1,1},
		 {0,0,0,1,1},
		 {0,0,0,0,1},
		 {0,0,0,0,0}},//upright

		{{1,1,1,1,0},
		 {1,1,1,0,0},
		 {1,1,0,0,0},
		 {1,0,0,0,0},
		 {0,0,0,0,0}},//upleft

		{{0,0,0,0,0},
		 {1,0,0,0,0},
		 {1,1,0,0,0},
		 {1,1,1,0,0},
		 {1,1,1,1,0}},//downleft

		{{0,0,0,0,0},
		 {0,0,0,0,1},
		 {0,0,0,1,1},
		 {0,0,1,1,1},
		 {0,1,1,1,1}},//downright
		{{1,1,1,1,1},
		 {1,1,1,1,1},
		 {1,1,1,1,1},
		 {1,1,1,1,1},
		 {1,1,1,1,1}}//attack 2 mode (shooting)
	};
public:
	boss(COORD cord);
	int getDirXfromPlayer(int x);
	int getDirYfromPlayer(int y);
	void movement(int dir);
	int getshape(int x, int y);

	void idel();
	void ATTACK1();
	int Attack2(int x, int y);



	bool getWall(COORD wall);

	void setAttack(int style);
	int getAttack();

	int gethp();
	void sethp(int h);

	int getFace();

};

