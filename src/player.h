#ifndef PNOG_PLAYER
#define PNOG_PLAYER

#define PNOG_COLLISION_PLAYER 1
#define PNOG_COLLISION_CPU 0

#include <stdbool.h>

typedef struct Player {
	int x;
	int y;
	int w;
	int h;
	int score;
	float v_y;
} Player_t;

#include "ball.h"

bool detect_collision(Ball_t*, Player_t*, int);
void move_player(Player_t*);

#endif

