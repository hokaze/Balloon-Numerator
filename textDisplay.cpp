#include "textDisplay.h"

namespace PPM
{
    TextDisplay::TextDisplay(SDL_Renderer *r) : BaseObject(r)
    {
        collisionBox.x = 250;
        collisionBox.y = 10;
        state = 0;
        questionText = renderText("Is this a placeholder?", "Roboto.ttf", WHITE, 30, r);
        correctText = renderText("But of course!", "Roboto.ttf", WHITE, 30, r);
        wrongText = renderText("Nope...", "Roboto.ttf", WHITE, 30, r);
        sprite = questionText;
        collisionBox.h = 0; collisionBox.w = 0;
        type = "TextDisplay";
    }
    
    TextDisplay::TextDisplay(int x, int y, std::string question, std::string font, SDL_Color col, int size, SDL_Renderer *r) : BaseObject(r)
    {
        collisionBox.x = x;
        collisionBox.y = y;
        state = 0;
        questionText = renderText(question, font, col, size, r);
        correctText = renderText("Well done, that's right!", font, col, size, r);
        wrongText = renderText("Sorry, that's not right.", font, col, size, r);
        sprite = questionText;
        collisionBox.h = 0; collisionBox.w = 0;
        type = "TextDisplay";
    }
    
    TextDisplay::~TextDisplay()
    {
        SDL_DestroyTexture(questionText);
        SDL_DestroyTexture(correctText);
        SDL_DestroyTexture(wrongText);
    }
    
    void TextDisplay::update(SDL_Renderer *r)
    {
        if (state != 0)
        {
            if (state == 1) {sprite = correctText;}
            else if (state == 2) {sprite = wrongText;}
            
            if (questionClock.getStarted() == false) {questionClock.start();}
            else
            {
                int ticksPassed = questionClock.ticks();
                if (ticksPassed > 3000)
                {
                    state = 0;
                    sprite = questionText;
                    questionClock.stop();
                }
            }
        }
        
        renderTexture(sprite, r, collisionBox.x, collisionBox.y);
    }
    
    void TextDisplay::setWrong()
    {
        state = 2;
        //sprite = wrongText;
    }
    
    void TextDisplay::setRight()
    {
        state = 1;
        //sprite = correctText;
    }
}