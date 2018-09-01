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

class Button {
public:
	Button(string bName, u32 x, u32 y, u32 width, u32 height, string fontPath, SDL_Renderer *rend){
		button.x = x;
		button.y = y;
		button.w = width;
		button.h = height;
		name = bName;
		font = NULL;
		font = TTF_OpenFont(fontPath.c_str(), 200);
		if (font == NULL){
			cerr << "Failed to init font: " << fontPath << "\n";
		}

		renderer = rend;

		SDL_Color fontColor = {255, 250, 255, 255};
		SDL_Surface *sur = TTF_RenderText_Solid(font, bName.c_str(), fontColor);

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
	TTF_Font *font;
};
