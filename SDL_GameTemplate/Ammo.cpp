#include "Ammo.h"

long long randomNumber(long long low, long long high);

Ammo::Ammo(SDL_Renderer* renderer, int x, int y) : GameObject("assets/ammo_1.png", GameObjectType::ammo, renderer, x, y), ammo((unsigned char)randomNumber(3, 10)) {}

int Ammo::getAmmo() {
    return ammo;
}
