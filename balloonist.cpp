#include "balloonist.h"

namespace PPM
{
	Balloonist::Balloonist(SDL_Renderer *r)
	{
		collisionBox.x = 50;
		collisionBox.y = 50;
		x_speed = 0;
		y_speed = 0.01;
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
		collisionBox.x = x;
		collisionBox.y = y;
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
		// Smoother movement by using velocities instead of adjusting X and Y directly
		if (event.type == SDL_KEYDOWN)
		{
			// Increment velocity
			switch(event.key.keysym.sym)
			{
				case SDLK_UP: y_speed = -8; break;
				//case SDLK_DOWN: y_speed = 4; break;
				case SDLK_LEFT: x_speed -= 8; facingRight = false; break;
				case SDLK_RIGHT: x_speed += 8; facingRight = true; break;
			}
		}
		if (event.type == SDL_KEYUP)
		{
			// Negate velocity
			switch(event.key.keysym.sym)
			{
				case SDLK_UP: y_speed += 2; break;
				//case SDLK_DOWN: y_speed -= 3; break;
				case SDLK_LEFT: x_speed += 3; break;
				case SDLK_RIGHT: x_speed -= 3; break;
			}
		}
	}
	
	void Balloonist::bounce(int direction)
    {
        if (direction == 1) {x_speed -= 2;} // bounce left
        else if (direction == 2) {x_speed += 2;} // bounce right
        else if (direction == 3) {y_speed += 4;} // bounce down
        else if (direction == 4) {y_speed -= 4;} // bounce up
    }
	
	void Balloonist::update(SDL_Renderer *r)
	{
		// Gravity
		if (!grounded)
		{
			y_speed += 0.05;
		}
		
		// Cap speeds
		if (x_speed > 4) {x_speed = 4;}
		else if (x_speed < -4) {x_speed = -4;}
		if (y_speed > 4) {y_speed = 4;}
		else if (y_speed < -4) {y_speed = -4;}
		
		// Update position
		collisionBox.x += x_speed;
		collisionBox.y += y_speed;
		
		// Horizontal screen-wrap
		if (collisionBox.x < -30) {collisionBox.x = SCREEN_WIDTH - (collisionBox.w / 2);}
		else if (collisionBox.x > SCREEN_WIDTH - (collisionBox.w / 2)) {collisionBox.x = -30;}
		
		// Vertical screen-bounds
		if (collisionBox.y < 0) {collisionBox.y = 0; y_speed = 0;}
		else if (collisionBox.y > SCREEN_HEIGHT - collisionBox.h) {collisionBox.y = SCREEN_HEIGHT - collisionBox.h;}
		
		// Draw to screen
		renderTexture(sprite, r, collisionBox.x, collisionBox.y, facingRight);
		
		// Make horizontal screen-wrap render on both sides of screen
		if (collisionBox.x < 0)
		{
			renderTexture(sprite, r, collisionBox.x + SCREEN_WIDTH, collisionBox.y, facingRight);
		}
		else if (collisionBox.x > SCREEN_WIDTH - collisionBox.w)
		{
			renderTexture(sprite, r, collisionBox.x - SCREEN_WIDTH, collisionBox.y, facingRight);
		}
	}
}