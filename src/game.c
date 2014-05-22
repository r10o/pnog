#include <stdio.h>

#include "game.h"

#include "types.h"
#include "vars.h"
#include "lib.h"
#include "player.h"
#include "ball.h"

void init_game()
{
	game.state = GAME;
	game.player = (Player_t){ 2, 42, 2, 16, 0, 0 };
	game.cpu = (Player_t){ 196, 42, 2, 16, 0, 0 };
	game.ball = (Ball_t){ 97, 47, 2, -3, 0 };
}

void update_game()
{
	if (detect_collision(game.ball, game.player, PNOG_COLLISION_PLAYER)) {
		manage_collision_player(&game.ball, game.player);
	}

	if (detect_collision(game.ball, game.cpu, PNOG_COLLISION_CPU)) {
		manage_collision_player(&game.ball, game.cpu);
	}

	if (detect_edge(game.ball)) {
		manage_collision_wall(&game.ball);
	}

	move_player(&game.player);
	move_player(&game.cpu);
	move_ball(&game.ball);
}

void run_game()
{
	int current_time = get_time();
	int previous_time;
	while (game.state == GAME) {
		previous_time = current_time;
		current_time = get_time();
		
		manage_input(game.state);
		if (current_time - previous_time >= TIME_PER_TICK) {
			update_game();
		}

		draw_game(game);
	}
}

void play()
{
	while (game.state != STOPPED) {
		switch (game.state) {
			case MENU: break;
			case GAME: run_game(); break;
			case OPTIONS: break;
			case PAUSED: break;
			default: break;
		}
	}
}

