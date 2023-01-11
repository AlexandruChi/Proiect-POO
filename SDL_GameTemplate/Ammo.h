#pragma once
#include "GameObject.h"

class Ammo : public GameObject {
	unsigned char ammo;
public:
	Ammo(SDL_Renderer* renderer, int x, int y);
	virtual ~Ammo() = default;

	int getAmmo();
};