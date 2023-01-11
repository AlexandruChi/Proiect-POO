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

    clcAll = false;
}

Player::~Player() {
    delete[] altWeapon;
}


void Player::init()
{
   srcRect.x = srcRect.y = 0;
   srcRect.w = srcRect.h = 32;
   destRect.w = destRect.h = 64;

   position.x = playerSpawnXLvl1;
   position.y = playerSpawnYLvl1;

   position.xPX = position.x * 32 + 32 / 2;
   position.yPX = position.y * 32 + 32 / 2;

   position.tmpX = position.xPX;
   position.tmpY = position.yPX;

   speed = 1;
   dead = false;
}

void Player::update() {

    if (health == 0) {
        dead = true;
    } else {

        if (collected == 3) {
            addMedal();
            clcAll = true;
            collected = 0;
        }

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
    }
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

bool Player::collectedAll() {
    return clcAll;
}

void Player::changeLevel(unsigned char level) {
    clcAll = false;

    switch (level) {
        case 1:
            position.x = playerSpawnXLvl1;
            position.y = playerSpawnYLvl1;
            break;
        case 2:
            position.x = playerSpawnXLvl2;
            position.y = playerSpawnYLvl2;
            break;
        case 3:
            position.x = playerSpawnXLvl3;
            position.y = playerSpawnYLvl3;
            break;
    }

    position.xPX = position.x * 32 + 32 / 2;
    position.yPX = position.y * 32 + 32 / 2;

    position.tmpX = position.xPX;
    position.tmpY = position.yPX;
}

void Player::changeWeapon(unsigned char weapon) {
    this->weapon = altWeapon[weapon];
}
