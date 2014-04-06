#include "numberBalloon.h"

namespace PPM
{
    NumberBalloon::NumberBalloon(SDL_Renderer *r) : BaseObject(r)
    {
        collisionBox.x = 700;
        collisionBox.y = 200;
        value = 0;
        correct = 0;
        sprite = loadTexture("img/numberBalloon", r);
        text = renderText("0", "Roboto.ttf", {255,255,255}, 18, r);
        SDL_QueryTexture(sprite, NULL, NULL, &collisionBox.w, &collisionBox.h);
        type = "NumberBalloon";
    }
    
    NumberBalloon::NumberBalloon(int x, int y, std::string image_file, std::string number, std::string font, SDL_Color col, int size, bool answer, SDL_Renderer *r) : BaseObject(r)
    {
        collisionBox.x = x;
        collisionBox.y = y;
        value = stoi(number);
        correct = answer;
        sprite = loadTexture(image_file, r);
        text = renderText(number, font, col, size, r);
        SDL_QueryTexture(sprite, NULL, NULL, &collisionBox.w, &collisionBox.h);
        type = "NumberBalloon";
    }
    
    NumberBalloon::~NumberBalloon()
    {
        SDL_DestroyTexture(text);
        SDL_DestroyTexture(sprite);
    }
    
    void NumberBalloon::update(SDL_Renderer *r)
    {
        // Draw to screen
        renderTexture(sprite, r, collisionBox.x, collisionBox.y);
        renderTexture(text, r, collisionBox.x + 5, collisionBox.y + 5);
    }
    
    int NumberBalloon::getValue()
    {
        return value;
    }
    
    bool NumberBalloon::check()
    {
        return correct;
    }
}