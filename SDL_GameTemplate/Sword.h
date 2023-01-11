#pragma once
#include "Weapon.h"

class Sword : public Weapon {
	unsigned char range;
public:
	Sword(unsigned char type, unsigned char damage, unsigned char range, double attackDelay);
	virtual ~Sword() = default;

	virtual bool hasAmmo(unsigned char& ammo);
	virtual bool hasRange(unsigned char& range);

	virtual void attack(const Position& position);

	virtual void addAmmo();
	virtual void decAmmo();
};