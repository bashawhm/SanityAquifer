#pragma once
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <vector>

#include "type.h"
#include "graphics/button.h"
#include "graphics/TexturedButton.h"
#include "graphics/background.h"
#include "stage.h"

using namespace std;

class Menu {
public:
	Menu(SDL_Renderer *rend, u32 width, u32 height, string backImg);

	void addButton(string name, u32 x, u32 y, u32 width, u32 height);

	Button* getButton(string name);
	Button* getButton(u32 x, u32 y);
	const vector<Button> getButtons(){
		return buttons;
	}

	Events handleEvents();
	void renderMenu();

private:
	vector<Button> buttons;
	vector<TexturedButton> debugButtons;
	Background *background;
	SDL_Renderer *renderer;

	u32 winWidth;
	u32 winHeight;

};
