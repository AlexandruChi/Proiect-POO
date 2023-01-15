#include "Game.h"
#include <iostream>
#include "Map.h"
#include "Player.h"
#include "UI.h"
#include "Enemy.h"
#include "GameObject.h"
#include "ExitBlock.h"
#include "LevelManager.h"
#include <algorithm>

void printError(const char* messege);
bool sortComponents(Component* component1, Component* component2);

using namespace std;

Component** Game::enemy;
GameObject** Game::collectables;
GameObject* Game::exitLevel;
UI* Game::ui;
Map* Game::map;
Player* Game::player;

TextureUI_path setUIpaths();

Game::Game(): isRunning(false), window(nullptr), renderer(nullptr), mouseLeft(false), nrEnemy(0), nrClc(0), exitLvl(0), clcLvl(0), aspectRatio(0) {}

Game::~Game()
{
	if (player != nullptr) {
		delete player;
		player = nullptr;
	}
	if (map != nullptr) {
		delete map;
		map = nullptr;
	}
	if (map != nullptr) {
		delete ui;
		ui = nullptr;
	}
	if (enemy != nullptr) {
		delete[] enemy;
		enemy = nullptr;
	}
	if (collectables != nullptr) {
		delete[] collectables;
		collectables = nullptr;
	}

   TTF_Quit();
}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = SDL_WINDOW_RESIZABLE;

	if (fullscreen) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 and TTF_Init() == 0)
	{
		std::cout << "Subsystems initialized" << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window!=nullptr)
		{
			std::cout << "Window created" << std::endl;
		} else {
			printError(SDL_GetError());
		}
 
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer != nullptr)
		{
			if (fullscreen) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			} else {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}
			std::cout << "Renderer created" << std::endl;
		} else {
			printError(SDL_GetError());
		}

		isRunning = true;
	}
	else
	{
		printError(SDL_GetError());
		isRunning = false;
	}

	SDL_RenderSetLogicalSize(renderer, 800, 640);

	aspectRatio = 800. / 640;

	map = new Map(renderer);
	if (map == nullptr) {
		printError("Can not create map");
		exit(1);
	}


    player = new Player ("assets/player.png", "assets/player_r.png", renderer);
	if (player == nullptr) {
		printError("Can not create player");
		exit(1);
	}
    player->init();

    TextureUI_path textureUI_path = setUIpaths();
    ui = new UI(&textureUI_path, renderer);

	nrEnemy = map->getNrEnemy();
	enemy = new Component * [nrEnemy];
	if (enemy == nullptr) {
		printError("Can not create enemys");
		exit(1);
	}
	for (unsigned char i = 0; i < nrEnemy; i++) {
		enemy[i] = new Enemy("assets/enemy.png", "assets/enemy_r.png", renderer);
		if (enemy[i] != nullptr) {
			enemy[i]->init();
		} else {
			printError("Can not load all caracters");
			exit(1);
		}
	}

	nrClc = LevelManager::getNrColectables();
	exitLvl = LevelManager::getExit();
	clcLvl = LevelManager::getCollectables();


	collectables = GameObject::createGameObjects(clcLvl, nrClc, renderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.state == SDL_PRESSED) {
				switch (event.key.keysym.scancode) {
					case SDL_SCANCODE_W:
						player->addMovement(TravelDirection::up);
						break;
					case SDL_SCANCODE_S:
						player->addMovement(TravelDirection::down);
						break;
					case SDL_SCANCODE_D:
						player->addMovement(TravelDirection::right);
						break;
					case SDL_SCANCODE_A:
						player->addMovement(TravelDirection::left);
						break;
					case SDL_SCANCODE_1:
						player->changeWeapon(0);
						break;
					case SDL_SCANCODE_2:
						player->changeWeapon(1);
						break;
					case SDL_SCANCODE_F11:
						if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN) {
							if (SDL_SetWindowFullscreen(window, NULL)) {
								printError(SDL_GetError());
							} else {
								SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
							}
						} else {
							if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN)) {
								printError(SDL_GetError());
							} else {
								SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
							}
						}
						break;
				}
			}
			break;

		case SDL_KEYUP:
			if (event.key.state == SDL_RELEASED) {
				switch (event.key.keysym.scancode) {
					case SDL_SCANCODE_W:
						player->subMovement(TravelDirection::up);
						break;
					case SDL_SCANCODE_S:
						player->subMovement(TravelDirection::down);
						break;
					case SDL_SCANCODE_D:
						player->subMovement(TravelDirection::right);
						break;
					case SDL_SCANCODE_A:
						player->subMovement(TravelDirection::left);
						break;
				}
			}
			break;
		
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.state == SDL_PRESSED) {
				switch (event.button.button) {
					case SDL_BUTTON_LEFT:
						if (!mouseLeft) {
							mouseLeft = true;
							Position mouseButtonLocation = {};
							mouseButtonLocation.xPX = (unsigned int)event.button.x;
							mouseButtonLocation.yPX = (unsigned int)event.button.y;
							player->attack(mouseButtonLocation);
						}
						break;
				}
			}
			break;

		case SDL_MOUSEBUTTONUP:
			if (event.button.state == SDL_RELEASED) {
				switch (event.button.button) {
					case SDL_BUTTON_LEFT:
						mouseLeft = false;
						break;
				}
			}
			break;

		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED and !(SDL_GetWindowFlags(window) & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN))) {
				int w, h;
				SDL_GetWindowSize(window, &w, &h);

				if ((double)w / h != aspectRatio) {
					w = (int)((double)h * aspectRatio);
					SDL_SetWindowSize(window, w, h);
				}
			}

		default:
			break;
	}

	if (player->isDead()) {
		isRunning = false;
	}

	if (exitLevel == nullptr) {
		if (player->collectedAll()) {
			exitLevel = new ExitBlock(renderer, (*exitLvl)[0], (*exitLvl)[1]);
			if (exitLevel == nullptr) {
				printError("Can not load object ExitBlock");
				exit(1);
			}
		}
	} else if (player->getPosition().x == exitLevel->getX() and player->getPosition().y == exitLevel->getY()) {
		nextLevel();
	}
}
void Game::update() const
{
	player->update();

	for (unsigned char i = 0; i < nrEnemy; i++) {
		if (enemy[i]) {
			enemy[i]->update();
			if (enemy[i]->isDead()) {
				delete enemy[i];
				enemy[i] = nullptr;
				player->addKill();
			}
		}
	}
}

void Game::render() const
{
	SDL_RenderClear(renderer);
	// this is where we would add stuff to render
	map->DrawMap();

	for (size_t i = 0; i < nrClc; i++) {
		if (collectables[i] != nullptr) {
			collectables[i]->Render();
		}
	}

	if (exitLevel != nullptr) {
		exitLevel->Render();
	}

	vector<Component*> components;

	components.push_back(player);

	for (size_t i = 0; i < nrEnemy; i++) {
		if (enemy[i] != nullptr) {
			components.push_back(enemy[i]);
		}
	}

	componentRenderAll(components);

	ui->draw();

	SDL_RenderPresent(renderer);
}

void Game::clean() const
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_QUIT;
	std::cout << "Game cleaned" << std::endl;
}

Component* Game::searchHitbox(const Position& position) {
	for (unsigned int i = 0; i < map->getNrEnemy(); i++) {
		if (enemy[i] != nullptr) {
			if (position.xPX > enemy[i]->getHitbox().xPX1 and position.xPX < enemy[i]->getHitbox().xPX2) {
				if (position.yPX > enemy[i]->getHitbox().yPX1 and position.yPX < enemy[i]->getHitbox().yPX2) {
					return enemy[i];
				}
			}
		}
	}
	return 0;
}

void Game::componentRenderAll(vector<Component*> components) const {
	sort(components.begin(), components.end(), sortComponents);

	for (vector<Component*>::iterator i = components.begin(); i != components.end(); i++) {
		(*i)->draw();
	}
}

void Game::nextLevel() {

	if (!map->loadNextMap()) {
		isRunning = false;
	} else {
		ui->nextLevel();
		player->changeLevel();

		if (enemy != nullptr) {
			delete[] enemy;
		}

		nrEnemy = map->getNrEnemy();

		enemy = new Component * [nrEnemy];
		if (enemy == nullptr) {
			printError("Can not create enemys");
			exit(1);
		}

		for (unsigned char i = 0; i < nrEnemy; i++) {
			enemy[i] = new Enemy("assets/enemy.png", "assets/enemy_r.png", renderer);
			if (enemy[i] != nullptr) {
				enemy[i]->init();
			} else {
				printError("Can not load all caracters");
				exit(1);
			}
		}

		if (exitLevel != nullptr) {
			delete exitLevel;
		}
		if (collectables != nullptr) {
			delete[] collectables;
		}

		nrClc = LevelManager::getNrColectables();
		exitLvl = LevelManager::getExit();
		clcLvl = LevelManager::getCollectables();

		collectables = GameObject::createGameObjects(clcLvl, nrClc, renderer);
		exitLevel = nullptr;
	}
}