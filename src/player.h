#include <stdbool.h>

#include "types.h"

#ifndef PNOG_PLAYER
#define PNOG_PLAYER

void init_player(Player_t *, bool);
void add_score(Player_t *);
void reset_score(Player_t *);
void move_player(Player_t *);

#endif

