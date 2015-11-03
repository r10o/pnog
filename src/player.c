#include <stdbool.h>
#include <stdio.h>

#include "player.h"

bool detect_collision(Ball_t* ball, Player_t* player, int flag)
{
	if (flag) {
		if (ball->x <= player->x + player->w) {
			if (ball->y >= player->y && ball->y + ball->r <= player->y + player->h) {
				if (ball->y + ball->r <= player->y + player->h) {
					return true;
				}
			}
		}
	} else {
		if (ball->x + ball->r >= player->x) {
			if (ball->y >= player->y && ball->y + ball->r <= player->y + player->h) {
				if (ball->y + ball->r <= player->y + player->h) {
					return true;
				}
			}
		}
	}

	return false;
}

void move_player(Player_t* player)
{
	if (player->v_y > 0 && player->y + player->h <= 100) {
		player->y += player->v_y;
	} else if (player->v_y < 0 && player->y >= 0) {
		player->y += player->v_y;
	}
}

