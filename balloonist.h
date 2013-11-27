#ifndef PPM__BALLOONIST
#define PPM__BALLOONIST

#include "common.h"
#include "gfx.h"

namespace PPM
{
	class Balloonist
	{
		private:
			// Example values - currently don't do anything
			//const int run_speed = 2, float_speed = 1;
			//const float fall_accel = 0.1, ascend_accel = 0.05;
			// Possible variables to keep track of
			int balloons, x_pos, y_pos, score, lives;
			float x_speed, y_speed;
			bool alive, grounded;
			SDL_Texture *sprite;
		public:
			Balloonist(SDL_Renderer *r);
			Balloonist(int x, int y, int starting_balloons, int starting_lives, std::string image_file, SDL_Renderer *r);
			~Balloonist();
			//void move(bool direction); // final move is just left/right
			void move(SDL_Event event); // prototype move is up/down/left/right
			void fall();
			void flap();
			void collisions();
			//void kick(Enemy foe); // No "enemy" class exists yet
			//void stomp(Enemy foe);
			void update(SDL_Renderer *r);
	};
}

#endif