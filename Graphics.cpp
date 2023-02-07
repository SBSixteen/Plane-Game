#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Graphics.h"

Graphics::Graphics() {

}

SDL_Texture* Graphics::load(,const char* texture_path) {

	SDL_Texture* T = NULL;

	T = IMG_LoadTexture(texture_path);

	return T;

}