#include "gfx.h"

namespace PPM
{
	SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer)
	{
		// Loads a texture from file with SDL_image, no need for surface to texture conversion
		SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
		return texture;
	}

	// Non-stretch, original size rendering at position (x, y), whether flipped or not
	void renderTexture(SDL_Texture *tex, SDL_Renderer *renderer, int x, int y, bool facingRight)
	{
		// Destination rectangle of our desired position to render to
		SDL_Rect position;
		position.x = x;
		position.y = y;
		// Check texture for original width and height, use those instead of stretching upon render
		SDL_QueryTexture(tex, NULL, NULL, &position.w, &position.h);
		if (facingRight)
		{
			SDL_RenderCopy(renderer, tex, NULL, &position);
		}
		else
		{
			SDL_RenderCopyEx(renderer, tex, NULL, &position, 0, NULL, SDL_FLIP_HORIZONTAL);
		}
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
}