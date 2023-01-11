#include "Document.h"

Document::Document(SDL_Renderer* renderer, int x, int y) : GameObject("assets/collected_1.png", GameObjectType::document, renderer, x, y) {}