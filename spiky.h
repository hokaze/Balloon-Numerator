#ifndef PPM__SPIKY
#define PPM__SPIKY

#include "baseObject.h"

namespace PPM
{
    class Spiky : public BaseObject
    {
        protected:
            bool facingRight;
            int speed;
        public:
            Spiky(SDL_Renderer *r);
            Spiky(int x, int y, bool rightwards, int velocity, SDL_Renderer *r);
            ~Spiky();
            virtual void update(SDL_Renderer *r);
    };
}

#endif