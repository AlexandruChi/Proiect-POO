#include "Player.h"
#include "Map.h"
#include "UI.h"
#include "Sword.h"
#include "Rifle.h"
#include <utility>
#include "Ammo.h"
#include "Game.h"

using namespace std;

unsigned long long calculateDistance(pair<long long, long long> A, pair<long long, long long> B);



extern size_t nrClc;

Player::Player(const char* path_r, const char* path_l, SDL_Renderer* renderer) {
    this->renderer = renderer;
    setTex(path_r, path_l);

    altWeapon = new Weapon * [2];

    altWeapon[0] = new Sword(1, 128, 0.5);
    altWeapon[1] = new Rifle(2, 0, 0.3);

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
            if (Game::collectables[i] != nullptr) {
                if (Game::collectables[i]->getX() == position.x and Game::collectables[i]->getY() == position.y) {
                    switch (Game::collectables[i]->getType()) {
                        case document:
                            addCollected();
                            delete Game::collectables[i];
                            Game::collectables[i] = nullptr;
                            break;
                        case ammo:
                            altWeapon[1]->addAmmo(((Ammo*)Game::collectables[i])->getAmmo());
                            delete Game::collectables[i];
                            Game::collectables[i] = nullptr;
                            break;
                        case medkit:
                            if (health < maxHealth) {
                                incHealth();
                                delete Game::collectables[i];
                                Game::collectables[i] = nullptr;
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

    Game::ui->setAmmo(weapon->hasAmmo(ammo), ammo);
    Game::ui->setWeapon(weapon->getType());
    Game::ui->setHealth(health);

    if (clcAll) {
        Game::ui->setCollected(2);
    } else {
        switch (collected) {
            case 0:
                Game::ui->setCollected(0);
                break;
            case 1:
                Game::ui->setCollected(1);
                break;
            default:
                break;
        }
    }

    Game::ui->setMedals(medals);
}

void Player::attack(const Position& position) {
    weapon->attack(*this, position);
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

Hitbox Player::getHitbox() const {
    return Hitbox();
}
