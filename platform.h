#ifndef PPM__PLATFORM
#define PPM__PLATFORM

#include "gfx.h"

namespace PPM
{
    class Platform
    {
        private:
            SDL_Texture *sprite;
        public:
            SDL_Rect collisionBox;
            Platform();
            Platform(SDL_Renderer *r);
            Platform(int x, int y, std::string image_file, SDL_Renderer *r);
            ~Platform();
            virtual void update(SDL_Renderer *r);
    };
}

#endif