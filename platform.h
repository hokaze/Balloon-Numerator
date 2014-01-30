#ifndef PPM__PLATFORM
#define PPM__PLATFORM

#include "common.h"
#include "gfx.h"

namespace PPM
{
    class Platform
    {
        private:
            SDL_Texture *sprite;
            //SDL_Rect collisionBox;
        public:
            SDL_Rect collisionBox;
            Platform(SDL_Renderer *r);
            Platform(int x, int y, std::string image_file, SDL_Renderer *r);
            ~Platform();
            //void move(bool direction);
            void update(SDL_Renderer *r);
    };
}

#endif