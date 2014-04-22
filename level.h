#ifndef PPM__LEVEL
#define PPM__LEVEL

#include "balloonist.h"
#include "enemy.h"
#include "platform.h"
#include "numberBalloon.h"
#include "textDisplay.h"
#include "spiky.h"

namespace PPM
{
	class Level
	{
		protected:
			std::vector<BaseObject*> objectList;
			int playerStartX, playerStartY;
			std::string creationString;
			SDL_Renderer* rend; 
			Balloonist* hero;
		public:
			Level(Balloonist *player, std::string fileline, SDL_Renderer *r);
			~Level();
			std::vector<BaseObject*> getObjectList();
			int getPlayerStartX();
			int getPlayerStartY();
			void createLevel(Balloonist* player, std::string fileline, SDL_Renderer *r);
			void resetLevel();
	};

	class LevelList
	{
		protected:
			std::vector<Level*> levelsContain;
			Balloonist* hero;
		public:
			bool educationLevel;
			int currentLevel, lastLevel, enemyCount, enemyAliveCount, eduCountdown;
			Level* activeLevel;
			std::vector<BaseObject*> objectList;
			TextDisplay* message;
			std::vector<Enemy1*> enemyList;
			std::vector<Platform*> groundList;
			std::vector<NumberBalloon*> numberList;
            std::vector<Spiky*> spikyList;
			LevelList(Balloonist *player, std::string filename, SDL_Renderer *r);
			~LevelList();
			void setLevel(int levelNo);
			int totalLevels();
	};
}

#endif