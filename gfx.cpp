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
	
	// SDL_Rect based collision checking. 0 = no collide. 1 = a overlaps left of b.
	// 2 = a overlaps top of b. 3 = a overlaps right of b. 4 = a overlaps bottom of b.
	bool checkCollision(SDL_Rect a, SDL_Rect b)
	{
		// Sides of the rectangles
		int left_a, right_a, top_a, bottom_a;
		int left_b, right_b, top_b, bottom_b;
		
		left_a = a.x;
		right_a = a.x + a.w;
		top_a = a.y;
		bottom_a = a.y + a.h;
		
		left_b = b.x;
		right_b = b.x + b.w;
		top_b = b.y;
		bottom_b = b.y + b.h;
		
		// Checks for A overlapping with B
		if (bottom_a <= top_b)
		{
			return false;
		}

		if (top_a >= bottom_b)
		{
			return false;
		}

		if (right_a <= left_b)
		{
			return false;
		}

		if (left_a >= right_b)
		{
			return false;
		}

		// If none of the sides from A are outside B
		return true;
	}
}