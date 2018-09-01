#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

#include "../type.h"

using namespace std;

class Animation {
public:
	Animation(vector<string> aFrames, SDL_Rect *aHitBox, SDL_Renderer *aRend) {
		renderer = aRend;
		hitBox = aHitBox;
		currFrame = 0;

		for (string tex : aFrames) {
			SDL_Surface *sur = IMG_Load(tex.c_str());
			frames.push_back(SDL_CreateTextureFromSurface(renderer, sur));
			SDL_FreeSurface(sur);
		}
	}

	void setFrames(vector<string> aFrames){
		for (string tex : aFrames) {
			SDL_Surface *sur = IMG_Load(tex.c_str());
			frames.push_back(SDL_CreateTextureFromSurface(renderer, sur));
			SDL_FreeSurface(sur);
		}
	}

	void nextFrame(){
		if (currFrame == frames.size() - 1) {
			currFrame = 0;
		}
		currFrame++;
	}

	void render(){
		SDL_RenderCopy(renderer, frames[currFrame], NULL, hitBox);
	}

private:
	vector<SDL_Texture*> frames;
	u32 currFrame;
	SDL_Rect *hitBox;
	SDL_Renderer *renderer;
};