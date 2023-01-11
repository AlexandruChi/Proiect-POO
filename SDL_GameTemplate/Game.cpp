#include "Game.h"
#include <iostream>
#include "Map.h"
#include "Player.h"
#include "UI.h"
#include "Enemy.h"
#include "GameObject.h"
#include "Colectables.h"

TextureUI_path setUIpaths();

Game* game;
Map* map;
UI* ui;
Player* player;
Enemy** enemy;
GameObject** collectables;

unsigned char nrEnemy;
size_t nrClc;

Game::Game(): isRunning(false), window(nullptr), renderer(nullptr), mouseLeft(false) {}

Game::~Game()
{
   delete player;
   delete map;
   delete ui;
   delete[] enemy;
   delete[] collectables;

   TTF_Quit();
}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 and TTF_Init() == 0)
	{
		std::cout << "Subsystems initialized" << std::endl;
		auto window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window!=nullptr)
		{
			std::cout << "Window created" << std::endl;
		}
 
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer != nullptr)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	map = new Map(renderer);

    player = new Player ("assets/player.png", "assets/player_r.png", renderer);
    player->init();

    TextureUI_path textureUI_path = setUIpaths();
    ui = new UI(&textureUI_path, renderer);

	unsigned char nrEnemy = map->getNrEnemy();
	enemy = new Enemy * [nrEnemy];
	if (enemy == nullptr) {
		exit(1);
	}
	for (unsigned char i = 0; i < nrEnemy; i++) {
		enemy[i] = new Enemy("assets/enemy.png", "assets/enemy_r.png", renderer);
		if (enemy[i] == nullptr) {
			exit(1);
		}
		enemy[i]->init();
	}

	nrClc = nrClcLvl1;

	collectables = GameObject::createGameObjects(clcLvl1, nrClc, renderer);

	game = this;
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
						player->addMovement(up);
						break;
					case SDL_SCANCODE_S:
						player->addMovement(down);
						break;
					case SDL_SCANCODE_D:
						player->addMovement(right);
						break;
					case SDL_SCANCODE_A:
						player->addMovement(left);
						break;
					case SDL_SCANCODE_1:
						player->changeWeapon(0);
						break;
					case SDL_SCANCODE_2:
						player->changeWeapon(1);
						break;
				}
			}
			break;

		case SDL_KEYUP:
			if (event.key.state == SDL_RELEASED) {
				switch (event.key.keysym.scancode) {
					case SDL_SCANCODE_W:
						player->subMovement(up);
						break;
					case SDL_SCANCODE_S:
						player->subMovement(down);
						break;
					case SDL_SCANCODE_D:
						player->subMovement(right);
						break;
					case SDL_SCANCODE_A:
						player->subMovement(left);
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
		
		default:
			break;
	}
}
void Game::update() const
{
	player->update();

	for (unsigned char i = 0; i < map->getNrEnemy(); i++) {
		if (enemy[i]) {
			enemy[i]->update();
			if (enemy[i]->isDead()) {
				delete enemy[i];
				enemy[i] = 0;
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

	for (unsigned char i = 0; i < map->getNrEnemy(); i++) {
		if (enemy[i]) {
			enemy[i]->draw();
		}
	}

	player->draw();
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

Character* Game::searchHitbox(const Position& position) const {
	for (int i = 0; i < map->getNrEnemy(); i++) {
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