#ifndef PPM__TEXTDISPLAY
#define PPM__TEXTDISPLAY

#include "baseObject.h"
#include "timer.h"

namespace PPM
{
    class TextDisplay : public BaseObject
    {
        protected:
            SDL_Texture *questionText;
            SDL_Texture *correctText;
            SDL_Texture *wrongText;
            int state;
            Timer questionClock;
        public:
            TextDisplay(SDL_Renderer *r);
            TextDisplay(int x, int y, std::string question, std::string font, SDL_Color col, int size, SDL_Renderer *r);
            ~TextDisplay();
            virtual void update(SDL_Renderer *r);
            void setWrong();
            void setRight();
    };
}

#endif