#pragma once
#include <fstream>

class LevelManager {
	static unsigned int nrLevels;
	static unsigned int nrEnmLvl;
	static size_t nrClcLvl;
	static int Lvl[20][25];
	static unsigned int exitLvl[2];
	static unsigned int playerSpawn[2];
	static unsigned int (*clcLvl)[3];

	static std::ifstream campaine;
public:
	static void getData(const char* campaineFile);
	static unsigned int getNrLevels();
	static bool readLevel(unsigned char level);
	static int getNrEnemy();
	static size_t getNrColectables();
	static int(*getMap())[25];
	static unsigned int(*getExit())[2];
	static unsigned int(*getCollectables())[3];
	static void closeLevelManager();
	static unsigned int(*getPlayerSpawn())[2];
};