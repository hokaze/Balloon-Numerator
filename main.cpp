// Balloon Numerator //

#include "level.h"
using namespace std;
using namespace PPM;

int main(int argc, char*argv[])
{
	// Initialise SDL video, event, audio, timer, joystick, controller, etc subsystems
	SDL_Init(SDL_INIT_EVERYTHING);
	// Create window to draw to, failure results in NULL
	SDL_Window *window = SDL_CreateWindow("Balloon Numerator", 50, 50, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	// Create 2D renderer for window with default driver, graphics acceleration and current refresh rate
	SDL_Renderer *rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	// Load TTF support
    TTF_Init();
    
	// Load background image files
	SDL_Texture *bgTex = loadTexture("img/background.png", rend);
    SDL_Texture *bgTex2 = loadTexture("img/sunsetBackground.png", rend);
	SDL_Texture *loseLevelTex = loadTexture("img/lose.png", rend);
	SDL_Texture *nextLevelTex = loadTexture("img/win.png", rend);
	
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
	bool loadNextLevel = 0;
    
	// Create our main game objects
    Balloonist* player = new Balloonist(50, 50, rend);
	LevelList MasterList(player, "levels/levels.txt", rend);

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
                        MasterList.currentLevel = -3;
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
							MasterList.setLevel(0);
							MasterList.activeLevel->resetLevel();
							MasterList.setLevel(0);
                        }
                        // Educational level
                        /*else if (menuItem == 2)
                        {
                            menu = false;
                            currentLevel = 2;
                        }*/
                        // Display high score
                        /*else if (menuItem == 3)
                        {
                            // high score popup?
                        }*/
                        // Quit game
                        else if (menuItem == 4)
                        {
                            menu = false;
                            MasterList.currentLevel = -3;
                            running = false;
                        }
                    }
                }
                if (event.type == SDL_QUIT)
                {
                    menu = false;
                    running = false;
                    MasterList.currentLevel = -3;
                }
            }
            
            // Clear renderer, copy texture to it and display
            SDL_RenderClear(rend);
            
            // Render menu
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
        while (MasterList.currentLevel > -1)
        {   
			loadNextLevel = false;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    running = false;
                    menu = false;
                    MasterList.currentLevel = -3;
                }
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                {
                    menu = true;
                    MasterList.currentLevel = -3;
                }
                if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
                {
                    player->move(event);
                }
            }
            
			// IF REGULAR LEVEL
			if (MasterList.educationLevel == 0)
			{
				// Enemy movement and collisions
				for (unsigned int i = 0; i < MasterList.enemyList.size(); ++i)
				{
					if (MasterList.enemyList.at(i)->isAlive() == 1)
					{
						MasterList.enemyList.at(i)->move();

						collide = checkCollision(player->collisionBox, MasterList.enemyList.at(i)->collisionBox);
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
								MasterList.enemyList.at(i)->pop(1);
							}
							player->bounce(collide);
							MasterList.enemyList.at(i)->bounce(enemyCollide);
						}
						// Enemy - Ground bouncing
						for (unsigned int j = 0; j < MasterList.groundList.size(); ++j)
						{
							enemyCollide = 0;
							enemyCollide = checkCollision(MasterList.enemyList.at(i)->collisionBox, MasterList.groundList.at(j)->collisionBox);
							if (enemyCollide) {MasterList.enemyList.at(i)->bounce(enemyCollide);}
						}
						// Enemy - Spiky collisions
						for (unsigned int k = 0; k < MasterList.spikyList.size(); ++k)
                        {
                            enemyCollide = 0;
                            enemyCollide = checkCollision(MasterList.enemyList.at(i)->collisionBox, MasterList.spikyList.at(k)->collisionBox);
                            if (enemyCollide) {MasterList.enemyList.at(i)->pop(1);}
                        }
					}
				}
            }
            
            // Clear renderer, copy texture to it and display
            SDL_RenderClear(rend);
			if (MasterList.educationLevel) {renderTexture(bgTex2, rend, 0, 0);}
			else {renderTexture(bgTex, rend, 0, 0);}
            for (unsigned int i = 0; i < MasterList.objectList.size(); ++i)
            {
                MasterList.objectList.at(i)->update(rend);
            }
            SDL_RenderPresent(rend);
            
            // Player - Ground bouncing
            for (unsigned int j = 0; j < MasterList.groundList.size(); ++j)
            {
                collide = 0;
                collide = checkCollision(player->collisionBox, MasterList.groundList.at(j)->collisionBox);
                if (collide) {player->bounce(collide);}
            }
            // Player - Spiky collisions
            for (unsigned int k = 0; k < MasterList.spikyList.size(); ++k)
            {
                collide = 0;
                collide = checkCollision(player->collisionBox, MasterList.spikyList.at(k)->collisionBox);
                if (collide) {player->pop(1);}
            }

			// IF SUB LEVEL
			if (MasterList.educationLevel == 1)
			{
				if (MasterList.eduCountdown == -1)
				{
					loadNextLevel = true;
				}
				// Player - Balloon collisions
				for (unsigned int i = 0; i < MasterList.numberList.size(); ++i)
				{
					collide = checkCollision(player->collisionBox, MasterList.numberList.at(i)->collisionBox);
					if (collide)
					{
						player->bounce(collide);
						if (MasterList.numberList.at(i)->check())
						{
							MasterList.message->setRight();
							MasterList.eduCountdown = -1;
						}
						else
						{
							MasterList.message->setWrong();
						}
					}
				}
			}

			// IF REGULAR LEVEL
			if (MasterList.educationLevel == 0)
			{
				MasterList.enemyAliveCount = MasterList.enemyCount;
				// Test if all enemies are dead, if so, next level
				for (unsigned int k = 0; k < MasterList.enemyList.size(); ++k)
				{
					if (MasterList.enemyList.at(k)->isAlive() == -1)
					{
						MasterList.enemyAliveCount--;
					}
				}

				if (MasterList.enemyAliveCount < 1)
				{
					loadNextLevel = true;
				}
			}

			if (loadNextLevel)
			{
				MasterList.lastLevel = MasterList.currentLevel;
				MasterList.setLevel(-1);
			}
        }

		// Between level popup/delay
		while (MasterList.currentLevel == -1)
		{
			// Display "level complete" image, wait a few seconds (or poll keyboard input?)
			// then load the next level after the delay (or any keypress)
			renderTexture(nextLevelTex, rend, 0, 0);
			SDL_RenderPresent(rend);
			SDL_Delay(2000);
			if (MasterList.lastLevel + 1 >= MasterList.totalLevels())
			{
				MasterList.setLevel(-3);
				menu = true; // TEMPORARY, return to menu so game doesn't crash when we run out of levels to play
			}
			else
			{
				MasterList.currentLevel = MasterList.lastLevel;
				MasterList.setLevel(MasterList.lastLevel + 1);
			}
		}

		// Gameover popup/delay
		while (MasterList.currentLevel == -2)
		{
			// Display "game over image", wait for input, then return to menu
			renderTexture(loseLevelTex, rend, 0, 0);
			SDL_RenderPresent(rend);
			SDL_Delay(2000);
			MasterList.currentLevel = -3;
			MasterList.lastLevel = 0;
			menu = 1;
		}
    }
	
	// Clean up objects and safely close SDL
	SDL_DestroyTexture(bgTex);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(bgTex2);
	SDL_DestroyTexture(nextLevelTex);
	SDL_DestroyTexture(loseLevelTex);
	SDL_Quit();
	
	return 0;
}