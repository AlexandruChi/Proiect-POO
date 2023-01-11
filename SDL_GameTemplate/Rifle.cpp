#include "Rifle.h"
#include "Game.h"

extern Game* game;

Rifle::Rifle(unsigned char type, unsigned char damage, unsigned char ammo, double attackDelay) : Weapon(type, damage), ammo(ammo) {
	getTimer()->duration(attackDelay);
}

bool Rifle::hasAmmo(unsigned char& ammo) {
	ammo = this->ammo;
	return true;
}

bool Rifle::hasRange(unsigned char& range) {
	return false;
}

void Rifle::attack(const Position& position) {
	if (getTimer()->run() and ammo) {
		Character* character = game->searchHitbox(position);
		if (character != nullptr) {
			character->decHealth(getDamage());
		}
	}
}

void Rifle::addAmmo() {
	ammo++;
}
void Rifle::decAmmo() {
	if (ammo) {
		ammo--;
	}
}