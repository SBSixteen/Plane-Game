#include "Boss.h"
#include <cstdlib>
#include <iostream>

Boss::Boss(int x, int y, SDL_Renderer* R) : GameObject(x, y) {

	health = 100;
	shooter = true;
	shoot = true;
	Bounding_Box->x = x;
	Bounding_Box->y = y;
	Bounding_Box->w = 743;
	Bounding_Box->h = 196;
	w = 743;
	h = 196;

	Texture = IMG_LoadTexture(R, "Art/Boss.png");
}

void Boss::Move() {

	if (Bounding_Box->y < 200) {
		Bounding_Box->y = Bounding_Box->y + 1;
	}

	std::cout << Bounding_Box->x << ", " << Bounding_Box->y << std::endl;

}

Boss::~Boss() {

}