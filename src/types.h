#ifndef PNOG_TYPES
#define PNOG_TYPES

typedef struct Player {
	int x;
	int y;
	int w;
	int h;
	int score;
	float v_y;
} Player_t;

typedef struct Ball {
	int x;
	int y;
	int r;
	float v_x;
	float v_y;
} Ball_t;

typedef enum {
	MENU,
	GAME,
	OPTIONS,
	PAUSED,
	STOPPED
} States_t;

typedef struct Game {
	States_t state;
	Player_t player;
	Player_t cpu;
	Ball_t ball;
} Game_t;

#endif

