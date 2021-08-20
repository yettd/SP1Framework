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

int face = 1;
int lastface = 1;
double  g_dElapsedTime;
double  g_dDeltaTime;
float defTime = 5;
float currTime = 0;
int wave = 1;
int maxenemy = 0;
int current = 0;

int ug1 = 5, ug2 = 5, ug3 = 5;
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;

std::vector<bullet*> b;
std::vector<enemy*> e;
std::vector<entity*> en;
std::ostringstream error;
// Game specific variables here
//Player  player;

EGAMESTATES g_eGameState = S_SPLASHSCREEN; // initial state

// Console object
Console g_Console(80, 25, "SP1 Framework");

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
    en.push_back(new enemy);
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
    //memset(g_skKeyEvent, 0, K_COUNT * sizeof(*g_skKeyEvent));
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

void displayScored()
{
    COORD c;
    c.X = 0;
    c.Y = 0;
    std::string s;
    std::ostringstream ss;
    int WS= floor(currTime);
    int hp = ((Player*)en[0])->getHp();
    ss <<"TIME : "<< std::to_string(WS)<<"  HP:"<< std::to_string(hp);

    g_Console.writeToBuffer(c, ss.str(), 0x17);
}

void updateScord(int s)
{
    currTime += s;
}

void collisionDetection()
{
    int size = en.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i != j)
            {
                if (en[i]->getCoordX() == en[j]->getCoordX() && en[i]->getCoordY() == en[j]->getCoordY())
                {
                    if (en[i]->getTag() == 'P')
                    {
                        if (en[j]->getTag() == 45 || en[j]->getTag() == 'E')
                        {
                            delete en[j];
                            en.erase(en.begin() + j);
                            ((Player*)en[i])->setHp(((Player*)en[i])->getHp() - 1);
                            size = en.size();
                        }
                    }
                    else if (en[i]->getTag() == 'E')
                    {
                        if (en[j]->getTag() == 43)
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

                            delete en[j];
                            delete en[i];

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
                           
                            size = en.size();
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
    if (((Player*)en[0])->getHp() == 0)
    {
        en.clear();
        g_eGameState = S_LOSE;
    }
    if (currTime <= 0)
    {
        g_eGameState = S_UPGRADESCREEN;
    }

    currTime -= 0.01;
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
    rechargeFire();          // sound can be played here too.
    moveEnemy();
    moveBullet();
    enShoot();
    collisionDetection();
   // spawnEnemy();
}

void upgradeScreenInput()
{
    if (g_skKeyEvent[K_NUM1].keyDown)
    {
        if (((Player*)en[0])->getcoin() >= ug1)
        {
            ((Player*)en[0])->setCoin(((Player*)en[0])->getcoin()-ug1);
            float fireRate = en[0]->getFireRate();
            fireRate -= 0.1;
            en[0]->SetFireRate(fireRate);
            currTime = defTime;
            en[0]->setCoordX(g_Console.getConsoleSize().X / 2);
            en[0]->setCoordY(g_Console.getConsoleSize().Y / 2);
            g_eGameState = S_GAME;
            updateWave();
            ((Player*)en[0])->setHp(((Player*)en[0])->getmHp());
            clearEnemy();
            updateMaxenemy();
            spawnEnemy();
            current = 0;
            ug1 += 5;
            error.str("");
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
            ((Player*)en[0])->setCoin(((Player*)en[0])->getcoin() - ug2);
            float speed = en[0]->getSpeed();
            speed += 0.05;
            en[0]->setspeed(speed);
            currTime = defTime;
            en[0]->setCoordX(g_Console.getConsoleSize().X / 2);
            en[0]->setCoordY(g_Console.getConsoleSize().Y / 2);
            g_eGameState = S_GAME;
            updateWave();
            ((Player*)en[0])->setHp(((Player*)en[0])->getmHp());
            clearEnemy();
            updateMaxenemy();
            spawnEnemy();
            current = 0;
            ug2 += 5;
            error.str("");
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
            ((Player*)en[0])->setCoin(((Player*)en[0])->getcoin() - ug3);
            ((Player*)en[0])->setmHp(((Player*)en[0])->getmHp()+1);
            currTime = defTime;
            en[0]->setCoordX(g_Console.getConsoleSize().X / 2);
            en[0]->setCoordY(g_Console.getConsoleSize().Y / 2);
            g_eGameState = S_GAME;
            updateWave();
            ((Player*)en[0])->setHp(((Player*)en[0])->getmHp());
            clearEnemy();
            updateMaxenemy();
            spawnEnemy();
            current = 0;
            ug3 += 5;
            error.str("");
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
        updateWave();
        ((Player*)en[0])->setHp(((Player*)en[0])->getmHp());
        clearEnemy();
        updateMaxenemy();
        spawnEnemy();
        current = 0;
    }
}

void loseScreenInput()
{
    if (g_skKeyEvent[K_SPACE].keyDown)
    {
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
        clearEnemy();
        updateMaxenemy();
        spawnEnemy();
        current = 0;
    }
    else if (g_skKeyEvent[K_ESCAPE].keyDown)
    {
        g_bQuitGame = true;
    }
}

void moveCharacter()
{    
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    if (g_skKeyEvent[K_UP].keyDown && en[0]->getCoordY() > 1)
    {
        face += 1;
        en[0]->movement(1);
    }
    else if (g_skKeyEvent[K_DOWN].keyDown && en[0]->getCoordY() < g_Console.getConsoleSize().Y - 1)
    {
        face -= 1;
        en[0]->movement(2);
    }
    if (g_skKeyEvent[K_LEFT].keyDown && en[0]->getCoordX() > 0)
    {
        face -= 3;
        en[0]->movement(3);
    }
    else if (g_skKeyEvent[K_RIGHT].keyDown && en[0]->getCoordX() < g_Console.getConsoleSize().X - 1)
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
        createBullet(en[0]->getCoordX(), en[0]->getCoordY(),43,lastface);
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
                createBullet(e->getCoordX(), e->getCoordY(), 45, e->shootDir(en[0]->getCoordX(), en[0]->getCoordY()));
                e->SetFireC(0);
                e->setm_bActive(false);
            }
        }
    }
}

void createBullet(int x,int y,char t,int dir)
{
    en.push_back(new bullet(x, y, dir,t));
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
                e->AggresiveAI(en[0]->getCoordX(), en[0]->getCoordY(), g_Console.getConsoleSize().X-1, g_Console.getConsoleSize().Y-1);
            }
            else if (e->getAI() == 2) 
            {
                e->SmartAI(g_Console.getConsoleSize().X-1, g_Console.getConsoleSize().Y-1);
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
        maxenemy = 1;
    }
    else if (wave < 4)
    {
        maxenemy = wave;
    }
    else if (wave < 10)
    {
        maxenemy = ceil(wave + 2);
    }
    else
    {
        maxenemy = ceil(wave + 5);
    }
}

void spawnEnemy()
{

    while (current < maxenemy)
    {
        en.push_back(new enemy);
        current++;
    }
}

void clearEnemy()
{
    en.erase(en.begin() + 1,en.end());
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
    if (en[i]->getCoordX() > g_Console.getConsoleSize().X ||
        en[i]->getCoordY() > g_Console.getConsoleSize().Y ||
        en[i]->getCoordX() < 0 ||
        en[i]->getCoordY() < 0)
    {
        delete en[i];
        en.erase(en.begin() + i);
    }
}

void destroyEnemy(int i)
{
    if (e[i]->getCoordX() > g_Console.getConsoleSize().X ||
        e[i]->getCoordY() > g_Console.getConsoleSize().Y ||
        e[i]->getCoordX() < 0 ||
        e[i]->getCoordY() < 0)
    {
        delete e[i];
        e.erase(e.begin() + i);
    }
    // Collision?
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
    c.X = c.X / 2 - 7;
    g_Console.writeToBuffer(c, "BATTLESHIP", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 8;
    g_Console.writeToBuffer(c, "WASD TO MOVE", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 10;
    g_Console.writeToBuffer(c, "SPACEBAR TO FIRE", 0x09);
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderEntity();
    //renderCharacter();  // renders the character into the buffer
    //renderBullet();
    //renderEnemy();      // renders enemies
    displayScored();
    displayWave();
    displayCoin();
}

void renderUpgradeScreen()
{
    std::ostringstream ss;
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    ss << "Select Upgrade";
    g_Console.writeToBuffer(c, ss.str(), 0x03);
    ss.str("");
    ss << "1. Increase Fire Rate " << "( " << ug1 << " coin )";
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 18;
    g_Console.writeToBuffer(c, ss.str(), 0x09);
    c.Y += 1;
    ss.str("");
    ss <<  "2. Increase Movement Speed" << "( " << ug2 << " coin )";
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c,ss.str(), 0x09);
    c.Y += 1;
    ss.str("");
    ss << "3. Increase Max health" << "( " << ug3 << " coin )";
    c.X = g_Console.getConsoleSize().X / 2 - 18;
    g_Console.writeToBuffer(c, ss.str(), 0x09);
    c.Y += 1;
    ss.str("");
    ss << "4. skip";
    c.X = g_Console.getConsoleSize().X / 2 - 6;
    g_Console.writeToBuffer(c, ss.str(), 0x09);
}

void renderLoseScreen()
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "YOU LOSE", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "SCORE: ", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "PRESS SPACE TO PLAY AGAIN", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "PRESS ESCAPE TO QUIT", 0x09);
}

void renderMap()
{
    //// Set up sample colours, and output shadings
    //const WORD colors[] = {
    //    0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
    //    0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    //};

    //COORD c;
    //for (int i = 0; i < 12; ++i)
    //{
    //    c.X = 5 * i;
    //    c.Y = i + 1;
    //    colour(colors[i]);
    //    g_Console.writeToBuffer(c, " °±²Û", colors[i]);
    //}
}

void renderEntity()
{
    for (int i = 0; i < en.size(); i++)
    {
        WORD charColor= 0x17;
        if (en[i]->getTag() == 'P')
        {
            charColor = 0x17;
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
}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    //if (en[0]->m_bActive)
    //{
    //    charColor = 0x0A;
    //}
    COORD temp;
    temp.X = en[0]->getCoordX();
    temp.Y = en[0]->getCoordY();
    g_Console.writeToBuffer(temp, en[0]->getSym(), 0x17);
}

void renderBullet()
{
    for (int i = 0; i < b.size(); i++)
    {
        COORD temp;
        temp.X = b[i]->getCoordX();
        temp.Y = b[i]->getCoordY();
        g_Console.writeToBuffer(temp, b[i]->getSym(), 0x17);
    }
}

void renderEnemy()
{
    for (int i = 0; i < e.size(); i++)
    {
        COORD temp;
        temp.X = e[i]->getCoordX();
        temp.Y = e[i]->getCoordY();
        g_Console.writeToBuffer(temp, e[i]->getSym(), 0x17);
    }
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

void displayCoin()
{
    if (g_eGameState == S_GAME)
    {
        COORD c;
        c.X = g_Console.getConsoleSize().X / 4;
        c.Y = 0;
        std::string s;
        std::ostringstream ss;
        int WS = ((Player*)en[0])->getcoin();
        ss << "Coin : " << std::to_string(WS);
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
        ss << "Coin : " << std::to_string(WS);
        g_Console.writeToBuffer(c, ss.str(), 0x17);
    }
}


void displayWave()
{
    COORD c;
    c.X = g_Console.getConsoleSize().X/2;
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
}