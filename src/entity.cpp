#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>
#include <cmath>

#include "type.h"
#include "entity.h"
#include "stage.h"
#include "graphics/animation.h"

using namespace std;

#define MAXXSPEED 5
#define MAXYSPEED 5
#define DELTAX 1
#define DELTAY 1


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
	originX = hitBox -> x;
	originY = hitBox -> y;
	targetX = (rand() % stage -> winWidth);
	targetY = (rand() % stage -> winHeight);
	// cerr << "Ending Target (x,y): (" << targetX << "," << targetY << ")" << endl;
	
	dx = 0;
	dy = 0;

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
	struct timeval tNow;
	gettimeofday(&tNow, NULL);
	u64 now = ((tNow.tv_sec * 1000UL) + (tNow.tv_usec / 1000UL));
	// Can I do this? lol
	// cerr << (now - start) % 10000 << endl;
	if ((now - start) % 100 > 75) {
		lastRender = now;
		//TODO: Move fish around, have eat, have grow, etc...

		if (abs(hitBox -> x - targetX) > MAXXSPEED || abs(hitBox -> y - targetY) > MAXYSPEED) {
			// cerr << "hitbox: " << hitBox -> x << " target: " << targetX << endl;
			if ((hitBox -> x != targetX && abs(hitBox -> x - targetX) > MAXXSPEED) || (hitBox -> y != targetY && abs(hitBox -> y - targetY) > MAXYSPEED)) {
				//If accelarating
				if (abs(targetX - hitBox -> x) >= (abs(targetX - originX) / 3) || abs(targetY - hitBox -> y) >= (abs(targetY - originY) / 3)) {
					// cerr << "positive" << endl;
					if (dx == 0) {
						dx = DELTAX;
					} else if (((targetX - hitBox -> x) / dx) == 0) {
						dx = DELTAX;
					} else if (dy == 0) {
						dy = DELTAY;
					} else if (((targetY - hitBox -> y) / dy) == 0) {
						dy = DELTAY;
					} else {
						if ((dx * ((targetX - hitBox -> x) / dx)) < MAXXSPEED) {
							dx = (dx * ((targetX - hitBox -> x) / abs(dx)));
						} else {
							dx = MAXXSPEED;
						}
						if ((dy * ((targetY - hitBox -> y) / dy)) < MAXYSPEED) {
							dy = (dy * ((targetY - hitBox -> y) / abs(dy)));
						} else {
							dy = MAXYSPEED;
						}
					}
				} else {
					// cerr << "negative" << endl;
					if (dx == 0) {
						dx = DELTAX;
					} else if (((targetX - hitBox -> x) / dx) == 0) {
						dx = DELTAX;
					} else if (dy == 0) {
						dy = DELTAY;
					} else if (((targetY - hitBox -> y) / dy) == 0) {
						dy = DELTAY;
					} else {
						if ((dx / ((targetX - hitBox -> x) / dx)) < (0 - MAXXSPEED)) {
							dx = (dx / ((targetX - hitBox -> x) / abs(dx)));
						} else {
							dx = (0 - MAXXSPEED);
						}
						if ((dy / ((targetY - hitBox -> y) / dy)) < (0 - MAXYSPEED)) {
							dy = (dy / ((targetY - hitBox -> y) / abs(dy)));
						} else {
							dy = (0 - MAXYSPEED);
						}
					}
				}
				//Submit speed
				// cerr << "dx: " << dx << " dy: " << dy << endl;
				hitBox -> x += dx;
				hitBox -> y += dy;
			}
		} 
		
		if ((now - start) % 10000 > 9980) {
			// cerr << "hitbox: " << hitBox -> x << " hitbox y: " << hitBox -> y << endl;
			targetX = (rand() % (stage -> winWidth - (stage -> winWidth / 16))) + (stage -> winWidth / 16);
			targetY = (rand() % (stage -> winHeight - (stage -> winHeight / 16))) + (stage -> winHeight / 16);
			originX = hitBox -> x;
			originY = hitBox -> y;
			// cerr << "hitbox x: " << hitBox -> x << " hitbox y: " << hitBox -> y << endl;
			// cerr << "Ending Target (x,y): (" << targetX << "," << targetY << ")" << endl;
		}
		ani -> nextFrame();
	}
	
	ani -> render();
}
