#pragma once
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "type.h"
#include "menu.h"
#include "adventure.h"
#include "entity.h"
//#include <SDL2/SDL_ttf>

class Menu;
class Adventure;

class Stage {
public:

	Stage();
	Stage(u32 width, u32 height);

	~Stage();

	bool isAlive(){
		return alive;
	}

	void setTime(time_t now) {
		current = now;
	}

	void handleEvents();
	void render();

private:
	friend class Entity;
	void initGrapgics() {
		SDL_Init(SDL_INIT_EVERYTHING);
		TTF_Init();
	}

	Menu *mainMenu;
	Adventure *advent;
	Events state;

	SDL_Window *window;
	SDL_Renderer *renderer;
	bool needsUpdate;

	bool alive;
	time_t start;
	time_t current;

	u32 winWidth;
	u32 winHeight;
};