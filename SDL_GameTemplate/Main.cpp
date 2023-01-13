//Using SDL and standard IO
#include "Game.h"
#include <SDL.h>
#include "fstream"
#include <iostream>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;

int main(int argc, char* args[])
{
	const int fps = 60;
	// max time between frames
	const int frameDelay = 1000 / fps;


	ofstream logFile;
	logFile.open("log.txt");
	streambuf* log = logFile.rdbuf();
	cout.rdbuf(log);

	Game *game = new Game();

	game->init("GameTitle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

	while (game->running())
	{
		Uint32 frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();
		const int frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	delete game;
	return 0;
}