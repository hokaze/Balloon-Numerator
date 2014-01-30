#include "platform.h"

namespace PPM
{
    Platform::Platform(SDL_Renderer *r)
    {
        collisionBox.x = 250;
        collisionBox.y = 250;
        sprite = loadTexture("platform1.png", r);
        SDL_QueryTexture(sprite, NULL, NULL, &collisionBox.w, &collisionBox.h);
    }
    
    Platform::Platform(int x, int y, std::string image_file, SDL_Renderer *r)
    {
        collisionBox.x = x;
        collisionBox.y = y;
        SDL_Texture *charTex = loadTexture(image_file, r);
        collisionBox.w = SDL_QueryTexture(sprite, NULL, NULL, &collisionBox.w, &collisionBox.h);
    }
    
    Platform::~Platform()
    {
        SDL_DestroyTexture(sprite);
    }
    
    void Platform::update(SDL_Renderer *r)
    {
        // Draw to screen
        renderTexture(sprite, r, collisionBox.x, collisionBox.y);
    }
}