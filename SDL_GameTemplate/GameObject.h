#pragma once
#include "SDL_image.h"
#include "Character.h"

enum GameObjectType {
	document, ammo, medkit, exitBlock
};

class GameObject
{
public:
	static GameObject** createGameObjects(unsigned int(*v)[3], size_t nr, SDL_Renderer* renderer);

	GameObject(const char* textureSheet, GameObjectType type, SDL_Renderer* renderer, int x, int y);
	virtual ~GameObject();

	GameObject* searchGameObject(GameObject** objects, int x, int y, size_t size);
	void Render();

	GameObjectType getType();

	int getX();
	int getY();

private:
	GameObjectType type;

	int _x;
	int _y;
	SDL_Texture* _texture;
	SDL_Rect _srcRectangle;
	SDL_Rect _destRectangle;
	SDL_Renderer* _renderer;
};