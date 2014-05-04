#include <stdarg.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "var.h"
#include "sdl.h"

void init_SDL()
{
	// initializing the SDL library
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf(stderr, "pnog:SDL_Init: %s.\n", SDL_GetError());
		exit(1);
	}

	// create the game window
	window = SDL_CreateWindow(
			"pnog",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN );
	if (window == NULL) {
		fprintf(stderr, "pnog:SDL_CreateWindow: %s.\n", SDL_GetError());
		exit(1);
	}

	// create the render window
	ren = SDL_CreateRenderer(
			window,
			-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ); 
	if (ren == NULL) {
		fprintf(stderr, "pnog:SDL_CreateRenderer: %s.\n", SDL_GetError()); 
		exit(1);
	}
}

void draw(int count, ...)
{
	// clear the screen with white
	SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(ren);

	// set the color back to black
	SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);

	va_list arg_list;
	va_start(arg_list, count);

	SDL_Rect *temp;

	for (int i = 0; i < count; i++) {
		temp = va_arg(arg_list, SDL_Rect *);
		printf("%d, %d, %d, %d\n",
				temp->x,
				temp->y,
				temp->w,
				temp->h );
		SDL_RenderDrawRect(ren, temp);
		SDL_RenderFillRect(ren, temp);
	}

	// draw to the window
	SDL_RenderPresent(ren);
}

void cleanup()
{
	// SDL cleanup
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

