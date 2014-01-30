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
		SDL_QueryTexture(sprite, NULL, NULL, &collisionBox.w, &collisionBox.h);
	}
	
	Enemy1::~Enemy1()
	{
		SDL_DestroyTexture(sprite);
	}
	
	void Enemy1::move(SDL_Event event)
	{
		// TODO
	}
	
	void Enemy1::update(SDL_Renderer *r)
	{
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