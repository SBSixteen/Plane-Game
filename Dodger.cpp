#include "Dodger.h"
#include <iostream>

Dodger::Dodger(int x, int y , SDL_Renderer* R): GameObject(x,y) {

	ticks = 0;
	dodge = true;
	health = 1;
	Bounding_Box->x = x;
	Bounding_Box->y = y;
	Bounding_Box->w = 72;
	Bounding_Box->h = 41;
	w = 72;
	h = 41;

	Texture = IMG_LoadTexture(R, "Art/UAV.png");
}

Dodger::~Dodger() {

}

void Dodger::Move() {

	ticks++;

	if (ticks % 120 == 0) {
		dodge = true;
		std::cout << "Yo GURT!" << std::endl;
	}


	if (health < 1) {
		alive = false;
	}

	if (Bounding_Box->y > 1005) {
		alive = false;
	}
	else {
		Bounding_Box->y = Bounding_Box->y + 2;
	}

}