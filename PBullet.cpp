#include "PBullet.h"
#include <iostream>

PBullet::PBullet(int x, int y, SDL_Renderer* R, bool E) : GameObject(x, y) {

	ScatterL = false;
	ScatterR = false;
	enemyB = E;
	alive = true;
	Bounding_Box->x = x-4;
	Bounding_Box->y = y;
	if (enemyB) {
		Bounding_Box->y = Bounding_Box->y + 64;
	}
	Bounding_Box->w = 10;
	Bounding_Box->h = 10;
	w = 10;
	h = 10;

	if (enemyB) {
		Texture = IMG_LoadTexture(R, "Art/Enemy_Bullet.png");
	}
	else {
		Texture = IMG_LoadTexture(R, "Art/Player_Bullet.png");
	}
}

void PBullet::Move() {

	if (enemyB) {
		
		if (ScatterL) {
			Bounding_Box->x = Bounding_Box->x - 3;
		}
		if (ScatterR) {
			Bounding_Box->x = Bounding_Box->x + 3;
		}

		Bounding_Box->y = Bounding_Box->y + 6;

		if(Bounding_Box->y>1000) {
			alive = false;
		}
	}
	else {

		Bounding_Box->y = Bounding_Box->y -6;
		
		if (Bounding_Box->y < 5) {
			alive = false;
		}
	}

}

PBullet::~PBullet() {

}