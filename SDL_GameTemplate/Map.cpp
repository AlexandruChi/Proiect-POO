#include "Map.h"
#include "TextureManager.h"

#include "Levels.h"

#include "LevelManager.h"

Map::Map(SDL_Renderer* renderer)
{
	this->renderer = renderer;

	water = TextureManager::LoadTexture("assets/water.png", renderer);
	ground = TextureManager::LoadTexture("assets/ground.png", renderer);
	flooring = TextureManager::LoadTexture("assets/flooring.png", renderer);
	wall = TextureManager::LoadTexture("assets/wall.png", renderer);
	bridge = TextureManager::LoadTexture("assets/bridge.png", renderer);
	bridge_r = TextureManager::LoadTexture("assets/bridge_r.png", renderer);

	curentMap = 1;

	LoadMap(lvl1);

	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;
	dest.x = 0;
	dest.y = 0;
	dest.w = 32;
	dest.h = 32;

}

Map::~Map() {}

void Map::LoadMap(int arr[20][25])
{
	for (int row = 0; row < 20; row++) {
		for (int column = 0; column < 25; column++) {
			map[row][column] = arr[row][column];
		}
	}
}

void Map::DrawMap()
{
	int type = 0;
	for (int row = 0; row < 20; row++) {
		for (int column = 0; column < 25; column++) {
			type = map[row][column];

			dest.x = column * 32;
			dest.y = row * 32;
			switch (type) {
				case 0:
				{
					TextureManager::Draw(this->water, src, dest, renderer);
					break;
				}
				case 1:
				{
					TextureManager::Draw(this->ground, src, dest, renderer);
					break;
				}
				case 2:
				{
					TextureManager::Draw(this->flooring, src, dest, renderer);
					break;
				}
				case 3:
				{
					TextureManager::Draw(this->wall, src, dest, renderer);
					break;
				}
				case 4:
				{
					TextureManager::Draw(this->bridge, src, dest, renderer);
					break;
				}
				case 5:
					TextureManager::Draw(this->bridge_r, src, dest, renderer);
					break;
				default:
					break;
			}
		}
	}
}

bool Map::loadNextMap() {
	if (curentMap == nrLevels) {
		return false;
	}
	curentMap++;
	switch (curentMap) {
		case 2:
			LoadMap(lvl2);
			break;
		case 3:
			LoadMap(lvl3);
			break;
	}
	return true;
}

unsigned char Map::getCurentMap() {
	return curentMap;
}

unsigned char Map::getNrEnemy() {
	switch (curentMap) {
		case 1:
			return nrEnmLvl1;
			break;
		case 2:
			return nrEnmLvl2;
			break;
		case 3:
			return nrEnmLvl3;
			break;
		default:
			return 0;
			break;
	}
}

bool Map::canSeeThrew(unsigned int x, unsigned int y) {
	return map[y][x] != ::wall;
}

bool Map::canWalkOn(unsigned int x, unsigned int y) {
	return (map[y][x] != ::water and map[y][x] != ::wall);
}