#ifndef PNOG_EXT_LIB
#define PNOG_EXT_LIB

#include <SDL2/SDL.h>

#include "game.h"

SDL_Window *window;

void init_lib();
void manage_input(Game_t*);
void draw_menu();
void draw_game(Game_t*);
int get_time();
void clean_lib();

#endif

