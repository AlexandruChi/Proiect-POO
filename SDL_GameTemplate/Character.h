#pragma once
#include "Component.h"
#include "SDL.h"

constexpr auto characterTextureRight = 0;
constexpr auto characterTextureLeft = 1;

constexpr auto characterDeltaX = 32;
constexpr auto characterDeltaY = 56;

constexpr auto hitboxDeltaX = 32;
constexpr auto hitboxDeltaY = 46;

constexpr auto playerSpawnXLvl1 = 2;
constexpr auto playerSpawnYLvl1 = 4;

constexpr auto playerSpawnXLvl2 = 1;
constexpr auto playerSpawnYLvl2 = 17;

constexpr auto playerSpawnXLvl3 = 2;
constexpr auto playerSpawnYLvl3 = 18;

enum TravelDirection {
	stop, up, down, right, left, up_right, up_left, down_right, down_left
};

struct Position {
	int x, y;
	int xPX, yPX;
	double tmpX, tmpY;
};

struct Hitbox {
	int xPX1, yPX1;
	int xPX2, yPX2;
};

class Character : public Component {
protected:
	SDL_Texture* texture{};
	SDL_Renderer* renderer{};
	SDL_Rect srcRect{}, destRect{};

	SDL_Texture** altTexture{};

	TravelDirection travelDirection;
	Position position;

	double speed;
	unsigned char health, maxHealth;

	bool dead;
public:
	virtual ~Character() = default;
	virtual void init() = 0;
	virtual void update();
	
	void draw();

	void setTex(const char* path_r, const char* path_l);

	void addMovement(TravelDirection travelDirection);
	void subMovement(TravelDirection travelDirection);

	Position getPosition();

	void move();

	void decHealth(unsigned char health);
	void incHealth(unsigned char health);

	bool lineOfSight(const Position& position) const;

	bool isDead();
};