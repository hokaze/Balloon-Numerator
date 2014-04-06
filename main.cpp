// Balloon game demo code

#include "balloonist.h"
#include "enemy.h"
#include "platform.h"
#include "numberBalloon.h"
#include "textDisplay.h"
using namespace std;
using namespace PPM;

vector<BaseObject*> loadLevel(Balloonist* player, string filename, SDL_Renderer *r);

int main(int argc, char*argv[])
{
	// Initialise SDL video, event, audio, timer, joystick, controller, etc subsystems
	SDL_Init(SDL_INIT_EVERYTHING);
	// Create window to draw to, failure results in NULL
	SDL_Window *window = SDL_CreateWindow("Balloon Numerator", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	// Create 2D renderer for window with default driver, graphics acceleration and current refresh rate
	SDL_Renderer *rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	// Load TTF support
    TTF_Init();
    
	// Load background image file
	SDL_Texture *bgTex = loadTexture("img/background.png", rend);
    SDL_Texture *bgTex2 = loadTexture("img/sunsetBackground.png", rend);
	
	// Event structure for handling input and rendering until closed
	SDL_Event event;
    
    srand(time(NULL));
	bool running = true;
    bool menu = true;
    
    int collide = 0;
    int enemyCollide = 0;
	
    // Create menu objects
    SDL_Texture *menuBG = loadTexture("img/menuBackground.png", rend);
    SDL_Texture *menuSelect = loadTexture("img/menuSelector.png", rend);
    int menuItem = 1;
    const int menuItemLast = 4;
    int level = 0;
    
	// Create our main game objects
    Balloonist* player = new Balloonist(50, 50, rend);
    vector<BaseObject*> objectList = loadLevel(player, "levels/main1.txt", rend);
    objectList.push_back(player);
    vector<Enemy1*> enemyList;
    vector<Platform*> groundList;
    
    // Populate sublists
    for (int i = 0; i < objectList.size(); ++i)
    {
        if (objectList.at(i)->getType() == "Enemy1")
        {
            enemyList.push_back(dynamic_cast<Enemy1*>(objectList.at(i)));
        }
        else if (objectList.at(i)->getType() == "Platform")
        {
            groundList.push_back(dynamic_cast<Platform*>(objectList.at(i)));
        }
    }
    
    // Subgame objects
    vector<BaseObject*> objectList2 = loadLevel(player, "levels/sub1.txt", rend);
    objectList2.push_back(player);
    vector<NumberBalloon*> numberList2;
    vector<Platform*> groundList2;
    TextDisplay* message;
    
    // Populate subgame sublists
    for (int i = 0; i < objectList2.size(); ++i)
    {
        if (objectList2.at(i)->getType() == "NumberBalloon")
        {
            numberList2.push_back(dynamic_cast<NumberBalloon*>(objectList2.at(i)));
        }
        else if (objectList2.at(i)->getType() == "Platform")
        {
            groundList2.push_back(dynamic_cast<Platform*>(objectList2.at(i)));
        }
        else if (objectList2.at(i)->getType() == "TextDisplay")
        {
            message = dynamic_cast<TextDisplay*>(objectList2.at(i));
        }
    }
	
	cout << "Running..." << endl;
	
	while (running)
	{
        // MENU LOOP //
        
        while (menu)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        menu = false;
                        level = -1;
                        running = false;
                    }
                    if (event.key.keysym.sym == SDLK_UP)
                    {
                        if (menuItem > 1) {menuItem--;}
                    }
                    if (event.key.keysym.sym == SDLK_DOWN)
                    {
                        if (menuItem < menuItemLast) {menuItem++;}
                    }
                    if (event.key.keysym.sym == SDLK_RETURN)
                    {
                        // Normal level
                        if (menuItem == 1)
                        {
                            menu = false;
                            level = 1;
                        }
                        // Educational level
                        else if (menuItem == 2)
                        {
                            menu = false;
                            level = 2;
                        }
                        // Display high score
                        /*else if (menuItem == 3)
                        {
                            // high score popup?
                        }*/
                        // Quit game
                        else if (menuItem == 4)
                        {
                            menu = false;
                            level = -1;
                            running = false;
                        }
                    }
                }
                if (event.type == SDL_QUIT)
                {
                    menu = false;
                    running = false;
                    level = -1;
                }
            }
            
            // Clear renderer, copy texture to it and display
            SDL_RenderClear(rend);
            
            // Render meny
            renderTexture(menuBG, rend, 0, 0);
            if (menuItem == 1)
            {
                renderTexture(menuSelect, rend, 0, 200);
            }
            else if (menuItem == 2)
            {
                renderTexture(menuSelect, rend, 0, 290);
            }
            else if (menuItem == 3)
            {
                renderTexture(menuSelect, rend, 0, 385);
            }
            else if (menuItem == 4)
            {
                renderTexture(menuSelect, rend, 0, 475);
            }
            SDL_RenderPresent(rend);
        }
        
        
        // MAIN GAME LOOP //
        
        // Start Game
        while (level == 1)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    running = false;
                    menu = false;
                    level = -1;
                }
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                {
                    menu = true;
                    level = 0;
                }
                if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
                {
                    player->move(event);
                }
            }
            
            // Enemy movement and collisions
            for (int i = 0; i < enemyList.size(); ++i)
            {
                if (enemyList.at(i)->isAlive())
                {
                    enemyList.at(i)->move();
                }
                collide = checkCollision(player->collisionBox, enemyList.at(i)->collisionBox);
                enemyCollide = 0;
                if (collide)
                {
                    if (collide == 1)
                    {
                        enemyCollide = 2;
                    }
                    else if (collide == 2)
                    {
                        enemyCollide = 1;
                    }
                    else if (collide == 3)
                    {
                        enemyCollide = 4;
                        player->pop(1);
                    }
                    else
                    {
                        enemyCollide = 3;
                        enemyList.at(i)->pop(1);
                    }
                    player->bounce(collide);
                    enemyList.at(i)->bounce(enemyCollide);
                }
                // Enemy - Ground bouncing
                for (int j = 0; j < groundList.size(); ++j)
                {
                    enemyCollide = 0;
                    enemyCollide = checkCollision(enemyList.at(i)->collisionBox, groundList.at(j)->collisionBox);
                    if (enemyCollide) {enemyList.at(i)->bounce(enemyCollide);}
                }
            }
            
            // Clear renderer, copy texture to it and display
            SDL_RenderClear(rend);
            renderTexture(bgTex, rend, 0, 0);
            for (int i = 0; i < objectList.size(); ++i)
            {
                objectList.at(i)->update(rend);
            }
            SDL_RenderPresent(rend);
            
            // Player - Ground bouncing
            for (int j = 0; j < groundList.size(); ++j)
            {
                collide = 0;
                collide = checkCollision(player->collisionBox, groundList.at(j)->collisionBox);
                if (collide) {player->bounce(collide);}
            }   
        }
        
        // SUB GAME LOOP //
        while (level == 2)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    running = false;
                    menu = false;
                    level = -1;
                }
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                {
                    menu = true;
                    level = 0;
                }
                if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
                {
                    player->move(event);
                }
            }
            
            // Clear renderer, copy texture to it and display
            SDL_RenderClear(rend);
            renderTexture(bgTex2, rend, 0, 0);
            for (int i = 0; i < objectList2.size(); ++i)
            {
                objectList2.at(i)->update(rend);
            }
            SDL_RenderPresent(rend);
            
            // Player - Ground bouncing
            for (int j = 0; j < groundList2.size(); ++j)
            {
                collide = 0;
                collide = checkCollision(player->collisionBox, groundList2.at(j)->collisionBox);
                if (collide) {player->bounce(collide);}
            }
            
            // Player - Balloon collisions
            for (int i = 0; i < numberList2.size(); ++i)
            {
                collide = checkCollision(player->collisionBox, numberList2.at(i)->collisionBox);
                if (collide)
                {
                    player->bounce(collide);
                    if (numberList2.at(i)->check())
                    {
                        message->setRight();
                    }
                    else
                    {
                        message->setWrong();
                    }
                }
            }
        }
    }
	
	// Clean up objects and safely close SDL
	SDL_DestroyTexture(bgTex);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}

// EXPERIMENTAL LEVEL LOADER
vector<BaseObject*> loadLevel(Balloonist* player, string filename, SDL_Renderer *r)
{
    vector <BaseObject*> levelContains;
    string value1, value2, value3, value4, value5, value6, value7, value8, value9;
    SDL_Color colour;
    void *object;
    ifstream levelFile(filename);
    while (levelFile.good())
    {
        getline(levelFile, value1, ';');
        if (value1 == "player")
        {
            getline(levelFile, value2, ';');
            getline(levelFile, value3, ';');
            player->startx = stoi(value2);
            player->starty = stoi(value3);
            player->reset();
            getline(levelFile, value1);
        }
        else if (value1 == "enemy1")
        {
            getline(levelFile, value2, ';');
            getline(levelFile, value3, ';');
            object = new Enemy1(stoi(value2), stoi(value3), r);
            levelContains.push_back(static_cast<Enemy1*>(object));
            getline(levelFile, value1);
        }
        else if (value1 == "ground")
        {
            getline(levelFile, value2, ';');
            getline(levelFile, value3, ';');
            getline(levelFile, value4, ';');
            object = new Platform(stoi(value2), stoi(value3), value4, r);
            levelContains.push_back(static_cast<Platform*>(object));
            getline(levelFile, value1);
        }
        else if (value1 == "numberBalloon")
        {
            getline(levelFile, value2, ';');
            getline(levelFile, value3, ';');
            getline(levelFile, value4, ';');
            getline(levelFile, value5, ';');
            getline(levelFile, value6, ';');
            getline(levelFile, value7, ';');
            getline(levelFile, value8, ';');
            getline(levelFile, value9, ';');
            if (value7 == "white") {colour = {255,255,255};}
            object = new NumberBalloon(stoi(value2), stoi(value3), value4, value5, value6, colour, stoi(value8), stoi(value9), r);
            levelContains.push_back(static_cast<NumberBalloon*>(object));
            getline(levelFile, value1);
        }
        else if (value1 == "textDisplay")
        {
            getline(levelFile, value2, ';');
            getline(levelFile, value3, ';');
            getline(levelFile, value4, ';');
            getline(levelFile, value5, ';');
            getline(levelFile, value6, ';');
            getline(levelFile, value7, ';');
            if (value6 == "white") {colour = {255,255,255};}
            object = new TextDisplay(stoi(value2), stoi(value3), value4, value5, colour, stoi(value7), r);
            levelContains.push_back(static_cast<TextDisplay*>(object));
            getline(levelFile, value1);
        }
        else
        {
            getline(levelFile, value1);
        }
    }
    
    return levelContains;
}