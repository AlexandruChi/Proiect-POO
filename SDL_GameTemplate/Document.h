#pragma once
#include "GameObject.h"

class Document : public GameObject {
public:
	Document(SDL_Renderer* renderer, int x, int y);
	virtual ~Document() = default;
};