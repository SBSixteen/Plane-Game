#pragma once
#include <SDL.h>
#include "GameObject.h"

class Shooter : public GameObject
{
public:
	int g;
	Shooter(int x, int y, SDL_Renderer* R);
	~Shooter();
	void Move();
	void Roll();
};

