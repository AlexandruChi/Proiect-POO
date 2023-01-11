#pragma once
#include "Character.h"
#include "Weapon.h"

class Player : public Character {
	unsigned char collected, medals, kills;

	Weapon* weapon;
	Weapon** altWeapon;
public:
   Player(const char* path_r, const char* path_l, SDL_Renderer* renderer);
   ~Player();

	void init() override;
	void update() override;

	void setUI();

	void attack(const Position& position);

	void addKill();
	void addMedal();
	void addCollected();

	void changeWeapon(unsigned char weapon);
};
