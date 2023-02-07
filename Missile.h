#pragma once
#include <SDL.h>
#include "GameObject.h"

class Missile:public GameObject
{
public:
	float angle;
	Missile(int x, int y, GameObject* T, SDL_Renderer* R);
	~Missile();
	void Move();
};

