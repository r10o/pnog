#include <stdbool.h>

#include "types.h"

#ifndef PNOG_PLAYER
#define PNOG_PLAYER

#define PNOG_COLLISION_PLAYER 1
#define PNOG_COLLISION_CPU 0

bool detect_collision(Ball_t, Player_t, int);
void move_player(Player_t *);

#endif
