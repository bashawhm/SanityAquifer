#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

#include "../type.h"

using namespace std;

class Background {
public:
	Background(string backImg, u32 width, u32 height, SDL_Renderer *rend){
		backgroundImg = backImg;
		winHeight = height;
		winWidth = width;
		renderer = rend;
		tex = NULL;
	}

	void render(){
		if (tex == NULL){
			background.x = 0;
			background.y = 0;
			background.w = winWidth;
			background.h = winHeight;

			SDL_Surface *sur = IMG_Load(backgroundImg.c_str());
			tex = SDL_CreateTextureFromSurface(renderer, sur);
			SDL_FreeSurface(sur);		
		}

		SDL_RenderCopy(renderer,tex, NULL, &background);
	}
private:
	u32 winWidth;
	u32 winHeight;
	string backgroundImg;

	SDL_Rect background;
	SDL_Texture *tex;
	SDL_Renderer *renderer;
};