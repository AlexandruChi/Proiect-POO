#pragma once
#include <SDL.h>
#include "Component.h"
#include "Map.h"
#include "UI.h"
#include "GameObject.h"
#include "Player.h"

class Game
{
	static Game* game;
	static Component** enemy;;
	static GameObject* exitLevel;

public:
	Game();
	~Game();

	static Map* map;
	static Player* player;
	static UI* ui;
	static GameObject** collectables;

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update() const;
	void render() const;
	void clean() const;

	bool running() const { return isRunning;  }

	static Component* searchHitbox(const Position& position);

	void nextLevel();
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool mouseLeft;
};
