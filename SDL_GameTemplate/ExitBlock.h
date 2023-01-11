#pragma once
#include "GameObject.h"

class ExitBlock : public GameObject {
public:
	ExitBlock(SDL_Renderer* renderer, int x, int y);
	virtual ~ExitBlock() = default;
};