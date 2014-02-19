#include "baseObject.h"

namespace PPM
{
    BaseObject::BaseObject(SDL_Renderer *r)
    {
        collisionBox.x = 320;
        collisionBox.y = 260;
        sprite = loadTexture("error.png", r);
        SDL_QueryTexture(sprite, NULL, NULL, &collisionBox.w, &collisionBox.h);
    }
    
    BaseObject::BaseObject(int x, int y, std::string image_file, SDL_Renderer *r) 
    {
        collisionBox.x = x;
        collisionBox.y = y;
        sprite = loadTexture(image_file, r);
        SDL_QueryTexture(sprite, NULL, NULL, &collisionBox.w, &collisionBox.h);
    }
    
    BaseObject::~BaseObject()
    {
        SDL_DestroyTexture(sprite);
    }
    
    void BaseObject::update(SDL_Renderer *r)
    {
        // Draw to screen
        renderTexture(sprite, r, collisionBox.x, collisionBox.y);
    }
}