#pragma once
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <vector>

#include "type.h"
#include "graphics/button.h"
#include "graphics/TexturedButton.h"
#include "graphics/background.h"
#include "stage.h"

class Stage;
class Entity;

class Adventure {
public:
	Adventure(SDL_Renderer *rend, u32 width, u32 height, u8 startLevel, string backImg, Stage *stage);

	void addButton(string name, u32 x, u32 y, u32 width, u32 height);

	Button* getButton(string name);
	Button* getButton(u32 x, u32 y);
	const vector<Button> getButtons(){
		return buttons;
	}

	Events handleEvents();
	void renderAdventure();

private:
	vector<Button> buttons;
	vector<TexturedButton> debugButtons;
	Background *background;
	SDL_Renderer *renderer;

	u32 winWidth;
	u32 winHeight;

	vector<Entity> entities;
	u8 level;
};