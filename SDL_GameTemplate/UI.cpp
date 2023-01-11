#include <iostream>
#include "UI.h"
#include "TextureManager.h"

UI::UI(TextureUI_path* textures, SDL_Renderer* renderer) : renderer(renderer), level(1) {
	setTex(textures);
	White = { 255, 255, 255 };
	f_story = TTF_OpenFont("assets/Reach Story.ttf", 50);
	f_canter = TTF_OpenFont("assets/AnglicanText.ttf", 64);
}

UI::~UI() {}

void UI::setHealth(unsigned char health) {
	switch (health) {
		case 0:
			TexturesUI.health.curent = TexturesUI.health.tx_0;
			break;
		case 1:
			TexturesUI.health.curent = TexturesUI.health.tx_1;
			break;
		case 2:
			TexturesUI.health.curent = TexturesUI.health.tx_2;
			break;
		case 3:
			TexturesUI.health.curent = TexturesUI.health.tx_3;
			break;
		case 4:
			TexturesUI.health.curent = TexturesUI.health.tx_4;
			break;
		case 5:
			TexturesUI.health.curent = TexturesUI.health.tx_5;
			break;
	}
}

void UI::setWeapon(unsigned char weapon) {
	switch (weapon) {
		case 0:
			TexturesUI.weapon.curent = TexturesUI.weapon.tx_0;
			break;
		case 1:
			TexturesUI.weapon.curent = TexturesUI.weapon.tx_1;
			break;
	}
}

void UI::setAmmo(bool hasAmmo, unsigned char ammo) {
	switch (hasAmmo) {
		case false:
			TexturesUI.ammo.curent = TexturesUI.ammo.tx_0;
			break;
		case true:
			TexturesUI.ammo.curent = TexturesUI.ammo.tx_1;
			this->ammo = ammo;
			break;
	}
}

void UI::setCollected(unsigned char collected) {
	switch (collected) {
		case 0:
			TexturesUI.collected.curent = TexturesUI.collected.tx_0;
			break;
		case 1:
			TexturesUI.collected.curent = TexturesUI.collected.tx_1;
			break;
		case 2:
			TexturesUI.collected.curent = TexturesUI.collected.tx_2;
			break;
	}
}

void UI::setMedals(unsigned char medals) {
	switch (medals) {
		case 0:
			TexturesUI.medals.curent = TexturesUI.medals.tx_0;
			break;
		case 1:
			TexturesUI.medals.curent = TexturesUI.medals.tx_1;
			break;
		case 2:
			TexturesUI.medals.curent = TexturesUI.medals.tx_2;
			break;
		case 3:
			TexturesUI.medals.curent = TexturesUI.medals.tx_3;
			break;
		case 4:
			TexturesUI.medals.curent = TexturesUI.medals.tx_4;
			break;
		case 5:
			TexturesUI.medals.curent = TexturesUI.medals.tx_5;
			break;
		case 6:
			TexturesUI.medals.curent = TexturesUI.medals.tx_6;
			break;
		case 7:
			TexturesUI.medals.curent = TexturesUI.medals.tx_7;
			break;
	}
}

void UI::nextLevel() {
	level++;
}

void UI::setTex(TextureUI_path* textures) {
	TexturesUI.health.tx_0 = TextureManager::LoadTexture(textures->health.tx_0, renderer);
	TexturesUI.health.tx_1 = TextureManager::LoadTexture(textures->health.tx_1, renderer);
	TexturesUI.health.tx_2 = TextureManager::LoadTexture(textures->health.tx_2, renderer);
	TexturesUI.health.tx_3 = TextureManager::LoadTexture(textures->health.tx_3, renderer);
	TexturesUI.health.tx_4 = TextureManager::LoadTexture(textures->health.tx_4, renderer);
	TexturesUI.health.tx_5 = TextureManager::LoadTexture(textures->health.tx_5, renderer);

	TexturesUI.ammo.tx_0 = TextureManager::LoadTexture(textures->ammo.tx_0, renderer);
	TexturesUI.ammo.tx_1 = TextureManager::LoadTexture(textures->ammo.tx_1, renderer);

	TexturesUI.collected.tx_0 = TextureManager::LoadTexture(textures->collected.tx_0, renderer);
	TexturesUI.collected.tx_1 = TextureManager::LoadTexture(textures->collected.tx_1, renderer);
	TexturesUI.collected.tx_2 = TextureManager::LoadTexture(textures->collected.tx_2, renderer);

	TexturesUI.medals.tx_0 = TextureManager::LoadTexture(textures->medals.tx_0, renderer);
	TexturesUI.medals.tx_1 = TextureManager::LoadTexture(textures->medals.tx_1, renderer);
	TexturesUI.medals.tx_2 = TextureManager::LoadTexture(textures->medals.tx_2, renderer);
	TexturesUI.medals.tx_3 = TextureManager::LoadTexture(textures->medals.tx_3, renderer);
	TexturesUI.medals.tx_4 = TextureManager::LoadTexture(textures->medals.tx_4, renderer);
	TexturesUI.medals.tx_5 = TextureManager::LoadTexture(textures->medals.tx_5, renderer);
	TexturesUI.medals.tx_6 = TextureManager::LoadTexture(textures->medals.tx_6, renderer);
	TexturesUI.medals.tx_7 = TextureManager::LoadTexture(textures->medals.tx_7, renderer);

	TexturesUI.weapon.tx_0 = TextureManager::LoadTexture(textures->weapon.tx_0, renderer);
	TexturesUI.weapon.tx_1 = TextureManager::LoadTexture(textures->weapon.tx_1, renderer);

	TexturesUI.health.curent = TexturesUI.health.tx_5;
	TexturesUI.ammo.curent = TexturesUI.ammo.tx_0;
	TexturesUI.collected.curent = TexturesUI.collected.tx_0;
	TexturesUI.weapon.curent = TexturesUI.weapon.tx_0;
	TexturesUI.medals.curent = TexturesUI.medals.tx_0;
}

void UI::draw() {
	SDL_Rect srcRect{}, destRect{};

	char ammoCounterC[5]{};
	char levelC[6]{};

	if (TexturesUI.ammo.curent == TexturesUI.ammo.tx_1) {
		sprintf_s(ammoCounterC, 5, "X%d", ammo);
	}

	sprintf_s(levelC, 6, "Lvl %d", level);
	
	SDL_Surface* ammoCounterS = TTF_RenderText_Solid(f_story, ammoCounterC, White);

	SDL_Surface* levelS = TTF_RenderText_Solid(f_canter, levelC, White);

	SDL_Texture* ammoCounter = SDL_CreateTextureFromSurface(renderer, ammoCounterS);
	SDL_Texture* levelT = SDL_CreateTextureFromSurface(renderer,levelS);

	destRect.h = 64;
	destRect.w = 32 * 7;

	destRect.x = destRect.y = 0;

	TextureManager::Draw(TexturesUI.health.curent, srcRect, destRect, renderer);

	destRect.h = 64;
	destRect.w = 32 * 7;

	destRect.x = (int)(32 * 6.25);
	destRect.y = 0;

	TextureManager::Draw(TexturesUI.medals.curent, srcRect, destRect, renderer);

	destRect.h = 64;
	destRect.w = 64;

	destRect.x = 32 * 23;
	destRect.y = 0;

	TextureManager::Draw(TexturesUI.weapon.curent, srcRect, destRect, renderer);

	destRect.h = 64;
	destRect.w = 64;

	destRect.x = 32 * 19;
	destRect.y = 0;

	TextureManager::Draw(TexturesUI.ammo.curent, srcRect, destRect, renderer);

	destRect.h = 64;
	destRect.w = 64;

	destRect.x = 32 * 17;
	destRect.y = 0;

	TextureManager::Draw(TexturesUI.collected.curent, srcRect, destRect, renderer);

	destRect.h = 64;
	destRect.w = 64;

	destRect.x = (int)(32 * 20.5);
	destRect.y = 5;

	TextureManager::Draw(ammoCounter, srcRect, destRect, renderer);

	destRect.h = 56;
	destRect.w = 32 * 3;

	destRect.x = 32 * 13;
	destRect.y = 4;

	TextureManager::Draw(levelT, srcRect, destRect, renderer);

	SDL_FreeSurface(ammoCounterS);
	SDL_DestroyTexture(ammoCounter);
	SDL_FreeSurface(levelS);
	SDL_DestroyTexture(levelT);
}
