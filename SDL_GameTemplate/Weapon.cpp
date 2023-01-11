#include "Weapon.h"

Weapon::Weapon(unsigned char type, unsigned char damage): type(type), damage(damage) {
    attackTimer = new Timer(0, true);
}

unsigned char Weapon::getType() {
    return type;
}

unsigned char Weapon::getDamage() {
    return damage;
}

Timer* Weapon::getTimer() {
    return attackTimer;
}