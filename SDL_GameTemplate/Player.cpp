#include "Player.h"
#include "Map.h"
#include "UI.h"
#include "Sword.h"
#include "Rifle.h"
#include <utility>
#include "Ammo.h"

using namespace std;

unsigned long long calculateDistance(pair<long long, long long> A, pair<long long, long long> B);

extern Map* map;

extern UI* ui;

extern GameObject** collectables;

extern size_t nrClc;

Player::Player(const char* path_r, const char* path_l, SDL_Renderer* renderer) {
    this->renderer = renderer;
    setTex(path_r, path_l);

    altWeapon = new Weapon * [2];

    altWeapon[0] = new Sword(0, 1, 128, 0.5);
    altWeapon[1] = new Rifle(1, 2, 0, 0.3);

    weapon = altWeapon[0];

    maxHealth = 5;
    health = maxHealth;
    collected = 0;
    medals = 0;
    kills = 0;
}

Player::~Player() {}


void Player::init()
{
   srcRect.x = srcRect.y = 0;
   srcRect.w = srcRect.h = 32;
   destRect.w = destRect.h = 64;

   destRect.x = 32;
   destRect.y = 64;

   position.xPX = destRect.x + characterDeltaX;
   position.yPX = destRect.y + characterDeltaY;

   position.tmpX = position.xPX;
   position.tmpY = position.yPX;

   position.x = position.xPX / 32;
   position.y = position.yPX / 32;

   speed = 1;
   dead = false;
}

void Player::update() {
    for (size_t i = 0; i < nrClc; i++) {
        if (collectables[i] != nullptr) {
            if (collectables[i]->getX() == position.x and collectables[i]->getY() == position.y) {
                switch (collectables[i]->getType()) {
                    case document:
                        addCollected();
                        delete collectables[i];
                        collectables[i] = nullptr;
                        break;
                    case ammo:
                        for (unsigned char j = 0; j < ((Ammo*)collectables[i])->getAmmo(); j++) {
                            altWeapon[1]->addAmmo();
                        }
                        delete collectables[i];
                        collectables[i] = nullptr;
                        break;
                    case medkit:
                        if (health < maxHealth) {
                            incHealth(1);
                            delete collectables[i];
                            collectables[i] = nullptr;
                        }
                        break;
                }
            }
        }
    }

    Character::update();
    setUI();
}

void Player::setUI() {
    unsigned char ammo = 0;

    ui->setAmmo(weapon->hasAmmo(ammo), ammo);
    ui->setWeapon(weapon->getType());
    ui->setHealth(health);
    ui->setCollected(collected);
    ui->setMedals(medals);
}

void Player::attack(const Position& position) {
    weapon->decAmmo();
    if (lineOfSight(position)) {
        unsigned char range;
        if (weapon->hasRange(range) and calculateDistance({ this->position.xPX, this->position.yPX }, { position.xPX, position.yPX }) >= range) {
            return;
        }
        weapon->attack(position);
    }
}

void Player::addKill() {
    kills++;

    switch (kills) {
        case 1:
            addMedal();
            break;
        case 3:
            addMedal();
                break;
        case 7:
            addMedal();
            break;
        case 12:
            addMedal();
            break;
    }
}

void Player::addMedal() {
    medals++;
}

void Player::addCollected() {
    collected++;
}

void Player::changeWeapon(unsigned char weapon) {
    this->weapon = altWeapon[weapon];
}
