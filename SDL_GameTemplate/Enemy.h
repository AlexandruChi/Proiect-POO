#pragma once
#include "Character.h"
#include "Timer.h"

class Enemy : public Character {
	unsigned int range;
	unsigned char damage;

	Timer changeDirectionTimer, attackTimer;

	Hitbox hitbox;
public:
	Enemy(const char* path_r, const char* path_l, SDL_Renderer* renderer);
	~Enemy();

	void init() override;
	void update() override;

	Hitbox getHitbox() const;

	void setTravelDirection(TravelDirection travelDirection);
	void follow(const Position& position);
};
