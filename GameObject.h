#pragma once
#include <SDL.h>
#include <SDL_image.h>

class GameObject
{
public:
	//position
	GameObject* target;
	int health;
	int missiles;
	int ticks;
	int w, h, x, y; //SDL_Rect Size
	bool alive, shoot, dodge, homing, hasTarget, enemyB, shooter, ScatterL, ScatterR;
	SDL_Rect* Bounding_Box;
	SDL_Texture* Texture;

	GameObject(int x, int y);
	virtual ~GameObject();
	virtual void Move() = 0;
	virtual SDL_Texture* getTexture();
	virtual SDL_Rect* getRect();
	virtual void AddMissile();
};

