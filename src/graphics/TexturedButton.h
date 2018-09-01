#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_ttf.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

#include "../type.h"

using namespace std;

class TexturedButton {
public:
	TexturedButton(string bName, u32 x, u32 y, u32 width, u32 height, string tex, SDL_Renderer *rend){
		button.x = x;
		button.y = y;
		button.w = width;
		button.h = height;
		name = bName;

		renderer = rend;

		SDL_Surface *sur = IMG_Load(tex.c_str());

		texture = SDL_CreateTextureFromSurface(rend, sur);
		SDL_FreeSurface(sur);
	}

	void render() {
		SDL_RenderCopy(renderer, texture, NULL, &button);
	}

	string getName(){
		return name;
	}

	u32 getX() {
		return button.x;
	}

	u32 getY() {
		return button.y;
	}

	u32 getW() {
		return button.w;
	}

	u32 getH() {
		return button.h;
	}

private:
	string name;
	SDL_Renderer *renderer;
	SDL_Rect button;
	SDL_Texture *texture;
};
