#include "balloonist.h"

namespace PPM
{
	Balloonist::Balloonist(SDL_Renderer *r)
	{
		x_pos = 0;
		y_pos = 0;
		balloons = 3;
		lives = 3;
		score = 0;
		grounded = false;
		alive = true;
		SDL_Texture *sprite = loadTexture("balloonist.png", r);
	}
	
	Balloonist::Balloonist(int x, int y, int starting_balloons, int starting_lives, std::string image_file, SDL_Renderer *r)
	{
		x_pos = x;
		y_pos = y;
		balloons = starting_balloons;
		lives = starting_lives;
		score = 0;
		grounded = true;
		alive = true;
		SDL_Texture *charTex = loadTexture(image_file, r);
	}
	
	Balloonist::~Balloonist()
	{
		SDL_DestroyTexture(sprite);
	}
	
	void Balloonist::move(SDL_Event event)
	{
		// Primitive movement
		switch(event.key.keysym.sym)
		{
			case SDLK_UP: y_pos -= 5; break;
			case SDLK_DOWN: y_pos += 5; break;
			case SDLK_LEFT: x_pos -= 5; break;
			case SDLK_RIGHT: x_pos += 5; break;
		}
	}
	
	void Balloonist::update(SDL_Renderer *r)
	{
		// Draw to screen
		renderTexture(sprite, r, x_pos, y_pos);
	}
}