#include "Sword.h"
#include "Game.h"
#include <utility>

using namespace std;

unsigned long long calculateDistance(pair<long long, long long> A, pair<long long, long long> B);

extern Game* game;

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
		Character* character = game->searchHitbox(position);
		if (character != nullptr and (calculateDistance({ player.getPosition().x, player.getPosition().y}, {position.x, position.y}) or calculateDistance({ player.getPosition().x, player.getPosition().y }, { character->getPosition().x, character->getPosition().y}))) {
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
