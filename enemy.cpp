#include "enemy.h"

namespace PPM
{
	Enemy1::Enemy1(SDL_Renderer *r) : BaseObject(r)
	{
		collisionBox.x = 550;
		collisionBox.y = 350;
		balloons = 2;
		grounded = false;
		alive = true;
		facingRight = false;
		sprite = loadTexture("img/enemy1.png", r);
		SDL_QueryTexture(sprite, NULL, NULL, &collisionBox.w, &collisionBox.h);
	}
	
	Enemy1::~Enemy1()
	{
		SDL_DestroyTexture(sprite);
	}
	
	void Enemy1::move()
	{
        int direction = rand() % 60 + 1;
        if (direction == 1) {x_speed += 3; facingRight = true;}
        else if (direction == 2) {x_speed -=3; facingRight = false;}
        else if (direction == 60) {y_speed -= 4;}
	}
	
    void Enemy1::bounce(int direction)
    {
        if (direction == 1) {x_speed -= 2;} // bounce left
        else if (direction == 2) {x_speed += 2;} // bounce right
        else if (direction == 3) {y_speed += 4;} // bounce down
        else if (direction == 4) {y_speed -= 4;} // bounce up
    }
	
	void Enemy1::update(SDL_Renderer *r)
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
        
        // Draw to screen
        renderTexture(sprite, r, collisionBox.x, collisionBox.y, facingRight);
        
		// Horizontal screen-wrap
        if (collisionBox.x < -30) {collisionBox.x = SCREEN_WIDTH - (collisionBox.w / 2);}
        else if (collisionBox.x > SCREEN_WIDTH - (collisionBox.w / 2)) {collisionBox.x = -30;}
        
        // Vertical screen-bounds
        if (collisionBox.y < 0) {collisionBox.y = 0; y_speed = 0;}
        else if (collisionBox.y > SCREEN_HEIGHT - collisionBox.h) {collisionBox.y = SCREEN_HEIGHT - collisionBox.h;}
        
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