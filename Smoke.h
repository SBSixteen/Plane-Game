#pragma once
#include "GameObject.h"
class Smoke:public GameObject
{
public:
	Smoke(int x, int y, SDL_Renderer* R);
	~Smoke();
	void Move();
};

