#ifndef PPM__ENEMY1
#define PPM__ENEMY1

#include "gfx.h"

namespace PPM
{
	class Enemy1
	{
		private:
			// Example values - currently don't do anything
			//const int run_speed = 2, float_speed = 1;
			//const float fall_accel = 0.1, ascend_accel = 0.05;
			// Possible variables to keep track of
			int balloons, score, lives;
			float x_speed, y_speed;
			bool alive, grounded, facingRight;
			SDL_Texture *sprite;
			//SDL_Rect collisionBox; // restore this when collision works properly
		public:
			SDL_Rect collisionBox; // placed in public temporarily to test collision
			Enemy1(SDL_Renderer *r);
			~Enemy1();
			//void move(bool direction); // final move is just left/right
			void move(SDL_Event event); // prototype move is up/down/left/right
			void fall();
			void flap();
			void update(SDL_Renderer *r);
	};
}

#endif