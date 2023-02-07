#include "GameObject.h"

GameObject::GameObject(int x, int y) {

	missiles = 0;
	alive = true;
	this->x = x;
	this->y = y;
	Bounding_Box = new SDL_Rect();
	
	Bounding_Box->x = x;
	Bounding_Box->y = y;

}

GameObject::~GameObject() {

}

SDL_Rect* GameObject::getRect() {

	return Bounding_Box;
}

void GameObject::AddMissile()
{
	missiles++;
}

SDL_Texture* GameObject::getTexture() {

	return Texture;
}
