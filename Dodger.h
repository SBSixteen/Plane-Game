#pragma once
#include <SDL.h>
#include "GameObject.h"

class Dodger : public GameObject
{
public:
	Dodger(int x, int y, SDL_Renderer* R);
	~Dodger();
	void Move();
};

