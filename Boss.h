#pragma once
#include <SDL.h>
#include "GameObject.h"

class Boss : public GameObject
{
	public:
		Boss(int x, int y, SDL_Renderer* R);
		~Boss();
		void Move();
};

