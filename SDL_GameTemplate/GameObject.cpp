#include "GameObject.h"
#include "TextureManager.h"
#include <SDL.h>

#include "Document.h"
#include "Ammo.h"
#include "Medkit.h"

void printError(const char* messege);

GameObject** GameObject::createGameObjects(unsigned int(*v)[3], size_t nr, SDL_Renderer* renderer) {
	GameObject** objects = new GameObject * [nr];
	if (objects == nullptr) {
		printError("Can not create objects");
		exit(1);
	}
	for (size_t i = 0; i < nr; i++) {
		switch (v[i][0]) {
			case document:
				objects[i] = new Document(renderer, v[i][1], v[i][2]);
				if (objects[i] == nullptr) {
					printError("Can not create object Document");
					exit(1);
				}
				break;
			case ammo:
				objects[i] = new Ammo(renderer, v[i][1], v[i][2]);
				if (objects[i] == nullptr) {
					printError("Can not create object Ammo");
					exit(1);
				}
				break;
			case medkit:
				objects[i] = new Medkit(renderer, v[i][1], v[i][2]);
				if (objects[i] == nullptr) {
					printError("Can not create object Medkit");
					exit(1);
				}
				break;
		}
	}
	return objects;
}

GameObject::GameObject(const char* textureSheet, GameObjectType type, SDL_Renderer* renderer, int x, int y) : type(type)
{
   _renderer = renderer;
   _texture = TextureManager::LoadTexture(textureSheet, _renderer);
   _x = x;
   _y = y;

   _srcRectangle.h = 32;
   _srcRectangle.w = 32;
   _srcRectangle.x = 0;
   _srcRectangle.y = 0;

   _destRectangle.x = _x * 32;
   _destRectangle.y = _y * 32;
   _destRectangle.w = 32;
   _destRectangle.h = 32;
}

GameObject::~GameObject() = default;

GameObject* GameObject::searchGameObject(GameObject** objects, int x, int y, size_t size) {
	for (size_t i = 0; i < size; i++) {
		if (objects[i] != nullptr) {
			if (x == objects[i]->_x and y == objects[i]->_y) {
				return objects[i];
			}
		}
	}
	return 0;
}

void GameObject::Render()
{
	SDL_RenderCopy(_renderer, _texture, nullptr, &_destRectangle);
}

GameObjectType GameObject::getType() {
	return type;
}

int GameObject::getX() {
	return _x;
}

int GameObject::getY() {
	return _y;
}
