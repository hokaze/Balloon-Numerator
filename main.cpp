// Balloon game demo code
// v0.01 - Starting with SDL 2.0

// Visual Studio needs slightly different include statements
#ifdef _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
#endif
// Normal SDL includes for other platforms/compilers
#ifndef _WIN32
	#include "SDL2/SDL.h"
	#include "SDL2/SDL_image.h"
#endif
#include <string>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Texture* loadTexture(const string &file, SDL_Renderer *renderer);
void renderTexture(SDL_Texture *tex, SDL_Renderer *renderer, int x, int y);
void renderTexture(SDL_Texture *tex, SDL_Renderer *renderer, int x, int y, int w, int h);

int main()
{
	// Initialise SDL video, event, audio, timer, joystick, controller, etc subsystems
	SDL_Init(SDL_INIT_EVERYTHING);
	// Create window to draw to, failure results in NULL
	SDL_Window *window = SDL_CreateWindow("Balloon", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	// Create 2D renderer for window with default driver, graphics acceleration and current refresh rate
	SDL_Renderer *rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	// Load image files
	SDL_Texture *bgTex = loadTexture("background.png", rend);
	SDL_Texture *charTex = loadTexture("balloonist.png", rend);
	
	// Event structure for handling input and rendering until closed
	SDL_Event event;
	bool running = true;
	int charX = 0;
	int charY = 380;
	
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			if (event.type == SDL_KEYDOWN)
			{
				// Primitive movement
				switch(event.key.keysym.sym)
				{
					case SDLK_UP: charY -= 5; break;
					case SDLK_DOWN: charY += 5; break;
					case SDLK_LEFT: charX -= 5; break;
					case SDLK_RIGHT: charX += 5; break;
				}
			}
		}
		
		// Clear renderer, copy texture to it and display
		SDL_RenderClear(rend);
		renderTexture(bgTex, rend, 0, 0);
		renderTexture(charTex, rend, charX, charY);
		SDL_RenderPresent(rend);
	}
	
	// Clean up objects and safely close SDL
	SDL_DestroyTexture(bgTex);
	SDL_DestroyTexture(charTex);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}

SDL_Texture* loadTexture(const string &file, SDL_Renderer *renderer)
{
	// Loads a texture from file with SDL_image, no need for surface to texture conversion
	SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
	return texture;
}

// Non-stretch, original size rendering at position (x, y)
void renderTexture(SDL_Texture *tex, SDL_Renderer *renderer, int x, int y)
{
	// Destination rectangle of our desired position to render to
	SDL_Rect position;
	position.x = x;
	position.y = y;
	// Check texture for original width and height, use those instead of stretching upon render
	SDL_QueryTexture(tex, NULL, NULL, &position.w, &position.h);
	SDL_RenderCopy(renderer, tex, NULL, &position);
}

// Stretches to size specified by width (w) and height (h) at position (x, y)
void renderTexture(SDL_Texture *tex, SDL_Renderer *renderer, int x, int y, int w, int h)
{
	SDL_Rect position;
	position.x = x;
	position.y = y;
	position.w = w;
	position.h = h;
	SDL_RenderCopy(renderer, tex, NULL, &position);
}