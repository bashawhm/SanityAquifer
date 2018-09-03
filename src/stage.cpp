#include "stage.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>

#include "type.h"
#include "menu.h"
#include "adventure.h"

Stage::Stage() {
	initGrapgics();

	alive = true;
	needsUpdate = true;
	start = time(NULL);
	current = start;

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	winWidth = DM.w;
	winHeight = DM.h;
	state = MenuMode;
	//state = AdventureMode; // changed for testing
	window = SDL_CreateWindow("Four", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	mainMenu = new Menu(renderer, winWidth, winHeight, "assets/selectorback.jpg");
	advent = new Adventure(renderer, winWidth, winHeight, 0, "assets/aquarium1.jpg", this);

	// cerr << "width: " << winWidth << " height: " << winHeight << endl;
}

Stage::Stage(u32 width, u32 height) {
	initGrapgics();

	alive = true;
	needsUpdate = true;
	start = time(NULL);
	current = start;
	winWidth = width;
	winHeight = height;
	state = MenuMode;
	window = SDL_CreateWindow("Four", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	mainMenu = new Menu(renderer, winWidth, winHeight, "assets/selectorback.jpg");
	advent = new Adventure(renderer, winWidth, winHeight, 0, "assets/aquarium1.jpg", this);
}

Stage::~Stage() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}


void Stage::handleEvents() {
	if (state == MenuMode) {
		switch (mainMenu -> handleEvents()) {
		case Off: {
			alive = false;
			needsUpdate = true;
			break;
		}
		case AdventureMode: {
			state = AdventureMode;
			needsUpdate = true;
			break;
		}
		default: {
			break;
		}
		}

	} else if (state == AdventureMode) {
		switch (advent -> handleEvents()) {
		case Off: {
			state = MenuMode;
			needsUpdate = true;
			break;
		}
		case MenuMode: {
			state = MenuMode;
			needsUpdate = true;
			break;
		}
		default: {
			break;
		}
		}
	} else {

	}

}

void Stage::render() {
	if (state == MenuMode) {
		if (needsUpdate) {
			mainMenu -> renderMenu();
		}
	} else if (state == AdventureMode) {
		advent -> renderAdventure();
	} else {
		
	}
	needsUpdate = false;

}
