// Balloon game demo code

#include "balloonist.h"
#include "enemy.h"
#include "platform.h"
using namespace std;
using namespace PPM;

int main(int argc, char*argv[])
{
	// Initialise SDL video, event, audio, timer, joystick, controller, etc subsystems
	SDL_Init(SDL_INIT_EVERYTHING);
	// Create window to draw to, failure results in NULL
	SDL_Window *window = SDL_CreateWindow("Balloon Numerator", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	// Create 2D renderer for window with default driver, graphics acceleration and current refresh rate
	SDL_Renderer *rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
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
    vector<BaseObject*> objectList;
    vector<BaseObject*> objectList2;
	Balloonist* player = new Balloonist(rend);
	Enemy1* foe = new Enemy1(rend);
    Platform* ground1 = new Platform(-10, 550, "img/platform1.png", rend);
    Platform* ground2 = new Platform(660, 550, "img/platform1.png", rend);
    objectList.push_back(player);
    objectList.push_back(foe);
    objectList.push_back(ground1);
    objectList.push_back(ground2);
    
    // Subgame objects
    Platform* ground3 = new Platform(-50, 550, "img/platform2.png", rend);
    objectList2.push_back(player);
    objectList2.push_back(ground3);
	
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
            if (foe->isAlive())
            {
                foe->move();
            }
            
            // Clear renderer, copy texture to it and display
            SDL_RenderClear(rend);
            renderTexture(bgTex, rend, 0, 0);
            for (int i = 0; i < objectList.size(); ++i)
            {
                objectList.at(i)->update(rend);
            }
            //player->update(rend);
            //foe->update(rend);
            //ground1->update(rend);
            //ground2->update(rend);
            SDL_RenderPresent(rend);
            
            // Check collisions between player and enemy
            if (foe->isAlive())
            {
                collide = checkCollision(player->collisionBox, foe->collisionBox);
                enemyCollide = 0;
                if (collide)
                {
                    //cout << "Collision: ";
                    if (collide == 1)
                    {
                        enemyCollide = 2;
                        //cout << " LEFT" << endl;
                    }
                    else if (collide == 2)
                    {
                        enemyCollide = 1;
                        //cout << " RIGHT" << endl;
                    }
                    else if (collide == 3)
                    {
                        enemyCollide = 4;
                        player->pop(1);
                        //cout << " BELOW" << endl;
                    }
                    else
                    {
                        enemyCollide = 3;
                        foe->pop(1);
                        //cout << " ABOVE" << endl;
                    }
                    player->bounce(collide);
                    foe->bounce(enemyCollide);
                }
                
                // Enemy - Ground bouncing
                enemyCollide = 0;
                enemyCollide = checkCollision(foe->collisionBox, ground1->collisionBox);
                if (enemyCollide) {foe->bounce(enemyCollide);}
                enemyCollide = 0;
                enemyCollide = checkCollision(foe->collisionBox, ground2->collisionBox);
                if (enemyCollide) {foe->bounce(enemyCollide);}
            }
            
            // Player - Ground bouncing
            collide = 0;
            collide = checkCollision(player->collisionBox, ground1->collisionBox);
            if (collide) {player->bounce(collide);}
            collide = 0;
            collide = checkCollision(player->collisionBox, ground2->collisionBox);
            if (collide) {player->bounce(collide);}
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
            
            // Player collisions
            for (int i = 1; i < objectList2.size(); ++i)
            {
                collide = checkCollision(player->collisionBox, objectList2.at(i)->collisionBox);
                if (collide) {player->bounce(collide);}
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