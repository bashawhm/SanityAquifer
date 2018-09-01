#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

#include "adventure.h"
#include "graphics/button.h"
#include "graphics/TexturedButton.h"
#include "graphics/background.h"
#include "stage.h"

Adventure::Adventure(SDL_Renderer *rend, u32 width, u32 height, u8 startLevel, string backImg, Stage *stage){
	renderer = rend;
	winWidth = width;
	winHeight = height;
	level = startLevel;
	vector<EntityType> foods = {Food};
	Entity *entity = new Entity(Fish, Water, foods, stage);
	Entity *entity2 = new Entity(Fish, Water, foods, stage);
	entities.push_back(*entity);
	entities.push_back(*entity2);
	background = new Background(backImg, width, height, renderer);

}

void Adventure::addButton(string name, u32 x, u32 y, u32 width, u32 height) {
	// TexturedButton *dButton = new TexturedButton(name, x, y, width, height, "assets/debugButton.png", renderer);
	// debugButtons.push_back(*dButton);
	Button *button = new Button(name, x, y, width, height, "assets/DoHyeon.ttf", renderer);
	buttons.push_back(*button);
}

Button* Adventure::getButton(string name) {
	for (u64 i = 0; i < buttons.size(); ++i){
		if (buttons[i].getName() == name){
			return &buttons[i];
		}
	}
	return NULL;
}

Button* Adventure::getButton(u32 x, u32 y) {
	for (u64 i = 0; i < buttons.size(); ++i) {
		if ((x >= buttons[i].getX()) && (x <= (buttons[i].getX() + buttons[i].getW())) && (y >= buttons[i].getY()) && (y <= (buttons[i].getY() + buttons[i].getH()))){
			return &buttons[i];
		}
	}
	return NULL;
}

Events Adventure::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch (event.type) {
		case SDL_KEYDOWN: {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE: {
				return MenuMode;
			}
			}
			break;
		}

		case SDL_QUIT: {
			return MenuMode;
		}

		case SDL_MOUSEBUTTONDOWN: {
			i32 mouseX;
			i32 mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			Button *button = getButton(mouseX, mouseY);
			if (button == NULL) {
				return None;
			}

			break;
		}
		}
	}

	return None;
}

void Adventure::renderAdventure() {
	usleep(16000);
	background -> render();
	for (auto button : buttons) {
		button.render();
	}
	for (auto button : debugButtons) {
		button.render();
	}

	for (int i = 0; i < entities.size(); i++) {
		entities[i].render();
	}

	SDL_RenderPresent(renderer);
}
