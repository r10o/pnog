#include <stdbool.h>

#include "player.h"
#include "ball.h"

bool detect_edge(Ball_t* ball)
{
	if (ball->y >= 100 || ball->y <= 0) {
		return true;
	}

	return false;
}

void manage_collision_player(Ball_t* ball, Player_t* player)
{
	ball->v_y += player->v_y;
	ball->v_x *= -1;
}

void manage_collision_wall(Ball_t* ball)
{
	ball->v_y *= -1;
}

void move_ball(Ball_t* ball)
{
	if (ball->v_x < 0 && ball->x >= 0) {
		ball->x += ball->v_x;
	} else if (ball->v_x > 0 && ball->x <= 200) {
		ball->x += ball->v_x;
	}

	if (ball->v_y < 0 && ball->y >= 0) {
		ball->y += ball->v_y;
	} else if (ball->v_y > 0 && ball->y <= 100) {
		ball->y += ball->v_y;
	}
}

