#ifndef PPM__BASEOBJECT
#define PPM__BASEOBJECT
#include "gfx.h"

namespace PPM
{
    class BaseObject
    {
        protected:
            SDL_Texture *sprite;
        public:
            SDL_Rect collisionBox;
            BaseObject();
            BaseObject(SDL_Renderer *r);
            BaseObject(int x, int y, std::string image_file, SDL_Renderer *r);
            ~BaseObject();
            virtual void update(SDL_Renderer *r);
    };
}

#endif