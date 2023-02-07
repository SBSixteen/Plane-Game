#pragma once
#include "GameObject.h"


class Player_Plane : public GameObject
{
	float dx, dy;

public:
	Player_Plane(int x, int y, SDL_Renderer* R);
	~Player_Plane();
	void Move();
	void Direction(float dx, float dy);
	void AddMissile();
};

