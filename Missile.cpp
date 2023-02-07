#include "Missile.h"
#include <iostream>

Missile::Missile(int x, int y, GameObject* Target,SDL_Renderer* R) : GameObject(x, y) {

	Target->hasTarget = true;
	target = Target;
	target->Texture = IMG_LoadTexture(R, "Art/F-35-T.png");
	alive = true;
	Bounding_Box->x = x;
	Bounding_Box->y = y;
	if (enemyB) {
		Bounding_Box->y = Bounding_Box->y + 64;
	}
	Bounding_Box->w = 8;
	Bounding_Box->h = 48;
	w = 8;
	h = 8;

	Texture = IMG_LoadTexture(R, "Art/Missile.png");

}

Missile::~Missile() {

}

void Missile::Move() {
	
	if (target->alive == false || target == nullptr) {
		Bounding_Box->y = Bounding_Box->y - 6;
	}
	else {

		float a = target->Bounding_Box->y - Bounding_Box->y; //opp
		float b = target->Bounding_Box->x - Bounding_Box->x; //adj

		angle = atan2f(a, b);

		int dy = ceil(5 * sin(angle));
		int dx = ceil(5 * cos(angle));
		float deg = 90 + angle * (180 / 3.142);

		std::cout << "y: " << dy << std::endl;
		std::cout << "x: " << dy << std::endl;
		std::cout << "angle: " << deg << std::endl;
		std::cout << "dy: " << dy << std::endl;
		std::cout << "dx :" << dx << std::endl;

		Bounding_Box->y = Bounding_Box->y + dy;
		Bounding_Box->x = Bounding_Box->x + dx;

		if (Bounding_Box->y < 5 || Bounding_Box->y > 1000) {
			alive = false;
		}
	}

}