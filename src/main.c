#include <stdio.h>
#include <stdbool.h>

#include "game.h"
#include "lib.h"
#include "vars.h"

int main()
{
	init_lib();

	Game_t* game = malloc(sizeof(game));

	init_game(game);
	play(game);

	clean_lib();
	free(game);

	return 0;
}

