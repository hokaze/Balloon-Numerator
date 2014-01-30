// Balloon game demo code

#include "balloonist.h"
#include "enemy.h"
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
	SDL_Texture *bgTex = loadTexture("background.png", rend);
	
	// Event structure for handling input and rendering until closed
	SDL_Event event;
	bool running = true;
	
	// Create our player and a sample enemy
	Balloonist player(rend);
	Enemy1 foe(rend);
	
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
				player.move(event);
			}
		}
		
		// Clear renderer, copy texture to it and display
		SDL_RenderClear(rend);
		renderTexture(bgTex, rend, 0, 0);
		player.update(rend);
		foe.update(rend);
		SDL_RenderPresent(rend);
		
		// DEBUG - check collisions
		int collide = checkCollision(player.collisionBox, foe.collisionBox);
		if (collide)
		{
			cout << "Collision: ";
			if (collide == 1)
			{
				cout << " LEFT" << endl;
			}
			else if (collide == 2)
			{
				cout << " RIGHT" << endl;
			}
			else if (collide == 3)
			{
				cout << " BELOW" << endl;
			}
			else
			{
				cout << " ABOVE" << endl;
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