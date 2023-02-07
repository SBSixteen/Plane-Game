#pragma once
#include "GameObject.h"

class PBullet:public GameObject
{
public:
	PBullet(int x, int y, SDL_Renderer* R, bool E);
	~PBullet();
	void Move();
};

