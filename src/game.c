#include "types.h"
#include "vars.h"
#include "lib.h"

void init_game()
{
	game.state = GAME;
	game.player = (Player_t){ 1, 42, 1, 16, 0, 0 };
	game.cpu = (Player_t){ 198, 42, 1, 16, 0, 0 };
	game.ball = (Ball_t){ 99, 49, 2, 0, 0 };
}

void update_game(int elapsed_time)
{
	if (game.player.v_y < 0 && game.player.y > 0) {
		game.player.y = (game.player.v_y * elapsed_time) + game.player.y;
	} else {
		game.player.y = (game.player.v_y * elapsed_time) + game.player.y;
	}

	game.cpu.y = (game.cpu.v_y * elapsed_time) + game.cpu.y;
}

void run_game()
{
	int current_time = get_time();
	int previous_time;
	while (game.state == GAME) {
		previous_time = current_time;
		current_time = get_time();
		
		manage_input(game.state);
		update_game(current_time - previous_time);
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

