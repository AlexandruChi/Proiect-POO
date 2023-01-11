#pragma once
#include "Weapon.h"

class Rifle : public Weapon {
	unsigned char ammo;
public:
	Rifle(unsigned char type, unsigned char damage, unsigned char ammo, double attackDelay);
	virtual ~Rifle() = default;

	virtual bool hasAmmo(unsigned char& ammo);
	virtual bool hasRange(unsigned char& range);

	virtual void attack(const Position& position);

	virtual void addAmmo();
	virtual void decAmmo();
};