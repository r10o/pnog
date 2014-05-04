#ifndef PNOG_MAIN
#define PNOG_MAIN

#include <SDL2/SDL.h>

// the ball structure
typedef struct Ball {
	SDL_Rect rectangle;	// position rectangle
	float v[2];		// velocity array
} Ball_t;

// the player structure
typedef struct Player {
	SDL_Rect rectangle;	// position rectangle
	float v;		// vertical velocity
	unsigned int score;	// player score
} Player_t;

#endif

