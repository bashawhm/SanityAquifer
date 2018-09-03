#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>

#include "type.h"
#include "stage.h"
#include "graphics/animation.h"

using namespace std;

class Stage;

class Entity {
public:
	Entity(EntityType eType, DropType eDropType, const vector<EntityType> &eMeals, Stage *stage);

	bool ageUp();
	void render();

private:
	EntityType type;
	Age age;
	u32 growthThreshold;
	DropType dropType;
	u32 hungerRate;
	vector<EntityType> meals;

	Stage *stage;
	Animation *ani;
	SDL_Rect *hitBox;
	u64 start;
	u64 lastRender;

	i32 targetX;
	i32 targetY;
	i32 dx;
	i32 dy;
	f32 originX;
	f32 originY;
};
