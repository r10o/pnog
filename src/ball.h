#ifndef PNOG_BALL
#define PNOG_BALL

#include <stdbool.h>

#include "player.h"

typedef struct Ball {
	int x;
	int y;
	int r;
	float v_x;
	float v_y;
} Ball_t;

bool detect_edge(Ball_t*);
void manage_collision_player(Ball_t*, Player_t*);
void manage_collision_wall(Ball_t*);
void move_ball(Ball_t*);

#endif

