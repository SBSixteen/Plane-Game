#pragma once
#include <SDL.h>
#include "GameObject.h"
#include "Player_Plane.h"

class Turret : public GameObject
{
public:
	int g = 0;
	Turret(int x, int y,Player_Plane* Target, SDL_Renderer* R);
	~Turret();
	void Move();
};

