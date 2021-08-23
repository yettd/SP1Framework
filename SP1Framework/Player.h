#pragma once
#include "entity.h"
#include <iostream>
class Player :
    public entity
{
private:
    int hp;
    int Mhp;
    int coin;
    bool iframe;

public:

    Player();
    void movement(int dir);

    //player is the only one with hp
    void setHp(int h);
    int getHp();
    void setmHp(int h);
    int getmHp();
    void setCoin(int c);
    int getcoin();
    bool getiframe();
    void setiframe(bool iFrame);


};