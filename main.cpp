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
	
	// Event structure for handling input and rendering until closed
	SDL_Event event;
	bool running = true;
    srand(time(NULL));
	
	// Create our objects
    vector<BaseObject*> objectList;
	Balloonist* player = new Balloonist(rend);
	Enemy1* foe = new Enemy1(rend);
    Platform* ground1 = new Platform(-10, 550, "img/platform1.png", rend);
    Platform* ground2 = new Platform(660, 550, "img/platform1.png", rend);
    objectList.push_back(player);
    objectList.push_back(foe);
    objectList.push_back(ground1);
    objectList.push_back(ground2);
	
	cout << "Running..." << endl;
	
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
			{
				player->move(event);
			}
		}
		foe->move();
		
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
		
		// DEBUG - check collisions
		int collide = checkCollision(player->collisionBox, foe->collisionBox);
        int enemyCollide = 0;
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
		// Player - Ground bouncing
		collide = 0;
		collide = checkCollision(player->collisionBox, ground1->collisionBox);
        if (collide) {player->bounce(collide);}
        collide = 0;
        collide = checkCollision(player->collisionBox, ground2->collisionBox);
        if (collide) {player->bounce(collide);}
        // Enemy - Ground bouncing
        enemyCollide = 0;
        enemyCollide = checkCollision(foe->collisionBox, ground1->collisionBox);
        if (enemyCollide) {foe->bounce(enemyCollide);}
        enemyCollide = 0;
        enemyCollide = checkCollision(foe->collisionBox, ground2->collisionBox);
        if (enemyCollide) {foe->bounce(enemyCollide);}
	}
	
	// Clean up objects and safely close SDL
	SDL_DestroyTexture(bgTex);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}