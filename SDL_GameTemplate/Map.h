#pragma once
#include <SDL_image.h>

class Map {
public:
	Map(SDL_Renderer* renderer);
	~Map();

	void LoadMap(int arr[20][25]);
	void DrawMap();

	bool loadNextMap();
	unsigned char getCurentMap();
	unsigned char getNrEnemy();

	bool canSeeThrew(unsigned int x, unsigned int y);
	bool canWalkOn(unsigned int x, unsigned int y);

private:
	SDL_Renderer* renderer;
	SDL_Rect src, dest;

	SDL_Texture* water;
	SDL_Texture* ground;
	SDL_Texture* flooring;
	SDL_Texture* wall;
	SDL_Texture* bridge;
	SDL_Texture* bridge_r;

	int map[20][25];

	unsigned char curentMap;
};