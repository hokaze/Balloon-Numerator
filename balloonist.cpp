#include "balloonist.h"

namespace PPM
{
	Balloonist::Balloonist(SDL_Renderer *r)
	{
		x_pos = 50;
		y_pos = 50;
		balloons = 3;
		lives = 3;
		score = 0;
		grounded = false;
		alive = true;
		sprite = loadTexture("balloonist.png", r);
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
		
		// Horizontal screen-wrap
		if (x_pos < -30) {x_pos = 610;}
		else if (x_pos > 610) {x_pos = -30;}
		
		// Vertical screen-bounds
		if (y_pos < 0) {y_pos = 0;}
		else if (y_pos > 390) {y_pos = 390;}
	}
	
	void Balloonist::update(SDL_Renderer *r)
	{
		// Draw to screen
		renderTexture(sprite, r, x_pos, y_pos);
		
		// Make horizontal screen-wrap render on both sides of screen
		if (x_pos < 0)
		{
			renderTexture(sprite, r, x_pos + 640, y_pos);
		}
		else if (x_pos > 580)
		{
			renderTexture(sprite, r, x_pos - 640, y_pos);
		}
	}
}