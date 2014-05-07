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
	const Uint8 *key_state;

	key_state = SDL_GetKeyboardState(NULL);
	if (key_state[SDL_SCANCODE_Q]) {
		game.player.v_y = -20;
	} else if (key_state[SDL_SCANCODE_A]) {
		game.player.v_y = 20;
	} else {
		game.player.v_y = 0;
	}

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game.state = STOPPED;
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						game.state = PAUSED;
						break;
				}
		}
	}
}

void draw(int count, ...)
{
	for (int i = 0; i < count; i++) {
	}
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

