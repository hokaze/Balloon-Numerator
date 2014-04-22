#include "level.h"

namespace PPM
{
	// Level functions

	Level::Level(Balloonist *player, std::string fileline, SDL_Renderer *r)
	{
		creationString = fileline;
		hero = player;
		rend = r;
		createLevel(player, fileline, r);
	}

	Level::~Level()
	{
		for (unsigned int i = 0; i < objectList.size(); ++i)
		{
			delete objectList[i];
		}
	}

	std::vector<BaseObject*> Level::getObjectList()
	{
		return objectList;
	}

	int Level::getPlayerStartX()
	{
		return playerStartX;
	}

	int Level::getPlayerStartY()
	{
		return playerStartY;
	}

	void Level::createLevel(Balloonist *player, std::string fileline, SDL_Renderer *r)
	{
		std::string value1, value2, value3, value4, value5, value6, value7, value8, value9;
		SDL_Color colour;
		void *object;
		std::ifstream levelFile(fileline);
		while (levelFile.good())
		{
			std::getline(levelFile, value1, ';');
			if (value1 == "player")
			{
				getline(levelFile, value2, ';');
				getline(levelFile, value3, ';');
				playerStartX = stoi(value2);
				playerStartY = stoi(value3);
				getline(levelFile, value1);
			}
			else if (value1 == "enemy1")
			{
				getline(levelFile, value2, ';');
				getline(levelFile, value3, ';');
				object = new Enemy1(stoi(value2), stoi(value3), r);
				objectList.push_back(static_cast<Enemy1*>(object));
				getline(levelFile, value1);
			}
			else if (value1 == "ground")
			{
				getline(levelFile, value2, ';');
				getline(levelFile, value3, ';');
				getline(levelFile, value4, ';');
				object = new Platform(stoi(value2), stoi(value3), value4, r);
				objectList.push_back(static_cast<Platform*>(object));
				getline(levelFile, value1);
			}
			else if (value1 == "numberBalloon")
			{
				getline(levelFile, value2, ';');
				getline(levelFile, value3, ';');
				getline(levelFile, value4, ';');
				getline(levelFile, value5, ';');
				getline(levelFile, value6, ';');
				getline(levelFile, value7, ';');
				getline(levelFile, value8, ';');
				getline(levelFile, value9, ';');
				if (value7 == "white") {colour = WHITE;}
				object = new NumberBalloon(stoi(value2), stoi(value3), value4, value5, value6, colour, stoi(value8), !!stoi(value9), r);
				objectList.push_back(static_cast<NumberBalloon*>(object));
				getline(levelFile, value1);
			}
			else if (value1 == "textDisplay")
			{
				getline(levelFile, value2, ';');
				getline(levelFile, value3, ';');
				getline(levelFile, value4, ';');
				getline(levelFile, value5, ';');
				getline(levelFile, value6, ';');
				getline(levelFile, value7, ';');
				if (value6 == "white") {colour = WHITE;}
				object = new TextDisplay(stoi(value2), stoi(value3), value4, value5, colour, stoi(value7), r);
				objectList.push_back(static_cast<TextDisplay*>(object));
				getline(levelFile, value1);
			}
			else
			{
				getline(levelFile, value1);
			}
		}
		levelFile.close();
	}

	void Level::resetLevel()
	{
		for (unsigned int i = 0; i < objectList.size(); ++i)
		{
			delete objectList[i];
		}
		objectList.clear();
		createLevel(hero, creationString, rend);
	}

	// LevelList functions

	LevelList::LevelList(Balloonist *player, std::string filename, SDL_Renderer *r)
	{
		std::string fileString, pathString;
		std::string dirString = "levels/";
		std::ifstream levelFile(filename);
		Level* newLevel = nullptr;
		message = nullptr;
		hero = player;
		currentLevel = 0;
		lastLevel = 0;
		enemyAliveCount = 0;
		educationLevel = 0;
		eduCountdown = 0;

		while (levelFile.good())
		{
			getline(levelFile, fileString);
			pathString = dirString + fileString;
			newLevel = new Level(player, pathString, r);
			levelsContain.push_back(newLevel);
		}
	}

	LevelList::~LevelList()
	{
		for (unsigned int i = 0; i < levelsContain.size(); ++i)
		{
			delete levelsContain[i];
		}
	}

	void LevelList::setLevel(int levelNo)
	{
		enemyAliveCount = 0; educationLevel = 0; eduCountdown = 0; enemyCount = 0;
		lastLevel = currentLevel;
		currentLevel = levelNo;
		// Actually on a normal level
		if (levelNo > -1)
		{
			activeLevel = levelsContain[levelNo];
			hero->startx = levelsContain[levelNo]->getPlayerStartX();
			hero->starty = levelsContain[levelNo]->getPlayerStartY();
			hero->reset();
			// Purge previous lists
			objectList.clear();
			enemyList.clear();
			groundList.clear();
			numberList.clear();
			message = nullptr;
			// Create objectlist
			objectList = activeLevel->getObjectList();
			objectList.push_back(hero);
			// Populate sublists
			for (unsigned int i = 0; i < objectList.size(); ++i)
			{
				if (objectList.at(i)->getType() == "Enemy1")
				{
					enemyList.push_back(dynamic_cast<Enemy1*>(objectList.at(i)));
					enemyCount++;
					enemyAliveCount++;
				}
				else if (objectList.at(i)->getType() == "Platform")
				{
					groundList.push_back(dynamic_cast<Platform*>(objectList.at(i)));
				}
				else if (objectList.at(i)->getType() == "TextDisplay")
				{
					message = dynamic_cast<TextDisplay*>(objectList.at(i));
				}
				else if (objectList.at(i)->getType() == "NumberBalloon")
				{
					numberList.push_back(dynamic_cast<NumberBalloon*>(objectList.at(i)));
					educationLevel = 1;
					eduCountdown = 1;
				}
			}
		}
	}

	int LevelList::totalLevels()
	{
		return levelsContain.size();
	}
}