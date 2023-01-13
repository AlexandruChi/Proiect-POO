#include <cmath>
#include "Character.h"
#include "Map.h"
#include "TextureManager.h"

extern Map* map;

void Character::move() {
    char signX = 0, signY = 0;

    switch (travelDirection) {
        case right:
        case up_right:
        case down_right:
            signX = 1;
            break;
        case left:
        case up_left:
        case down_left:
            signX = -1;
            break;
        case up:
        case down:
        case stop:
            signX = 0;
            break;
    }
    switch (travelDirection) {
        case up:
        case up_right:
        case up_left:
            signY = -1;
            break;
        case down:
        case down_right:
        case down_left:
            signY = 1;
            break;
        case right:
        case left:
        case stop:
            signY = 0;
            break;
    }

    position.tmpX += speed * signX;
    position.tmpY += speed * signY;

    if ((int)position.tmpY / 32 < 2 or (int)position.tmpY / 32 > 18) {
        position.tmpY -= speed * signY;
        signY = 0;
    }

    if ((int)position.tmpX / 32 < 1 or (int)position.tmpX / 32 > 23) {
        position.tmpX -= speed * signX;
        signX = 0;
    }

    if (!map->canWalkOn(((int)position.tmpX) / 32, ((int)position.tmpY) / 32)) {
        position.tmpX -= speed * signX;
        position.tmpY -= speed * signY;

        if (signY and map->canWalkOn(((int)position.tmpX) / 32, ((int)(position.tmpY + speed * signY)) / 32)) {
            position.tmpY += speed * signY;
        }
        if (signX and map->canWalkOn(((int)(position.tmpX + speed * signX)) / 32, ((int)position.tmpY) / 32)) {
            position.tmpX += speed * signX;
        }
    }

    position.xPX = (int)position.tmpX;
    position.yPX = (int)position.tmpY;

    position.x = position.xPX / 32;
    position.y = position.yPX / 32;
}

void Character::decHealth(unsigned char health) {
    while (health and this->health) {
        health--;
        this->health--;
    }
}

void Character::incHealth(unsigned char health) {
    while (health and this->health < maxHealth) {
        health--;
        this->health++;
    }
}

void Character::setTex(const char* path_r, const char* path_l)
{
    altTexture = new SDL_Texture * [2];

    altTexture[0] = TextureManager::LoadTexture(path_r, renderer);
    altTexture[1] = TextureManager::LoadTexture(path_l, renderer);

    texture = altTexture[0];
}

Position Character::getPosition() const {
    return position;
}

void Character::draw()
{
    destRect.x = position.xPX - characterDeltaX;
    destRect.y = position.yPX - characterDeltaY;

    TextureManager::Draw(texture, srcRect, destRect, renderer);
}

void Character::update()
{
    move();

    switch (travelDirection) {
        case down:
        case down_right:
        case up_right:
        case right:
            texture = altTexture[characterTextureRight];
            break;
        case up:
        case up_left:
        case down_left:
        case left:
            texture = altTexture[characterTextureLeft];
            break;
    }
}

bool Character::lineOfSight(const Position& position) const {
    // Bresenham's line algorithm
    int x1 = this->position.xPX, y1 = this->position.yPX, x2 = position.xPX, y2 = position.yPX;
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;

    while (true) {
        if (!map->canSeeThrew(x1 / 32, y1 / 32)) {
            return false;
        }

        if (x1 == x2 && y1 == y2) {
            break;
        }

        int e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y1 += sy;
        }
    }

    return true;
}

bool Character::isDead() {
    return dead;
}


void Character::addMovement(TravelDirection travelDirection) {
    if (this->travelDirection == stop) {
        this->travelDirection = travelDirection;
        return;
    }

    switch (travelDirection) {
        case up:
            switch (this->travelDirection) {
                case down:
                    this->travelDirection = stop;
                    break;
                case right:
                    this->travelDirection = up_right;
                    break;
                case left:
                    this->travelDirection = up_left;
                    break;
                case down_right:
                    this->travelDirection = up_right;
                    break;
                case down_left:
                    this->travelDirection = up_left;
                    break;
                default:
                    break;
            }
            break;
        case down:
            switch (this->travelDirection) {
                case up:
                    this->travelDirection = stop;
                    break;
                case right:
                    this->travelDirection = down_right;
                    break;
                case left:
                    this->travelDirection = down_left;
                    break;
                case up_right:
                    this->travelDirection = down_right;
                    break;
                case up_left:
                    this->travelDirection = down_left;
                    break;
                default:
                    break;
            }
            break;
        case right:
            switch (this->travelDirection) {
                case left:
                    this->travelDirection = stop;
                    break;
                case up:
                    this->travelDirection = up_right;
                    break;
                case down:
                    this->travelDirection = down_right;
                    break;
                case up_left:
                    this->travelDirection = up_right;
                    break;
                case down_left:
                    this->travelDirection = down_right;
                    break;
                default:
                    break;
            }
            break;
        case left:
            switch (this->travelDirection) {
                case right:
                    this->travelDirection = stop;
                    break;
                case up:
                    this->travelDirection = up_left;
                    break;
                case down:
                    this->travelDirection = down_left;
                    break;
                case up_right:
                    this->travelDirection = up_left;
                    break;
                case down_right:
                    this->travelDirection = down_left;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void Character::subMovement(TravelDirection travelDirection) {
    switch (travelDirection) {
        case up:
            switch (this->travelDirection) {
                case up:
                    this->travelDirection = stop;
                    break;
                case up_right:
                    this->travelDirection = right;
                    break;
                case up_left:
                    this->travelDirection = left;
                    break;
            }
            break;
        case down:
            switch (this->travelDirection) {
                case down:
                    this->travelDirection = stop;
                    break;
                case down_right:
                    this->travelDirection = right;
                    break;
                case down_left:
                    this->travelDirection = left;
                    break;
            }
            break;
        case right:
            switch (this->travelDirection) {
                case right:
                    this->travelDirection = stop;
                    break;
                case up_right:
                    this->travelDirection = up;
                    break;
                case down_right:
                    this->travelDirection = down;
                    break;
            }
            break;
        case left:
            switch (this->travelDirection) {
                case left:
                    this->travelDirection = stop;
                    break;
                case up_left:
                    this->travelDirection = up;
                    break;
                case down_left:
                    this->travelDirection = down;
                    break;
            }
            break;
        default:
            break;
    }
}