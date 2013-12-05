#include "enemy.h"

namespace PPM
{
	Enemy1::Enemy1(SDL_Renderer *r)
	{
		collisionBox.x = 550;
		collisionBox.y = 350;
		balloons = 1;
		grounded = false;
		alive = true;
		facingRight = false;
		sprite = loadTexture("enemy1.png", r);
		collisionBox.w = SDL_QueryTexture(sprite, NULL, NULL, &collisionBox.w, &collisionBox.h);
	}
	
	Enemy1::~Enemy1()
	{
		SDL_DestroyTexture(sprite);
	}
	
	void Enemy1::move(SDL_Event event)
	{
		// Primitive movement
		/*switch(event.key.keysym.sym)
		{
			case SDLK_UP: collisionBox.y -= 5; break;
			case SDLK_DOWN: collisionBox.y += 5; break;
			case SDLK_LEFT: collisionBox.x -= 5; facingRight = false; break;
			case SDLK_RIGHT: collisionBox.x += 5; facingRight = true; break;
		}*/
		
		// Horizontal screen-wrap
		if (collisionBox.x < -30) {collisionBox.x = 610;}
		else if (collisionBox.x > 610) {collisionBox.x = -30;}
		
		// Vertical screen-bounds
		if (collisionBox.y < 0) {collisionBox.y = 0;}
		else if (collisionBox.y > 390) {collisionBox.y = 390;}
	}
	
	void Enemy1::update(SDL_Renderer *r)
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