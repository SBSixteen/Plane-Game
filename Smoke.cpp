#include "Smoke.h"

Smoke::Smoke(int x, int y, SDL_Renderer* R) : GameObject(x, y) {

	alive = true;
	Bounding_Box->x = x-8;
	Bounding_Box->y = y+20;
	Bounding_Box->w = 30;
	Bounding_Box->h = 30;
	w = 10;
	h = 10;
	health = 30;
	Texture = IMG_LoadTexture(R, "Art/Smoke.png");

}

void Smoke::Move(){

	health--;
	if (health <1) {
		alive = false;
	}
}

Smoke::~Smoke() {

}