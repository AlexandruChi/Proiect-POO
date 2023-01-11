#include <utility>
#include <cmath>
#include "Enemy.h"
#include "Map.h"
#include "Player.h"

using namespace std;

long long randomNumber(long long low, long long high);
unsigned long long calculateDistance(pair<long long, long long> A, pair<long long, long long> B);

extern Map* map;

extern Player* player;

constexpr auto moveDelay = 3;
constexpr auto attackDelay = 1;

Enemy::Enemy(const char* path_r, const char* path_l, SDL_Renderer* renderer)
{
    this->renderer = renderer;
    changeDirectionTimer = new Timer(moveDelay, true);
    attackTimer = new Timer(attackDelay, true);
    if (changeDirectionTimer == nullptr) {
        exit(1);
    }
    setTex(path_r, path_l);

    hitbox = {};

    speed = 0.70;
    range = 5 * 32;
    damage = 1;
    maxHealth = 3;
    health = maxHealth;
}

Enemy::~Enemy()
{
    delete changeDirectionTimer;
}

void Enemy::init()
{
    srcRect.x = srcRect.y = 0;
    srcRect.w = srcRect.h = 32;
    destRect.w = destRect.h = 64;

    bool ok = true;

    dead = false;

    do {
        ok = true;

        position.xPX = (unsigned int)randomNumber(36, 768);
        position.yPX = (unsigned int)randomNumber(65, 608);

        if (!map->canWalkOn(position.xPX / 32, position.yPX / 32)) {
            ok = false;
        }

        if (calculateDistance({position.xPX, position.yPX}, {player->getPosition().xPX, player->getPosition().yPX}) <= range) {
            ok = false;
        }
    } while (!ok);

    position.x = position.xPX / 32;
    position.y = position.yPX / 32;

    position.tmpX = position.xPX;
    position.tmpY = position.yPX;
}

void Enemy::update()
{
    if (health == 0) {
        dead = true;
        return;
    }

    if (position.x == player->getPosition().x and position.y == player->getPosition().y) {
        setTravelDirection(stop);
        if (attackTimer->run()) {
            player->decHealth(damage);
        }
    } else if (calculateDistance({ position.xPX, position.yPX }, { player->getPosition().xPX, player->getPosition().yPX }) <= range and lineOfSight(player->getPosition())) {
        follow(player->getPosition());
    } else if (changeDirectionTimer->run()) {
        setTravelDirection((TravelDirection)randomNumber(0, 8));
    }

    Character::update();

    hitbox.xPX1 = position.xPX - hitboxDeltaX / 2;
    hitbox.xPX2 = position.xPX + hitboxDeltaX / 2;
    hitbox.yPX1 = position.yPX - hitboxDeltaY;
    hitbox.yPX2 = position.yPX;
}

Hitbox Enemy::getHitbox() {
    return hitbox;
}

void Enemy::setTravelDirection(TravelDirection travelDirection) {
    this->travelDirection = travelDirection;
}

void Enemy::follow(const Position& position) {
    setTravelDirection(stop);
    if (this->position.x > position.x) {
        addMovement(left);
    } else if (this->position.x < position.x) {
        addMovement(right);
    }
    if (this->position.y > position.y) {
        addMovement(up);
    } else if (this->position.y < position.y) {
        addMovement(down);
    }
}