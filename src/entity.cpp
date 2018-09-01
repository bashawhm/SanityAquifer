#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>

#include "type.h"
#include "entity.h"
#include "stage.h"
#include "graphics/animation.h"

using namespace std;

#define XSPEED 10
#define YSPEED 10


Entity::Entity(EntityType eType, DropType eDropType, const vector<EntityType> &eMeals, Stage *eStage) {
	type = eType;
	dropType = eDropType;
	hungerRate = -1;
	growthThreshold = 0;
	age = Guppy;
	meals = eMeals;
	stage = eStage;
	hitBox = new SDL_Rect();
	struct timeval now;
	gettimeofday(&now, NULL);
	start = ((now.tv_sec * 1000UL) + (now.tv_usec  / 1000UL));
	lastRender = start;

	hitBox -> x = (rand() % stage -> winWidth);
	hitBox -> y = (rand() % stage -> winHeight);
	targetX = (rand() % stage -> winWidth);
	targetY = (rand() % stage -> winHeight);

	if (type == Fish || type == Breeder) {
		growthThreshold = 10;
		hungerRate = 15; // Needs to eat every 15 seconds
		hitBox -> w = 50;
		hitBox -> h = 50;
		if (type == Fish) {
			vector<string> frames = {"assets/fish/guppy3.png", "assets/fish/guppy4.png", "assets/fish/guppy5.png", "assets/fish/guppy6.png", "assets/fish/guppy7.png", "assets/fish/guppy8.png", "assets/fish/guppy9.png"};
			ani = new Animation(frames, hitBox, stage -> renderer);
		}
	} else if (type == Ultravore || type == Carnivore) {
		hungerRate = 30; // Needs to eat every 30 seconds
		if (type == Carnivore){
			hitBox -> w = 200;
			hitBox -> h = 150;
		} else {
			hitBox -> w = 450;
			hitBox -> h = 350;
		}
	}
}

bool Entity::ageUp() {
	age = (Age)(age + 1);
	switch (age){
		case Teen: {
			if (type == Fish){

			} else if (type == Breeder) {

			}
			break;
		}
		case Adult: {
			if (type == Fish){

			} else if (type == Breeder) {

			}
			break;
		}
		case Royal: {
			if (type == Fish){

			} else if (type == Breeder) {

			}
			break;
		}
		default:;
	}
	return true;
}

void Entity::render() {
	// cerr << this << endl;
	struct timeval tNow;
	gettimeofday(&tNow, NULL);
	u64 now = ((tNow.tv_sec * 1000UL) + (tNow.tv_usec / 1000UL));
	// Can I do this? lol
	if ((now - lastRender) % 50 > 40) {
		lastRender = now;
		//TODO: Move fish around, have eat, have grow, etc...

		// cerr << "Target (x,y): (" << targetX << "," << targetY << ")" << endl;

		// cerr << "hitbox: " << hitBox -> x << " target: " << targetX << endl;
		if ((hitBox -> x != targetX || (hitBox -> x - targetX) > XSPEED) && (hitBox -> y != targetY || (hitBox -> y - targetY) > YSPEED)) {
			if (targetX > hitBox -> x && targetY > hitBox -> y) {
				hitBox -> x += XSPEED;
				hitBox -> y += YSPEED;
			} else if (targetX > hitBox -> x && targetY < hitBox -> y) {
				hitBox -> y -= YSPEED;
				hitBox -> x += XSPEED;
			} else if (targetX < hitBox -> x && targetY < hitBox -> y) {
				hitBox -> x -= XSPEED;
				hitBox -> y -= YSPEED;
			} else if (targetX < hitBox -> x && targetY > hitBox -> y) {
				hitBox -> y += YSPEED;
				hitBox -> x -= XSPEED;
			} else if (targetX > hitBox -> x) {
				hitBox -> x += XSPEED;
			} else if (targetY > hitBox -> y) {
				hitBox -> y += YSPEED;
			} else if (targetX < hitBox -> x) {
				hitBox -> x -= XSPEED;
			} else if (targetY < hitBox -> y) {
				hitBox -> y -= YSPEED;
			} else {
				cerr << "Failed to target" << endl;
			}
		} else {
			targetX = (rand() % stage -> winWidth);
			targetY = (rand() % stage -> winHeight);
			cerr << "Ending Target (x,y): (" << targetX << "," << targetY << ")" << endl;
		}
		ani -> nextFrame();
	}
	
	ani -> render();
}
