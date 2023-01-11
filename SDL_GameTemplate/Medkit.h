#pragma once
#include "GameObject.h"

class Medkit : public GameObject {
public:
	Medkit(SDL_Renderer* renderer, int x, int y);
	virtual ~Medkit() = default;
};