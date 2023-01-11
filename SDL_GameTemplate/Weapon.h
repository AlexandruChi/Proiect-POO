#pragma once

#include "Timer.h"
#include "Character.h"

class Weapon {
	unsigned char type;
	unsigned char damage;

	Timer* attackTimer;
public:
	Weapon(unsigned char type, unsigned char damage);
	virtual ~Weapon() = default;

	virtual bool hasAmmo(unsigned char& ammo) = 0;
	virtual bool hasRange(unsigned char& range) = 0;
	virtual unsigned char getType();
	virtual unsigned char getDamage();
	virtual Timer* getTimer();

	virtual void addAmmo() = 0;
	virtual void decAmmo() = 0;

	virtual void attack(const Position& position) = 0;
};