#include <stdbool.h>

#include "ball.h"

#include "types.h"

bool detect_edge(Ball_t ball)
{
	if (ball.y >= 100 || ball.y <= 0) {
		return true;
	}

	return false;
}

void manage_collision_player(Ball_t *ball, Player_t player)
{
	ball->v_y += player.v_y;
	ball->v_x *= -1;
}

void manage_collision_wall(Ball_t *ball)
{
	ball->v_y *= -1;
}

void move_ball(Ball_t *ball)
{
	if (ball->x >= 0 && ball->x + ball->r <= 200) {
		ball->x += ball->v_x;
	}

	if (ball->y >= 0 && ball->y + ball->r <= 100) {
		ball->y += ball->v_y;
	}
}
