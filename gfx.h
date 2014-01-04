#ifndef PPM__GFX
#define PPM__GFX

#include "common.h"
#include <math.h> // needed for atan2 in directional collision

namespace PPM
{
	SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *renderer, int x, int y,  bool facingRight = true);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *renderer, int x, int y, int w, int h);
	int checkCollision(SDL_Rect a, SDL_Rect b);
}

#endif
