#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Graphics {

public:
	Graphics();
	SDL_Texture* load(const char* texture_path);

};