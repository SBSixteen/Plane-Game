#include "Shooter.h"
#include <cstdlib>
#include <iostream>

Shooter::Shooter(int x, int y, SDL_Renderer* R) : GameObject(x, y) {

	health = 5;
	shooter = true;
	shoot = true;
	Bounding_Box->x = x;
	Bounding_Box->y = y;
	Bounding_Box->w = 89;
	Bounding_Box->h = 130;
	w = 89;
	h = 130;
	g = 0;
	Texture = IMG_LoadTexture(R, "Art/F-35.png");
}

Shooter::~Shooter() {

}

void Shooter::Roll() {

	g++;
	//std::cout << g << std::endl;

	if (g > 5) {
		shoot = true;
		g = g-(rand()%299); // All foxbats have random shooting speeds
	}
	else {
		shoot = false;
	}
}

void Shooter::Move() {

	Roll();

	if (health <1) {
		alive = false;

	}

	if (Bounding_Box->y > 1005) {
		alive = false;
	}
	else {
		Bounding_Box->y = Bounding_Box->y + 2;
	}
}