#include "Rifle.h"
#include "Game.h"

Rifle::Rifle(unsigned char damage, unsigned char ammo, double attackDelay) : ammo(ammo), damage(damage), attackTimer(attackDelay, true) {}

bool Rifle::hasAmmo(unsigned char& ammo) {
	ammo = this->ammo;
	return true;
}

bool Rifle::hasRange(unsigned char& range) {
	return false;
}

void Rifle::attack(const Component& player, const Position& position) {
	if (attackTimer.run() and ammo) {
		decAmmo();
		Component* character = Game::searchHitbox(position);
		if (character != nullptr and (player.lineOfSight(character->getPosition()) or (player.lineOfSight(position) and !(player.getPosition().y > position.y)))) {
			character->decHealth(damage);
		}
	}
}

unsigned char Rifle::getType() {
	return 1;
}

unsigned char Rifle::getDamage() {
	return damage;
}

void Rifle::addAmmo(unsigned char ammo) {
	this->ammo += ammo;
}
void Rifle::decAmmo(unsigned char ammo) {
	this->ammo -= ammo;
}