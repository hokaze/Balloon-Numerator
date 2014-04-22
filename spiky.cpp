#include "spiky.h"

namespace PPM
{
    Spiky::Spiky(SDL_Renderer *r) : BaseObject(r)
    {
        collisionBox.x = 550;
        collisionBox.y = 350;
        facingRight = false;
        speed = 1;
        if (facingRight == false) {speed = -speed;}
        sprite = loadTexture("img/enemy/spiky.png", r);
        SDL_QueryTexture(sprite, NULL, NULL, &collisionBox.w, &collisionBox.h);
        type = "Spiky";
    }
    
    Spiky::Spiky(int x, int y, bool rightwards, int velocity, SDL_Renderer *r) : BaseObject(r)
    {
        collisionBox.x = x;
        collisionBox.y = y;
        facingRight = rightwards;
        speed = velocity;
        if (facingRight == false) {speed = -speed;}
        sprite = loadTexture("img/enemy/spiky.png", r);
        SDL_QueryTexture(sprite, NULL, NULL, &collisionBox.w, &collisionBox.h);
        type = "Spiky";
    }
    
    Spiky::~Spiky()
    {
        SDL_DestroyTexture(sprite);
    }
    
    void Spiky::update(SDL_Renderer *r)
    {
        // Cap speed
        if (speed > 4) {speed = 4;}
        else if (speed < -4) {speed = -4;}
        
        // Update position
        collisionBox.x += speed;
        
        // Draw to screen
        renderTexture(sprite, r, collisionBox.x, collisionBox.y, facingRight);
        
        // Horizontal screen-wrap
        if (collisionBox.x < -23) {collisionBox.x = SCREEN_WIDTH - (collisionBox.w / 2);}
        else if (collisionBox.x > SCREEN_WIDTH - (collisionBox.w / 2)) {collisionBox.x = -23;}
        
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