#pragma once
#include "Weapon.h"

class Sword : public Weapon {
	unsigned char range;
	unsigned char damage;

	Timer attackTimer;
public:
	Sword(unsigned char damage, unsigned char range, double attackDelay);
	virtual ~Sword() = default;

	virtual bool hasAmmo(unsigned char& ammo);
	virtual bool hasRange(unsigned char& range);

	virtual void attack(const Component& player, const Position& position);

	unsigned char getType();
	unsigned char getDamage();

	virtual void addAmmo(unsigned char ammo = 1);
	virtual void decAmmo(unsigned char ammo = 1);
};