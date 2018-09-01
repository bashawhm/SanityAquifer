#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

#include "menu.h"
#include "graphics/button.h"
#include "graphics/TexturedButton.h"
#include "graphics/background.h"
#include "stage.h"

using namespace std;

Menu::Menu(SDL_Renderer *rend, u32 width, u32 height, string backImg) {
	renderer = rend;
	winWidth = width;
	winHeight = height;
	background = new Background(backImg, width, height, renderer);

	addButton("Exit", (width) - (width / 5), (height) - (height / 7), 250, 80);
	addButton("Adventure", ((width / 2) + (width / 14)), ((height / 6) - (height / 16)), 600, 150);

}

void Menu::addButton(string name, u32 x, u32 y, u32 width, u32 height) {
	// TexturedButton *dButton = new TexturedButton(name, x, y, width, height, "assets/debugButton.png", renderer);
	// debugButtons.push_back(*dButton);
	Button *button = new Button(name, x, y, width, height, "assets/DoHyeon.ttf", renderer);
	buttons.push_back(*button);
}

Button* Menu::getButton(string name) {
	for (u64 i = 0; i < buttons.size(); ++i){
		if (buttons[i].getName() == name){
			return &buttons[i];
		}
	}
	return NULL;
}

Button* Menu::getButton(u32 x, u32 y) {
	for (u64 i = 0; i < buttons.size(); ++i) {
		if ((x >= buttons[i].getX()) && (x <= (buttons[i].getX() + buttons[i].getW())) && (y >= buttons[i].getY()) && (y <= (buttons[i].getY() + buttons[i].getH()))){
			return &buttons[i];
		}
	}
	return NULL;
}

Events Menu::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch (event.type) {
		case SDL_KEYDOWN: {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE: {
				return Off;
			}
			}
			break;
		}

		case SDL_QUIT: {
			return Off;
		}

		case SDL_MOUSEBUTTONDOWN: {
			i32 mouseX;
			i32 mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			Button *button = getButton(mouseX, mouseY);
			if (button == NULL) {
				return None;
			}
			if (button -> getName() == "Exit") return Off;
			else if (button -> getName() == "Adventure") return AdventureMode;

			break;
		}
		}
	}

	return None;
}

void Menu::renderMenu() {
	background -> render();

	for (auto button : buttons) {
		button.render();
	}
	for (auto button : debugButtons) {
		button.render();
	}
	SDL_RenderPresent(renderer);
}
