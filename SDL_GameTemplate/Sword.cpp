#include "Sword.h"
#include "Game.h"

extern Game* game;

Sword::Sword(unsigned char type, unsigned char damage, unsigned char range, double attackDelay): Weapon(type, damage), range(range) {
	getTimer()->duration(attackDelay);
}

bool Sword::hasAmmo(unsigned char& ammo) {
	return false;
}

bool Sword::hasRange(unsigned char& range) {
	range = this->range;
	return true;
}

void Sword::attack(const Position& position) {
	if (getTimer()->run()) {
		Character* character = game->searchHitbox(position);
		if (character != nullptr) {
			character->decHealth(getDamage());
		}
	}
}

void Sword::addAmmo() {}

void Sword::decAmmo() {}
