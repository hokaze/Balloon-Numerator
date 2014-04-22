#ifndef PPM__ENEMY1
#define PPM__ENEMY1

#include "baseObject.h"
#include "timer.h"

namespace PPM
{
	class Enemy1 : public BaseObject
	{
		protected:
			// Example values - currently don't do anything
			//const int run_speed = 2, float_speed = 1;
			//const float fall_accel = 0.1, ascend_accel = 0.05;
			// Possible variables to keep track of
			int balloons;
			float x_speed, y_speed;
			bool grounded, facingRight;
			int alive; // 1 = alive, 0 = no balloons, -1 = dead
            Timer damageClock;
            SDL_Texture *sprite2, *sprite1, *sprite0;
			// POLY //SDL_Texture *sprite;
			//SDL_Rect collisionBox; // restore this when collision works properly
		public:
			// POLY //SDL_Rect collisionBox; // placed in public temporarily to test collision
			Enemy1(SDL_Renderer *r);
            Enemy1(int x, int y, int heliumSpheres, SDL_Renderer *r);
			~Enemy1();
			//void move(bool direction);
			void move();
            void bounce(int direction);
            void pop(int damage);
			//void fall();
			//void flap();
			virtual void update(SDL_Renderer *r);
            virtual int isAlive();
	};
}

#endif