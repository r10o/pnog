#ifndef PNOG_GAME
#define PNOG_GAME

#include "player.h"
#include "ball.h"

typedef enum {
	MENU,
	GAME,
	OPTIONS,
	PAUSED,
	STOPPED
} States_t;

typedef struct Game {
	States_t state;
	Player_t* player;
	Player_t* cpu;
	Ball_t* ball;
} Game_t;

void init_game(Game_t*);
void play(Game_t*);

#endif

