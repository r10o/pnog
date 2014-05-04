#include <SDL2/SDL.h>

#ifndef PNOG_SDL
#define PNOG_SDL

SDL_Window *window;
SDL_Renderer *ren;

void init_SDL(void);
void draw(int, ...);
void cleanup(void);

#endif

