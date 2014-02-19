#ifndef PPM__BALLOONIST
#define PPM__BALLOONIST

#include "enemy.h"

namespace PPM
{
	class Balloonist : public Enemy1
	{
		//protected:
			// Example values - currently don't do anything
			//const int run_speed = 2, float_speed = 1;
			//const float fall_accel = 0.1, ascend_accel = 0.05;
			// Possible variables to keep track of
			// POLY //int balloons, score, lives;
			// POLY //float x_speed, y_speed;
			// POLY //bool alive, grounded, facingRight;
			// POLY //SDL_Texture *sprite;
			//SDL_Rect collisionBox; // restore this when collision works properly
		public:
			// POLY //SDL_Rect collisionBox; // placed in public temporarily to test collision
			Balloonist(SDL_Renderer *r);
			Balloonist(int x, int y, int starting_balloons, int starting_lives, std::string image_file, SDL_Renderer *r);
			~Balloonist();
			//void move(bool direction); // final move is just left/right
			void move(SDL_Event event); // prototype move is up/down/left/right
            void bounce(int direction);
			// POLY //void fall();
			// POLY //void flap();
			//void kick(Enemy foe);
			//void stomp(Enemy foe);
			virtual void update(SDL_Renderer *r);
	};
}

#endif