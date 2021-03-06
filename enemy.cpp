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
		sprite2 = loadTexture("img/enemy/2balloons.png", r);
        sprite1 = loadTexture("img/enemy/1balloon.png", r);
        sprite0 = loadTexture("img/enemy/0balloon.png", r);
        sprite = sprite2;
		SDL_QueryTexture(sprite, NULL, NULL, &collisionBox.w, &collisionBox.h);
        type = "Enemy1";
	}
	
    Enemy1::Enemy1(int x, int y, int heliumSpheres, SDL_Renderer *r) : BaseObject(r)
    {
        collisionBox.x = x;
        collisionBox.y = y;
        balloons = heliumSpheres;
        grounded = false;
        alive = true;
        facingRight = false;
        sprite2 = loadTexture("img/enemy/2balloons.png", r);
        sprite1 = loadTexture("img/enemy/1balloon.png", r);
        sprite0 = loadTexture("img/enemy/0balloon.png", r);
		if (balloons == 2) {sprite = sprite2;}
		else if (balloons == 1) {sprite = sprite1;}
		else {sprite = sprite0;}
        SDL_QueryTexture(sprite, NULL, NULL, &collisionBox.w, &collisionBox.h);
        type = "Enemy1";
    }
	
	Enemy1::~Enemy1()
	{
		SDL_DestroyTexture(sprite2);
        SDL_DestroyTexture(sprite1);
        SDL_DestroyTexture(sprite0);
	}
	
	void Enemy1::move()
	{
        int direction = rand() % 60 + 1;
        if (direction == 1) {x_speed += 1 + (1 * balloons); facingRight = true;}
        else if (direction == 2) {x_speed -= 1 + (1 * balloons); facingRight = false;}
        else if (direction == 60) {y_speed -= 3 * balloons;}
	}
	
    void Enemy1::bounce(int direction)
    {
        if (direction == 1) {x_speed -= 1;} // bounce left
        else if (direction == 2) {x_speed += 1;} // bounce right
        else if (direction == 3) {y_speed += 3;} // bounce down
        else if (direction == 4) {y_speed -= 3;} // bounce up
    }
    
    void Enemy1::pop(int damage)
    {
        int ticksPassed = damageClock.restart();
        // Only take damage if not damaged yet or it's been 1000 ticks (should be about 1 second)
        if (ticksPassed == 0 || ticksPassed > 1000)
        {
            balloons -= damage;
            if (balloons == 2) {sprite = sprite2;}
            else if (balloons == 1) {sprite = sprite1;}
            else {sprite = sprite0;}
        }
    }
	
	void Enemy1::update(SDL_Renderer *r)
	{
        // Gravity
        if (!grounded)
        {
            y_speed += 0.05;
        }

		if (balloons < 1) {alive = 0;} // no balloons = no collision
        
        // Cap speeds
        if (x_speed > 3) {x_speed = 3;}
        else if (x_speed < -3) {x_speed = -3;}
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
        if (collisionBox.y < 0)
        {
            collisionBox.y = 0;
            y_speed = 0;
        }
        else if (collisionBox.y > SCREEN_HEIGHT - collisionBox.h)
        {
            // Only protect from falling off screen if they have balloons
            if (balloons > 0)
            {
                collisionBox.y = SCREEN_HEIGHT - collisionBox.h;
                y_speed = 0;
            }
            else
            {
				if (collisionBox.y > SCREEN_HEIGHT + (collisionBox.h * 2))
				{
					alive = -1;
				}
            }
        }
        
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
	
	int Enemy1::isAlive()
    {
        return alive;
    }
}