#ifndef PPM__PLATFORM
#define PPM__PLATFORM

#include "baseObject.h"

namespace PPM
{
    class Platform : public BaseObject
    {
        //protected:
            // POLY //SDL_Texture *sprite;
        public:
            // POLY //SDL_Rect collisionBox;
            Platform();
            Platform(SDL_Renderer *r);
            Platform(int x, int y, std::string image_file, SDL_Renderer *r);
            ~Platform();
            // POLY //void update(SDL_Renderer *r);
    };
}

#endif