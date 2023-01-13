#pragma once

#include "Timer.h"
#include "Component.h"

class Weapon {
public:
	virtual bool hasAmmo(unsigned char& ammo) = 0;
	virtual bool hasRange(unsigned char& range) = 0;

	virtual unsigned char getType() = 0;
	virtual unsigned char getDamage() = 0;

	virtual void addAmmo(unsigned char ammo = 1) = 0;
	virtual void decAmmo(unsigned char ammo = 1) = 0;

	virtual void attack(const Component& player, const Position& position) = 0;
};