#pragma once
#include "Weapon.h"

class Rifle : public Weapon {
	unsigned char ammo;
	unsigned char damage;

	Timer attackTimer;
public:
	Rifle(unsigned char damage, unsigned char ammo, double attackDelay);
	virtual ~Rifle() = default;

	virtual bool hasAmmo(unsigned char& ammo);
	virtual bool hasRange(unsigned char& range);

	virtual void attack(const Component& player, const Position& position);

	unsigned char getType();
	unsigned char getDamage();

	virtual void addAmmo(unsigned char ammo = 1);
	virtual void decAmmo(unsigned char ammo = 1);
};