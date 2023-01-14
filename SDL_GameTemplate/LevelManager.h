#pragma once
#include <fstream>

class LevelManager {
	static unsigned char nrLevels;
	static unsigned char nrEnmLvl;
	static size_t nrClcLvl;
	static int Lvl[20][25];
	static unsigned char exitLvl[2];
	static unsigned char playerSpawn[2];
	static unsigned char (*clcLvl)[3];

	static std::ifstream campaine;
public:
	static void getData(const char* campaineFile);
	static bool readLevel(unsigned char level);
	static int getNrEnemy();
	static size_t getNrColectables();
	static int(*getMap())[25];
	static unsigned char(*getExit())[2];
	static unsigned char(*getCollectables())[3];
	static void closeLevelManager();
};