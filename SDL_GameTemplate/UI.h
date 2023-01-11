#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

struct TextureUI_path;

class UI {
public:
	UI(TextureUI_path* textures, SDL_Renderer* renderer);
	~UI();

	void setHealth(unsigned char health);
	void setWeapon(unsigned char weapon);
	void setAmmo(bool hasAmmo, unsigned char ammo);
	void setCollected(unsigned char collected);
	void setMedals(unsigned char medals);

	void nextLevel();

	void setTex(TextureUI_path* textures);
	void draw();
private:
	unsigned char level, ammo;

	SDL_Color White;

	TTF_Font* f_story;
	TTF_Font* f_canter;

	SDL_Renderer* renderer{};

	struct {
		struct {
			SDL_Texture* curent{};
			SDL_Texture* tx_0{};
			SDL_Texture* tx_1{};
			SDL_Texture* tx_2{};
			SDL_Texture* tx_3{};
			SDL_Texture* tx_4{};
			SDL_Texture* tx_5{};
		} health;

		struct {
			SDL_Texture* curent{};
			SDL_Texture* tx_0{};
			SDL_Texture* tx_1{};
		} weapon;

		struct {
			SDL_Texture* curent{};
			SDL_Texture* tx_0{};
			SDL_Texture* tx_1{};
		} ammo;

		struct {
			SDL_Texture* curent{};
			SDL_Texture* tx_0{};
			SDL_Texture* tx_1{};
			SDL_Texture* tx_2{};
		} collected;

		struct {
			SDL_Texture* curent{};
			SDL_Texture* tx_0{};
			SDL_Texture* tx_1{};
			SDL_Texture* tx_2{};
			SDL_Texture* tx_3{};
			SDL_Texture* tx_4{};
			SDL_Texture* tx_5{};
			SDL_Texture* tx_6{};
			SDL_Texture* tx_7{};
		} medals;
	} TexturesUI;
};

struct TextureUI_path {
	struct {
		char* tx_0{};
		char* tx_1{};
		char* tx_2{};
		char* tx_3{};
		char* tx_4{};
		char* tx_5{};
	} health;

	struct {
		char* tx_0{};
		char* tx_1{};
	} weapon;

	struct {
		char* tx_0{};
		char* tx_1{};
	} ammo;

	struct {
		char* tx_0{};
		char* tx_1{};
		char* tx_2{};
	} collected;

	struct {
		char* tx_0{};
		char* tx_1{};
		char* tx_2{};
		char* tx_3{};
		char* tx_4{};
		char* tx_5{};
		char* tx_6{};
		char* tx_7{};
	} medals;
};