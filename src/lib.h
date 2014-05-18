#include "types.h"

#ifndef PNOG_EXT_LIB
#define PNOG_EXT_LIB

void init_lib(void);
void manage_input(States_t);
void draw_menu(void);
void draw_game(Game_t);
int get_time(void);
void cleanup(void);

#endif

