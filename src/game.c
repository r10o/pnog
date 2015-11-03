#include <stdio.h>
#include <stdlib.h>

#include "game.h"

#include "vars.h"
#include "lib.h"
#include "player.h"
#include "ball.h"

void init_game(Game_t* game)
{
	game->state = GAME;
	
	game->player = malloc(sizeof(Player_t));
	game->player->x = 2;
	game->player->y = 42;
	game->player->w = 2;
	game->player->h = 16;
	game->player->score = 0;
	game->player->v_y = 0;

	game->cpu = malloc(sizeof(Player_t));
	game->cpu->x = 196;
	game->cpu->y = 42;
	game->cpu->w = 2;
	game->cpu->h = 16;
	game->cpu->score = 0;
	game->cpu->v_y = 0;

	game->ball = malloc(sizeof(Ball_t));
	game->ball->x = 99;
	game->ball->y = 49;
	game->ball->r = 2;
	game->ball->v_x = -3;
	game->ball->v_y = 0;
}

void reset_turn(Game_t* game)
{
	int temp_scores[2];
	temp_scores[0] = game->player->score;
	temp_scores[1] = game->cpu->score;
	init_game(game);
	game->player->score = temp_scores[0];
	game->cpu->score = temp_scores[1];

	printf("%d <-> %d\n", game->player->score, game->cpu->score);
}

void score_point(Player_t* player)
{
	player->score++;
}

void update_game(Game_t* game)
{
	if (detect_collision(game->ball, game->player, PNOG_COLLISION_PLAYER)) {
		manage_collision_player(game->ball, game->player);
	}

	if (detect_collision(game->ball, game->cpu, PNOG_COLLISION_CPU)) {
		manage_collision_player(game->ball, game->cpu);
	}

	if (detect_edge(game->ball)) {
		manage_collision_wall(game->ball);
	}

	move_player(game->player);
	move_player(game->cpu);
	move_ball(game->ball);

	if (game->ball->x <= 0) {
		score_point(game->cpu);
		reset_turn(game);
	} else if (game->ball->x + game->ball->r >= 200) {
		score_point(game->player);
		reset_turn(game);
	}

}

void run_game(Game_t* game)
{
	int current_time = get_time();
	int previous_time;
	while (game->state == GAME) {
		previous_time = current_time;
		current_time = get_time();
		
		manage_input(game);
		if (current_time - previous_time >= TIME_PER_TICK) {
			update_game(game);
		}

		draw_game(game);
	}
}

void play(Game_t* game)
{
	while (game->state != STOPPED) {
		switch (game->state) {
			case MENU: break;
			case GAME: run_game(game); break;
			case OPTIONS: break;
			case PAUSED: break;
			default: break;
		}
	}
}

