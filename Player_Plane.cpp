#include "Player_Plane.h"

Player_Plane::Player_Plane(int x, int y, SDL_Renderer* R) : GameObject(x, y) {

	dy = 0, dx = 0;
	Bounding_Box->x = x;
	Bounding_Box->y = y;
	Bounding_Box->w = 128;
	Bounding_Box->h = 160;
	w = 128;
	h = 160;
	missiles = 3;

	Texture = IMG_LoadTexture(R, "Art/SU47.png");
}

void Player_Plane::AddMissile() {

	if (missiles < 10) {
		missiles++;
	}

}

void Player_Plane::Direction(float x, float y) {

	dx = x;
	dy = y;

}

void Player_Plane::Move() {

	if (x > 64 && x < 720 - w) {
		Bounding_Box->x = Bounding_Box->x + (int)dx;
	}
	if (y > 160 && y < 1040 - h) {
		Bounding_Box->y = Bounding_Box->y + (int)dy;
	}

	dx = dx * 0.8f;
	dy = dy * 0.8f;
}

Player_Plane::~Player_Plane() {

}