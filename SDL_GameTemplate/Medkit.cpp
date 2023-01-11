#include "Medkit.h"

Medkit::Medkit(SDL_Renderer* renderer, int x, int y) :GameObject("assets/medkit.png", GameObjectType::medkit, renderer, x, y) {}