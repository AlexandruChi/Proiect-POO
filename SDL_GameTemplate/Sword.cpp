#include "Sword.h"
#include "Game.h"
#include <utility>

using namespace std;

unsigned long long calculateDistance(pair<long long, long long> A, pair<long long, long long> B);

Sword::Sword(unsigned char damage, unsigned char range, double attackDelay) : range(range), damage(damage), attackTimer(attackDelay, true) {}

bool Sword::hasAmmo(unsigned char& ammo) {
	return false;
}

bool Sword::hasRange(unsigned char& range) {
	range = this->range;
	return true;
}

void Sword::attack(const Component& player, const Position& position) {
	if (attackTimer.run()) {
		Component* character = Game::searchHitbox(position);
		if (character != nullptr and (calculateDistance({ player.getPosition().xPX, player.getPosition().yPX}, {position.xPX, position.yPX}) <= range or calculateDistance({ player.getPosition().xPX, player.getPosition().yPX }, { character->getPosition().xPX, character->getPosition().yPX}) <= range)) {
			if (player.lineOfSight(character->getPosition()) or (player.lineOfSight(position) and !(player.getPosition().yPX > position.yPX)))
			character->decHealth(getDamage());
		}
	}
}

unsigned char Sword::getType() {
	return 0;
}

unsigned char Sword::getDamage() {
	return damage;
}

void Sword::addAmmo(unsigned char ammo) {}

void Sword::decAmmo(unsigned char ammo) {}
