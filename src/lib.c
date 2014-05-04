#include <stdlib.h>
#include <stdarg.h>

#include <SDL2/SDL.h>

#include "lib.h"
#include "vars.h"

SDL_Window *window;
SDL_Renderer *ren;

void init_lib()
{
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		printf("error:SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow(
			"pnog",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			0 );
	if (window == NULL) {
		printf("error:SDL_CreateWindow: %s", SDL_GetError());
		exit(1);
	}

	ren = SDL_CreateRenderer(
		window,
			-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if (ren == NULL) {
		printf("error:SDL_CreateRenderer: %s", SDL_GetError());
		exit(1);
	}
}

void manage_input()
{
	SDL_Event event;
	switch (SDL_PollEvent(&event)) {
		default:
			break;
	}
}

void draw(int count, ...)
{
	count = 0;
}

void play_sound()
{
}

void play_music()
{
}

void cleanup()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(ren);
	SDL_Quit();
}

