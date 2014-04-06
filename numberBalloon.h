#ifndef PPM__NUMBERBALLOON
#define PPM__NUMBERBALLOON
#include "baseObject.h"

namespace PPM
{
    class NumberBalloon : public BaseObject
    {
        protected:
            SDL_Texture *text;
            int value;
            bool correct;
        public:
            NumberBalloon(SDL_Renderer *r);
            NumberBalloon(int x, int y, std::string image_file, std::string number, std::string font, SDL_Color col, int size, bool answer, SDL_Renderer *r);
            ~NumberBalloon();
            virtual void update(SDL_Renderer *r);
            std::string getType();
            int getValue();
            bool check();
    };
}

#endif