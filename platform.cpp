#include "platform.h"

namespace PPM
{
    Platform::Platform(SDL_Renderer *r) : BaseObject(r)
    {
        collisionBox.x = 250;
        collisionBox.y = 250;
        sprite = loadTexture("img/platform1.png", r);
        SDL_QueryTexture(sprite, NULL, NULL, &collisionBox.w, &collisionBox.h);
        type = "Platform";
    }
    
    Platform::Platform(int x, int y, std::string image_file, SDL_Renderer *r) : BaseObject(r) 
    {
        collisionBox.x = x;
        collisionBox.y = y;
        sprite = loadTexture(image_file, r);
        SDL_QueryTexture(sprite, NULL, NULL, &collisionBox.w, &collisionBox.h);
        type = "Platform";
    }
    
    Platform::~Platform()
    {
        SDL_DestroyTexture(sprite);
    }
    
    /*void Platform::update(SDL_Renderer *r)
    {
        // Draw to screen
        renderTexture(sprite, r, collisionBox.x, collisionBox.y);
    }*/
}