#include <stdbool.h>

#include "types.h"

#ifndef PNOG_BALL
#define PNOG_BALL

bool detect_edge(Ball_t);
void manage_collision_player(Ball_t *, Player_t);
void manage_collision_wall(Ball_t *);
void move_ball(Ball_t *);

#endif
