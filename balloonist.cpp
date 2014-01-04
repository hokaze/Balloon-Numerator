#include "balloonist.h"

namespace PPM
{
	Balloonist::Balloonist(SDL_Renderer *r)
	{
		collisionBox.x = 50;
		collisionBox.y = 50;
		balloons = 3;
		lives = 3;
		score = 0;
		grounded = false;
		alive = true;
		facingRight = true;
		sprite = loadTexture("balloonist.png", r);
		SDL_QueryTexture(sprite, NULL, NULL, &collisionBox.w, &collisionBox.h);
	}
	
	Balloonist::Balloonist(int x, int y, int starting_balloons, int starting_lives, std::string image_file, SDL_Renderer *r)
	{
		collisionBox.x = 50;
		collisionBox.y = 50;
		balloons = starting_balloons;
		lives = starting_lives;
		score = 0;
		grounded = true;
		alive = true;
		facingRight = true;
		SDL_Texture *charTex = loadTexture(image_file, r);
		collisionBox.w = SDL_QueryTexture(sprite, NULL, NULL, &collisionBox.w, &collisionBox.h);
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
			case SDLK_UP: collisionBox.y -= 5; break;
			case SDLK_DOWN: collisionBox.y += 5; break;
			case SDLK_LEFT: collisionBox.x -= 5; facingRight = false; break;
			case SDLK_RIGHT: collisionBox.x += 5; facingRight = true; break;
		}
		
		// Horizontal screen-wrap
		if (collisionBox.x < -30) {collisionBox.x = 610;}
		else if (collisionBox.x > 610) {collisionBox.x = -30;}
		
		// Vertical screen-bounds
		if (collisionBox.y < 0) {collisionBox.y = 0;}
		else if (collisionBox.y > 390) {collisionBox.y = 390;}
	}
	
	void Balloonist::update(SDL_Renderer *r)
	{
		// Draw to screen
		renderTexture(sprite, r, collisionBox.x, collisionBox.y, facingRight);
		
		// Make horizontal screen-wrap render on both sides of screen
		if (collisionBox.x < 0)
		{
			renderTexture(sprite, r, collisionBox.x + 640, collisionBox.y, facingRight);
		}
		else if (collisionBox.x > 580)
		{
			renderTexture(sprite, r, collisionBox.x - 640, collisionBox.y, facingRight);
		}
	}
}