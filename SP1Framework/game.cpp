// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "entity.h"
#include "Player.h"
#include "bullet.h"
#include "enemy.h"
#include "boss.h"
#include "star.h"
#include "Rocekt.h"
#include "powerUp.h"
float spawnCounter = 2;
float spawnRate = spawnCounter;
int face = 1;
int lastface = 1;


double  g_dElapsedTime;
double  g_dDeltaTime;
float defTime =10 ;
float currTime = 0;
int wave = 1;
int maxenemy = 3;
int current = 0;
//level for each upgrade
int ug1lvl = 1;
int ug2lvl = 1;
int ug3lvl = 1;

float iframeCD = 0;


COORD Teemp = { 0,0 };
COORD a = { 0,0 };
float timer = 0;

int ug1 = 5, ug2 = 5, ug3 = 5;
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;

float spawnStar = 2.5;
std::vector<star*> stars;

std::vector<Rocekt*> rkt;

std::vector<entity*> en;
std::ostringstream error;
// Game specific variables here
//Player  player;

EGAMESTATES g_eGameState = S_SPLASHSCREEN; // initial state

// Console object
Console g_Console(80, 25, "SP1 Framework");

//power-ups
bool triBullet = false;
bool rocket = false;

float tribulletTimer;
float rocketTimer;

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    srand(time(NULL));
    // Set precision for floating point output
    g_dElapsedTime = 0.0;    
    currTime = defTime;
    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;
    en.push_back(new Player);
    en[0]->setSym(94);
    en[0]->setspeed(0.1);
    en[0]->setCoordX(g_Console.getConsoleSize().X / 2);
    en[0]->setCoordY(g_Console.getConsoleSize().Y / 2);
    en[0]->setm_bActive(true);
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Get all the console input events
//            This function sets up the keyboard and mouse input from the console.
//            We will need to reset all the keyboard status, because no events will be sent if no keys are pressed.
//
//            Remember to set the handlers for keyboard and mouse events.
//            The function prototype of the handler is a function that takes in a const reference to the event struct
//            and returns nothing. 
//            void pfKeyboardHandler(const KEY_EVENT_RECORD&);
//            void pfMouseHandlerconst MOUSE_EVENT_RECORD&);
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{
    // resets all the keyboard events
    if (g_eGameState == S_UPGRADESCREEN)
    {

    memset(g_skKeyEvent, 0, K_COUNT * sizeof(*g_skKeyEvent));
    }
    // then call the console to detect input from user
    g_Console.readConsoleInput();    
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the keyboard input. Whenever there is a keyboard event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            The KEY_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any keyboard event in the Splashscreen state
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent - reference to a key event struct
// Output   : void
//--------------------------------------------------------------
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent)
{    
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: // don't handle anything for the splash screen
        break;
    case S_GAME: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
        break;
    case S_LOSE: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
        break;
    case S_WIN: gameplayKBHandler(keyboardEvent);
        break;
    case S_UPGRADESCREEN: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
        break;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the mouse input. Whenever there is a mouse event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            For the mouse event, if the mouse is not moved, no event will be sent, hence you should not reset the mouse status.
//            However, if the mouse goes out of the window, you would not be able to know either. 
//
//            The MOUSE_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any mouse event in the Splashscreen state
//            
// Input    : const MOUSE_EVENT_RECORD& mouseEvent - reference to a mouse event struct
// Output   : void
//--------------------------------------------------------------
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{    
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: // don't handle anything for the splash screen
        break;
    case S_GAME: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
        break;
    }
}
void rechargeFire()
{
    //fire rate for all
    for (int i = 0; i < en.size(); i++)
    {
        if (en[i]->getTag() == 'P' || en[i]->getTag() == 'E')
        {
            if (en[i]->getm_activr() == false)
            {
                en[i]->SetFireC(en[i]->getFireC() + 0.01);
                if (en[i]->getFireC() >= en[i]->getFireRate())
                {
                    en[i]->setm_bActive(true);
                    en[i]->SetFireC(0);
                }
            }
        }
    }
}

//--------------------------------------------------------------
// Purpose  : This is the keyboard handler in the game state. Whenever there is a keyboard event in the game state, this function will be called.
//            
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent)
{
    // here, we map the key to our enums
    EKEYS key = K_COUNT;
    
    switch (keyboardEvent.uChar.AsciiChar)
    {
    case 49: key = K_NUM1; break;
    case 50: key = K_NUM2; break;
    case 51: key = K_NUM3; break;
    case 52: key = K_NUM4; break;
    case 87:
    case 119: key = K_UP; break;
    case 83:
    case 115: key = K_DOWN; break;
    case 65: 
    case 97: key = K_LEFT; break;
    case 68:
    case 100: key = K_RIGHT; break;
    case VK_SPACE: key = K_SPACE; break;
    case VK_ESCAPE: key = K_ESCAPE; break; 
    }
    // a key pressed event would be one with bKeyDown == true
    // a key released event would be one with bKeyDown == false
    // if no key is pressed, no event would be fired.
    // so we are tracking if a key is either pressed, or released
    if (key != K_COUNT)
    {
        g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;
        g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;
    }    
}

//--------------------------------------------------------------
// Purpose  : This is the mouse handler in the game state. Whenever there is a mouse event in the game state, this function will be called.
//            
//            If mouse clicks are detected, the corresponding bit for that mouse button will be set.
//            mouse wheel, 
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{
    if (mouseEvent.dwEventFlags & MOUSE_MOVED) // update the mouse position if there are no events
    {
        g_mouseEvent.mousePosition = mouseEvent.dwMousePosition;
    }
    g_mouseEvent.buttonState = mouseEvent.dwButtonState;
    g_mouseEvent.eventFlags = mouseEvent.dwEventFlags;
}

void IframeCool()
{
    if (iframeCD >= 1 && ((Player*)en[0])->getiframe()==true)
    {
        ((Player*)en[0])->setiframe(false);
        iframeCD =0;
    }
    else if(((Player*)en[0])->getiframe() == true)
    {
        iframeCD += 0.01;
    }
}

void bossCollision()
{
    boss* bs = ((boss*)en[1]);
    COORD temp;

    temp.X = bs->getCoordX();
    temp.Y = bs->getCoordY();
    temp.X -= 4;
    temp.Y -= 2;
    int temp2y = temp.Y;
    int temp2x = temp.X;
    
    for (int i = 0; i < en.size(); i++)
    {
        if (i != 1)//not checking with boss
        {
            for (int k = 0; k < 5; k++)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (bs->getshape(j, k) == 1)
                    {
                        if ((en[i]->getCoordX() == temp.X || en[i]->getCoordX() == temp.X + 1) && en[i]->getCoordY() == temp.Y)
                        {
                            if (en[i]->getTag() == 43)
                            {
                                delete en[i];
                                en.erase(en.begin() + i);
                                bs->sethp(bs->gethp() - 1);
                                i--;
                            }
                            else if (en[i]->getTag() == 'P')
                            {
                                if ( !((Player*)en[i])->getiframe())
                                {
                                    ((Player*)en[i])->setHp(((Player*)en[i])->getHp() - 1);
                                    ((Player*)en[i])->setiframe(true);
                                }
                            }
                        }
                    }
                    temp.X += 2;
                }
                temp.X = temp2x;
                temp.Y += 1;
            }
            
        }
        temp.Y = temp2y;
    }
    //checkhp
    if (bs->gethp() <= 0)
    {
        wave++;
    }
    //gamewin
}

void collisionDetection()
{
    for (int i = 0; i < en.size(); i++)
    {
        for (int j = 0; j < en.size(); j++)
        {
            if (i != j)
            {
                if (en[i]->getCoordX() == en[j]->getCoordX() && en[i]->getCoordY() == en[j]->getCoordY())
                {
                    if (en[i]->getTag() == 'P')
                    {
                        if (en[j]->getTag() == 45 || en[j]->getTag() == 'E')
                        {
                            if (en[j]->getTag() == 'E')
                            {
                                current--;
                            }
                            delete en[j];
                            en.erase(en.begin() + j);
                            if (!((Player*)en[i])->getiframe())
                            {
                                ((Player*)en[i])->setHp(((Player*)en[i])->getHp() - 1);
                                ((Player*)en[i])->setiframe(true);
                            }
                            j--;
                           
                        }
                         if (en[j]->getTag()=='U')
                        {
                        
                            if (((powerUp*)en[j])->getpower() == 1)
                            {
                                triBullet = true;
                                tribulletTimer = 5;
                            }
                            else
                            {
                                rocket = true;
                                rocketTimer = 5;
                            }
                            delete en[j];
                            en.erase(en.begin() + j);

                            j--;
                        }
                    }
                    else if (en[i]->getTag() == 'E')
                    {             
                        if (en[j]->getTag() == 43)
                        {
                            if (rocket)
                            {
                                rkt.push_back(new Rocekt(en[i]->getCoordX(), en[i]->getCoordY()));
                            }
                            if (((enemy*)en[i])->getAI() == 0)
                            {
                                ((Player*)en[0])->setCoin(((Player*)en[0])->getcoin() + 2);
                                if ((rand() % 100) %2 == 0)
                                {
                                    en.push_back(new powerUp(en[i]->getCoordX(), en[i]->getCoordY(), rand() % 2));
                                }
                            }
                            else if (((enemy*)en[i])->getAI() == 1)
                            {
                                ((Player*)en[0])->setCoin(((Player*)en[0])->getcoin() + 10);
                                if ((rand() % 100) % 5 == 0)
                                {
                                    en.push_back(new powerUp(en[i]->getCoordX(), en[i]->getCoordY(), rand() % 2));
                                }
                            }
                            else if (((enemy*)en[i])->getAI() == 2)
                            {
                                if ((rand() % 100) % 6 == 0)
                                {
                                    en.push_back(new powerUp(en[i]->getCoordX(), en[i]->getCoordY(), rand() % 2));
                                }
                                ((Player*)en[0])->setCoin(((Player*)en[0])->getcoin() + 5);
                            }
                            //drop stuff


                            delete en[j];
                            delete en[i];
                            current--;
                            if (j < i)
                            {
                                en.erase(en.begin() + i);
                                en.erase(en.begin() + j);
                            }
                            else
                            {
                                en.erase(en.begin() + j);
                                en.erase(en.begin() + i);
                            }
                            i--;
                            j--;
                         
                        }
                    }
                    
                }
            }
        }
    }
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
  
    g_dDeltaTime = dt;
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: updateGame();// gameplay logic when we are in the game
            break;
        case S_LOSE: loseScreenInput();
            break;
        case S_WIN: winScreenInput();
            break;
        case S_UPGRADESCREEN: upgradeScreenInput();
            break;
    }
}


void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME;
}

void updateGame()       // gameplay logic
{
    if (wave > 10)
    {
        g_eGameState = S_WIN;
        PlaySound(TEXT("winSFX"), NULL, SND_ASYNC);
    }

    if (currTime <= 0)
    {
        g_eGameState = S_UPGRADESCREEN;
    }

    if (wave % 10 != 0)
    {
    spawnEnemy();
    }
    else
    {
        if (en.size() == 1)
        {
            en.push_back(new boss(g_Console.getConsoleSize()));
            //currTime = 30;
            PlaySound(TEXT("reeSFX.wav"), NULL, SND_SYNC);
        }
        bossAttacks();
       
    }
    if (wave < 10)
    {
        currTime -= 0.01;
    }
    createStar();
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
    rechargeFire();          // sound can be played here too.
    moveEnemy();
    moveBullet();
    enShoot();
    IframeCool();
    collisionDetection();
    explosionCollision();
    if (wave == 10)
    {
        bossCollision();
    }
    checkLose();
    powerUpTimer();
}

float bossAttackTimer = 5;//how long before next move
int temp;
void bossAttacks()
{
    boss* bs = ((boss*)en[1]);

    if (bossAttackTimer > 0)
    {
        if (bs->getAttack() == 1)
        {
            bs->ATTACK1();
            int dir = 0;
            if (bs->getFace() == 0)
            {
                dir = 1;
            }
            if (bs->getFace() == 1)
            {
                dir = -1;
            }
            if (bs->getFace() == 2)
            {
                dir = -3;
            }
            if (bs->getFace() == 3)
            {
                dir = 3;
            }
            if (bs->getm_activr())
            {

                createBullet(bs->getCoordX(), bs->getCoordY(), 45, dir, 0);
            }
        }
        else if (bs->getAttack() == 2)
        {
            
            if (Teemp.X != bs->getCoordX()-2 && Teemp.Y != bs->getCoordY())
            {
                Teemp.X = bs->getCoordX();
                Teemp.Y = bs->getCoordY();
                a.X = Teemp.X-2;
                a.Y = Teemp.Y-2;
                temp = a.X-2;
            }
            int face = bs->Attack2(a.X , a.Y);
            if (face != 0)
            {
                int ThreeFace[3];
                if (face == 4 || face == -4)
                {
                    ThreeFace[0] = face;
                    ThreeFace[1] = face - (1 * (face / 4));
                    ThreeFace[2] = face - (3 * (face / 4));
                    for (int i = 0; i < 3; i++)
                    {

                        createBullet(temp, a.Y, 45, ThreeFace[i], 3);
                    }
                }
                else if (face == 2 || face == -2)
                {
                    ThreeFace[0] = face;
                    ThreeFace[1] = face + (1 * (face / 2));
                    ThreeFace[2] = face - (3 * (face / 2));
                    for (int i = 0; i < 3; i++)
                    {

                        createBullet(temp, a.Y, 45, ThreeFace[i], 3);
                    }
                }
                else
                {
                    createBullet(temp, a.Y, 45, face, 0);

                }


            }
             if (timer >= 1)
             {
                 if (a.X < Teemp.X + 2 &&
                     a.Y == Teemp.Y - 2)
                 {
                     a.X += 1;
                     temp += 2;
                 }
                 else if (a.X == Teemp.X + 2 &&
                     a.Y < Teemp.Y + 2)
                 {
                     a.Y += 1;
                 }
                 else if (a.X > Teemp.X - 2 &&
                     a.Y == Teemp.Y + 2)
                 {
                     a.X -= 1;
                     temp -= 2;
                 }
                 else if (a.X == Teemp.X - 2 &&
                     a.Y > Teemp.Y - 2)
                 {
                     a.Y -= 1;
                 }

            
                 timer = 0;
             }
             else
             {
                 timer +=0.2 ;
             }



        }
        else if (bs->getAttack() == 0)
        {
            bs->idel();
        }
        bossAttackTimer -= 0.01;
    }
    else
    {
        if (bs->getAttack() != 0 && bs->getAttack() != -1)
        {
            bs->setAttack(0);
            bossAttackTimer = 5;
        }
        else
        {
            if (bs->getAttack() == -1)
            {
                bs->setAttack(1);
            }
            else
            {
                bs->setAttack(rand()%2+1);
            }
            bossAttackTimer = rand()%10+5;
        }

    }

  
}

void upgradeScreenInput()
{
    if (g_skKeyEvent[K_NUM1].keyDown)
    {
        if (((Player*)en[0])->getcoin() >= ug1)
        {

            error.str("");
            ((Player*)en[0])->setCoin(((Player*)en[0])->getcoin() - ug1);
            float fireRate = en[0]->getFireRate();
            fireRate -= 0.1;
            en[0]->SetFireRate(fireRate);
            ug1 += 5;
            currTime = defTime;
            ug1lvl++;
            PlaySound(TEXT("kachingSFX"), NULL, SND_ASYNC);
        }
        else
        {
            if (error.str() == "")
            {
                error << "NOT ENOUGH COINS";
            }
        }
    }
    else if (g_skKeyEvent[K_NUM2].keyDown)
    {
        if (((Player*)en[0])->getcoin() >= ug2)
        {

            error.str("");
            ((Player*)en[0])->setCoin(((Player*)en[0])->getcoin() - ug2);
            float speed = en[0]->getSpeed();
            speed += 0.05;
            en[0]->setspeed(speed);
            ug2 += 5;
            currTime = defTime;
            ug2lvl++;
            PlaySound(TEXT("kachingSFX"), NULL, SND_ASYNC);
        }
        else
        {
            if (error.str() == "")
            {
                error << "NOT ENOUGH COINS";
            }
        }
    }
    else if (g_skKeyEvent[K_NUM3].keyDown)
    {
        if (((Player*)en[0])->getcoin() >= ug3)
        {

            error.str("");
            ((Player*)en[0])->setCoin(((Player*)en[0])->getcoin() - ug3);
            ((Player*)en[0])->setmHp(((Player*)en[0])->getmHp() + 1);
            ug3 += 5;
            currTime = defTime;
            ug3lvl++;
            PlaySound(TEXT("kachingSFX"), NULL, SND_ASYNC);
        }
        else
        {
            if (error.str() == "")
            {
                error << "NOT ENOUGH COINS";
            }
        }
    }
    else if (g_skKeyEvent[K_NUM4].keyDown)
    {
        //float speed = en[0]->getSpeed();
        //speed += 0.05;
        //en[0]->setspeed(speed);
        currTime = defTime;
        en[0]->setCoordX(g_Console.getConsoleSize().X / 2);
        en[0]->setCoordY(g_Console.getConsoleSize().Y / 2);
        g_eGameState = S_GAME;
        rkt.clear();
        updateWave();
        ((Player*)en[0])->setHp(((Player*)en[0])->getmHp());
        clearEnemy(1);
        updateMaxenemy();
        current = 0;
        error.str("");
        spawnRate = spawnCounter;
        tribulletTimer = 0;
        rocketTimer = 0;
    }
    
}

void createStar()
{
    if (spawnStar == 0)
    {
        for (int i = 0; i < rand()%6; i++)
        {

            stars.push_back(new star(80, rand() % 76 + 2));
        }
    }
    else
    {
        spawnStar -= 0.50;
    }
}
void powerUpTimer()
{
    if (triBullet)
    {
        if (tribulletTimer > 0)
        {
            tribulletTimer -= 0.01;
        }
        else
        {
            triBullet = false;
        }
    }
    if (rocket)
    {
        if (rocketTimer > 0)
        {
            rocketTimer -= 0.01;
        }
        else
        {
            rocket = false;
        }
    }
}


void renderExplodsion()
{
    for (int i = 0; i < rkt.size(); i++)
    {
        WORD charColor = 0xCC;

        COORD temp;
        temp.X = rkt[i]->getCoordX();
        temp.Y = rkt[i]->getCoordY();
        temp.X -= 4;
        temp.Y -= 2;
        int temp2 = temp.X;

        for (int k = 0; k < 5; k++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (rkt[i]->getshape(j, k) == 1)
                {
                    if (temp.Y >= 2)
                    {
                        g_Console.writeToBuffer(temp, "0 ", charColor);
                    }
                }
                temp.X += 2;
            }
            temp.X = temp2;
            temp.Y += 1;
        }

        if (rkt[i]->getTimer() > 0)
        {
            rkt[i]->setTimer(rkt[i]->getTimer() - 0.01);
        }
        else
        {
            delete rkt[i];
            rkt.erase(rkt.begin()+i);
        }
    }
    
}

void explosionCollision()
{
    for (int i = 0; i < rkt.size(); i++)
    {
        COORD temp;
        temp.X = rkt[i]->getCoordX();
        temp.Y = rkt[i]->getCoordY();
        temp.X -= 4;
        temp.Y -= 2;
        int temp2y = temp.Y;
        int temp2x = temp.X;

        for (int e = 1; e < en.size(); e++)
        {
                for (int k = 0; k < 5; k++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        if (rkt[i]->getshape(j, k) == 1)
                        {
                            if ((en[e]->getCoordX() == temp.X || en[e]->getCoordX() == temp.X + 1) && en[e]->getCoordY() == temp.Y)
                            {
                                 if (en[e]->getTag() == 'E')
                                {
                                     if (((enemy*)en[i])->getAI() == 0)
                                     {
                                         ((Player*)en[0])->setCoin(((Player*)en[0])->getcoin() + 2);
                                     }
                                     else if (((enemy*)en[i])->getAI() == 1)
                                     {
                                         ((Player*)en[0])->setCoin(((Player*)en[0])->getcoin() + 10);
                                     }
                                     else if (((enemy*)en[i])->getAI() == 2)
                                     {
                                         ((Player*)en[0])->setCoin(((Player*)en[0])->getcoin() + 5);
                                     }
                                     delete en[e];
                                     en.erase(en.begin() + e);
                                }
                            }
                        }
                        temp.X += 2;
                    }
                    temp.X = temp2x;
                    temp.Y += 1;
                }
            temp.Y = temp2y;
        }
    }
}

void renderStar()
{
    for (int i = 0; i < stars.size(); i++)
    {
            WORD charColor = 0x07;
            COORD temp;
            temp.X = stars[i]->getCoordX();
            temp.Y = stars[i]->getCoordY();
            g_Console.writeToBuffer(temp, stars[i]->getSym(), charColor);
            stars[i]->movement(0);
            if (stars[i]->getCoordX() < 2)
            {
                delete stars[i];
                stars.erase(stars.begin() + i);
            }
    }
}
void loseScreenInput()
{
    if (g_skKeyEvent[K_SPACE].keyDown)
    {
        clearEnemy(0);
        en.clear();
        wave = 1;
        currTime = defTime;
        en.push_back(new Player);
        en[0]->setSym(94);
        en[0]->setspeed(0.1);
        en[0]->setCoordX(g_Console.getConsoleSize().X / 2);
        en[0]->setCoordY(g_Console.getConsoleSize().Y / 2);
        en[0]->setm_bActive(true);
        g_eGameState = S_GAME;
        spawnCounter = 2;
        updateMaxenemy();
        current = 0;
        spawnRate = spawnCounter;
        ug1 = 5;
        ug2 = 5;
        ug3 = 5;
        ug1lvl = 1;
        ug2lvl = 1;
        ug3lvl = 1;
    }
    else if (g_skKeyEvent[K_ESCAPE].keyDown)
    {
        g_bQuitGame = true;
    }
}

void winScreenInput()
{
    if (g_skKeyEvent[K_SPACE].keyDown)
    {
        clearEnemy(0);
        en.clear();
        wave = 1;
        currTime = defTime;
        en.push_back(new Player);
        en[0]->setSym(94);
        en[0]->setspeed(0.1);
        en[0]->setCoordX(g_Console.getConsoleSize().X / 2);
        en[0]->setCoordY(g_Console.getConsoleSize().Y / 2);
        en[0]->setm_bActive(true);
        g_eGameState = S_GAME;
        spawnCounter = 2;
        updateMaxenemy();
        current = 0;
        spawnRate = spawnCounter;
        ug1 = 5;
        ug2 = 5;
        ug3 = 5;
        ug1lvl = 1;
        ug2lvl = 1;
        ug3lvl = 1;
    }
    else if (g_skKeyEvent[K_ESCAPE].keyDown)
    {
        g_bQuitGame = true;
    }
}
int ThreeFace[3] = { 0,0,0 };
void moveCharacter()
{    
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    if (g_skKeyEvent[K_UP].keyDown && en[0]->getCoordY() > 2)
    {
        face += 1;
        en[0]->movement(1);
    }
    else if (g_skKeyEvent[K_DOWN].keyDown && en[0]->getCoordY() < g_Console.getConsoleSize().Y - 2)
    {
        face -= 1;
        en[0]->movement(2);
    }
    if (g_skKeyEvent[K_LEFT].keyDown && en[0]->getCoordX() > 3)
    {
        face -= 3;
        en[0]->movement(3);
    }
    else if (g_skKeyEvent[K_RIGHT].keyDown && en[0]->getCoordX() < g_Console.getConsoleSize().X - 3)
    {
        face += 3;
        en[0]->movement(4);
    }
    if (face != 0)
    {
        lastface = face;
    }
    if (g_skKeyEvent[K_SPACE].keyDown && en[0]->getm_activr() == true)
    {
        if (triBullet)
        {
     
            if (lastface == 1 || lastface==-1)
            {
                ThreeFace[0] = lastface;
                ThreeFace[1] = lastface+3;
                ThreeFace[2] = lastface-3;
            }
            else if (lastface == 3 || lastface == -3)
            {
                ThreeFace[0] = lastface;
                ThreeFace[1] = lastface + 1;
                ThreeFace[2] = lastface - 1;
            }
            else if (lastface == 4 || lastface == -4)
            {
                ThreeFace[0] = lastface;
                ThreeFace[1] = lastface - (1*(lastface/4));
                ThreeFace[2] = lastface - (3 * (lastface / 4));
            }
            else if (lastface == 2 || lastface == -2)
            {
                ThreeFace[0] = lastface;
                ThreeFace[1] = lastface + (1 * (lastface / 2));
                ThreeFace[2] = lastface - (3 * (lastface / 2));
            }

            for (int i = 0; i < 3; i++)
            {

            createBullet(en[0]->getCoordX(), en[0]->getCoordY(), 43, ThreeFace[i], 3);
            }

        }
        else
        {
          createBullet(en[0]->getCoordX(), en[0]->getCoordY(), 43, lastface, 3);
        }
        en[0]->setm_bActive(false);

    }
 
    face = 0;

}
void displayError()
{
    if (error.str() != "")
    {
        COORD c = g_Console.getConsoleSize();
        c.Y=
        c.Y /3 + 5;
        c.X = c.X / 2 - 9;
        g_Console.writeToBuffer(c, error.str(), 0x09);
    }
}
void enShoot()
{
    for (int i = 0; i < en.size(); i++)
    {
        if (en[i]->getTag() == 'E')
        {
            enemy* e = (enemy*)en[i];
            if (e->getm_activr() == true&& e->getAI()!=0)
            {
                createBullet(e->getCoordX(), e->getCoordY(), 45, e->shootDir(en[0]->getCoordX(), en[0]->getCoordY()), e->getAI());
                e->SetFireC(0);
                e->setm_bActive(false);
            }
        }
    }
}

void createBullet(int x,int y,char t,int dir, int i)
{
    en.push_back(new bullet(x, y, dir,t));
    if (i != 0) 
    {
        PlaySound(NULL, NULL, 0);
        if (i == 3) PlaySound(TEXT("playerLaserSFX.wav"), NULL, SND_ASYNC);
        else if (i == 1) PlaySound(TEXT("pewSFX.wav"), NULL, SND_ASYNC);
        else if (i == 2) PlaySound(TEXT("enemy1LaserSFX.wav"), NULL, SND_ASYNC);
    }
    /*else if (i == 0) PlaySound(TEXT("shootSFX.wav"), NULL, SND_ASYNC);*/
}

void moveEnemy()
{
    for (int i = 0; i < en.size(); i++)
    {
        if (en[i]->getTag() == 'E')
        {
            enemy* e = ((enemy*)en[i]);
            if (e->getAI() == 0)
            {
                e->DumbAI(en[0]->getCoordX(), en[0]->getCoordY());
            }
            else if (e->getAI() == 1)
            {
                e->AggresiveAI(en[0]->getCoordX(), en[0]->getCoordY(), g_Console.getConsoleSize().X-4, g_Console.getConsoleSize().Y-1);
            }
            else if (e->getAI() == 2) 
            {
                e->SmartAI(g_Console.getConsoleSize().X-3, g_Console.getConsoleSize().Y-2);
            }
        }
    }
}

void moveBullet()
{
    for (int i = 0; i < en.size(); i++)
    {
        if (en[i]->getTag() == 43 || en[i]->getTag() == 45)
        {
            bullet* b = (bullet*)en[i];
            b->movement(b->GetDirection());
            destroyBullet(i);
        }
    }
}

void updateMaxenemy()
{
    if (wave == 1)
    {
        maxenemy = 3;
    }
    else
    {
        maxenemy++;
    }
}

void spawnEnemy()
{
    if (spawnRate >= spawnCounter)
    {
        for (int i = current; i < maxenemy; i++)
        {
            en.push_back(new enemy);
            spawnRate = 0;
            current++;
        }
    }
    else
    {
        spawnRate += 0.01;
    }
}

void clearEnemy(int a)
{
    for (int i = a; i < en.size(); i++)
    {
        delete en[i];
    }
    en.erase(en.begin() + a,en.end());
}
// Include enemy behaviour


void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
        g_bQuitGame = true;    
}

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: renderSplashScreen();
        break;
    case S_GAME: renderGame();
        break;
    case S_LOSE: renderLoseScreen();
        break;
    case S_WIN: renderWinScreen();
        break;
    case S_UPGRADESCREEN: renderUpgradeScreen();
        displayCoin();
        displayError();
        break;
    }
   
    renderFramerate();      // renders debug information, frame rate, elapsed time, etc
    //renderInputEvents();    // renders status of input events
    renderToScreen();       // dump the contents of the buffer to the screen, one frame worth of game
    
}

void destroyBullet(int i)
{
    if (en[i]->getCoordX() > g_Console.getConsoleSize().X-3 ||
        en[i]->getCoordY() > g_Console.getConsoleSize().Y-2 ||
        en[i]->getCoordX() < 3 ||
        en[i]->getCoordY() < 2)
    {
        delete en[i];
        en.erase(en.begin() + i);
    }
}



void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x00);
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.Y +=  2;
    c.X = c.X / 2 - 6;
    g_Console.writeToBuffer(c, "BATTLESHIP", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 7;
    g_Console.writeToBuffer(c, "WASD TO MOVE", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "SPACEBAR TO FIRE", 0x09);
}

void renderGame()
{
    renderStar();
    renderExplodsion();
    renderEntity();
    displayStats();
    displayHP();
    displayWave();
    displayCoin();
    renderMap();        // renders the map to the buffer first
}

void renderUpgradeScreen()
{
    if (wave < 10)
    {
        std::ostringstream ss;
        COORD c = g_Console.getConsoleSize();
        c.Y /= 3;
        c.X = c.X / 2 - 8;
        ss << "Select Upgrade";
        g_Console.writeToBuffer(c, ss.str(), 0x03);
        ss.str("");
        ss << "1. Increase Fire Rate [Lv." << ug1lvl << "]( " << ug1 << " coin )";
        c.Y += 1;
        c.X = g_Console.getConsoleSize().X / 2 - 19;
        g_Console.writeToBuffer(c, ss.str(), 0x09);
        c.Y += 1;
        ss.str("");
        ss << "2. Increase Movement Speed [Lv." << ug2lvl << "]( " << ug2 << " coin )";
        c.X = g_Console.getConsoleSize().X / 2 - 21;
        g_Console.writeToBuffer(c, ss.str(), 0x09);
        c.Y += 1;
        ss.str("");
        ss << "3. Increase Max health [Lv." << ug3lvl << "]( " << ug3 << " coin )";
        c.X = g_Console.getConsoleSize().X / 2 - 19;
        g_Console.writeToBuffer(c, ss.str(), 0x09);
        c.Y += 1;
        ss.str("");
        ss << "4. Continue to next wave";
        c.X = g_Console.getConsoleSize().X / 2 - 13;
        g_Console.writeToBuffer(c, ss.str(), 0x09);
    }
    else
    {
        g_eGameState = S_WIN;
    }
}
void checkLose()
{
    if (((Player*)en[0])->getHp() <= 0)
    {
        en.clear();
        g_eGameState = S_LOSE;
    }
}

void renderLoseScreen()
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 4;
    g_Console.writeToBuffer(c, "YOU LOSE", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 5;
    
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 13;
    g_Console.writeToBuffer(c, "PRESS SPACE TO PLAY AGAIN", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 10;
    g_Console.writeToBuffer(c, "PRESS ESCAPE TO QUIT", 0x09);
}

void renderWinScreen()
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 4;
    g_Console.writeToBuffer(c, "YOU WIN", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 5;
    
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 13;
    g_Console.writeToBuffer(c, "PRESS SPACE TO PLAY AGAIN", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 10;
    g_Console.writeToBuffer(c, "PRESS ESCAPE TO QUIT", 0x09);
}

void renderMap()
{
    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;
    int maxX = g_Console.getConsoleSize().X;
    int maxY = g_Console.getConsoleSize().Y;
    c.X = 0;
    c.Y = 1;
    while (c.Y <= maxY)
    {
        while (c.X < maxX)
        {
            if (c.Y == 1)
            {
                colour(colors[11]);
                g_Console.writeToBuffer(c, "  ", colors[11]);
            }
            else if (c.Y == maxY - 1)
            {
                colour(colors[11]);
                g_Console.writeToBuffer(c, "  ", colors[11]);
            }
            else
            {
                if (c.X == 0)
                {
                    colour(colors[11]);
                    g_Console.writeToBuffer(c, "  ", colors[11]);
                }
                else if (c.X == maxX - 2)
                {
                    colour(colors[11]);
                    g_Console.writeToBuffer(c, "  ", colors[11]);
                }
            }
            c.X += 1;
        }
        c.X = 0;
        c.Y += 1;
    }
}

void renderEntity()
{
    for (int i = 0; i < en.size(); i++)
    {
        if (en[i]->getTag() != 'B')
        {
            WORD charColor = 0x17;
            if (en[i]->getTag() == 'P')
            {
                if (!((Player*)en[i])->getiframe())
                {
                    charColor = 0x17;

                }
                else
                {
                    charColor = 0x6F;
                }
            }
            else if (en[i]->getTag() == 43)
            {
                charColor = 0x06;
            }
            else if (en[i]->getTag()=='U')
            {
                if (((powerUp*)en[i])->getpower()==1)
                {
                    charColor = 0x17;

                }
                else
                {
                    charColor = 0x6F;
                }
            }
            else
            {
                charColor = 0x0C;
            }
            COORD temp;
            temp.X = en[i]->getCoordX();
            temp.Y = en[i]->getCoordY();
            g_Console.writeToBuffer(temp, en[i]->getSym(), charColor);
        }
        else
        {
           renderBOSS(i);
        }
    }
}
void renderBOSS(int a)
{
    boss* b = (boss*)en[a];
    WORD charColor = 0x0C;

    COORD temp;
    temp.X = b->getCoordX();
    temp.Y = b->getCoordY();
    temp.X -= 4;
    temp.Y -= 2;
    int temp2 = temp.X;
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (b->getshape(j,i) == 1)
            {
            g_Console.writeToBuffer(temp, "0 ", charColor);
            }
            temp.X += 2;
        }
        temp.X =temp2;
        temp.Y += 1;
    }
}

void renderCharacter()
{
    //Draw the location of the character
    WORD charColor = 0x0C;
    COORD temp;
    temp.X = en[0]->getCoordX();
    temp.Y = en[0]->getCoordY();
    g_Console.writeToBuffer(temp, en[0]->getSym(), 0x17);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    /*ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);*/
}

// this is an example of how you would use the input events
void renderInputEvents()
{
    // keyboard events
    COORD startPos = {50, 2};
    std::ostringstream ss;
    std::string key;
    for (int i = 0; i < K_COUNT; ++i)
    {
        ss.str("");
        switch (i)
        {
        case K_NUM1: key = "NUM1";
            break;
        case K_NUM2: key = "NUM1";
            break;
        case K_UP: key = "UP";
            break;
        case K_DOWN: key = "DOWN";
            break;
        case K_LEFT: key = "LEFT";
            break;
        case K_RIGHT: key = "RIGHT";
            break;
        case K_SPACE: key = "SPACE";
            break;
        default: continue;
        }
        if (g_skKeyEvent[i].keyDown)
            ss << key << " pressed";
        else if (g_skKeyEvent[i].keyReleased)
            ss << key << " released";
        else
            ss << key << " not pressed";

        COORD c = { startPos.X, startPos.Y + i };
        g_Console.writeToBuffer(c, ss.str(), 0x17);
    }
    
}

void displayStats()
{
    COORD c;
    c.X = g_Console.getConsoleSize().X / 2 - 6;
    c.Y = 0;
    std::string s;
    std::ostringstream ss;

    int WS = floor(currTime);
    if (wave == 10)
    {
        if (en.size() > 1)
        {
            WS = ((boss*)en[1])->gethp();
        }
    }
    //int hp = ((Player*)en[0])->getHp();
    if (wave != 10)
    {
        ss << "TIME : " << std::to_string(WS);
    }
    else
    {
        ss << "BOSS HP : " << std::to_string(WS);
    }
    g_Console.writeToBuffer(c, ss.str(), 0x17);
}

void displayHP()
{
    COORD c;
    c.X = 0;
    c.Y = 0;
    std::string s;
    std::ostringstream ss;
    int hp = ((Player*)en[0])->getHp();
    ss << "HP: " << std::to_string(hp);
    g_Console.writeToBuffer(c, ss.str(), 0x17);
}

void displayCoin()
{
    if (g_eGameState == S_GAME)
    {
        COORD c;
        c.X = (g_Console.getConsoleSize().X / 4) - 10;
        c.Y = 0;
        std::string s;
        std::ostringstream ss;
        int WS = ((Player*)en[0])->getcoin();
        ss << "COIN : " << std::to_string(WS);
        g_Console.writeToBuffer(c, ss.str(), 0x17);
    }
    else if (g_eGameState == S_UPGRADESCREEN)
    {
        COORD c;
        c.X = g_Console.getConsoleSize().X / 2 - 6;
        c.Y = 4;
        std::string s;
        std::ostringstream ss;
        int WS = ((Player*)en[0])->getcoin();
        ss << "COIN : " << std::to_string(WS);
        g_Console.writeToBuffer(c, ss.str(), 0x17);
    }
}

void displayWave()
{
    COORD c;
    c.X = (g_Console.getConsoleSize().X / 4) * 3 ;
    c.Y = 0;
    std::string s;
    std::ostringstream ss;
    int WS = floor(wave);
    ss << "WAVE : " << std::to_string(WS);
    g_Console.writeToBuffer(c, ss.str(), 0x17);
}

void updateWave()
{
    wave++;
    spawnCounter -= 0.01;
}