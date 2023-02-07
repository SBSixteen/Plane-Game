#include "Turret.h"
#include <cstdlib>
#include <iostream>

Turret::Turret(int x, int y, Player_Plane* Target ,SDL_Renderer* R) : GameObject(x, y) {

	alive = true;
	target = Target;
	health = 25;
	Bounding_Box->x = x;
	Bounding_Box->y = y;
	Bounding_Box->w = 48;
	Bounding_Box->h = 80;

	w = 32;
	h = 60;

	Texture = IMG_LoadTexture(R, "Art/Turret.png");
}

Turret::~Turret() {

}

void Turret::Move() {

	g++;
	//std::cout << g << std::endl;

	if (g > 15) {
		shoot = true;
		g = g - 75; // All foxbats have random shooting speeds
	}
	else {
		shoot = false;
	}

}