#include <stdio.h>
#include <stdbool.h>

#include "player.h"
#include "ball.h"
#include "cpu.h"
#include "var.h"
#include "types.h"

#include "sdl.h"

int main(int argc, char *argv[])
{
	// parsing Arguments
	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			printf("%s\n", argv[i]);
			if (argv[i][0] == '-') {
				switch (argv[i][1]) {
					case 'v':
						printf("pnog version %s\n", VERSION);
						break;
					default:
						printf("Usage: pnog -[hv]\n \
							\t-h\tShow this text.\n \
							\t-v\tPrint program version.\n");
						break;
				}
			}
		}
		return 0;
	}

	// initialize the SDL library
	init_SDL();

	Player_t player;
	Player_t cpu;
	Ball_t ball;

	// initialize the player paddle and velocity
	init_player(&player, false);

	// initialize the CPU paddle and velocity
	init_player(&cpu, true);

	// initialize the ball paddle and velocity
	init_ball(&ball);

	// determines if the game loop is running
	bool running = true;

	// the SDL_Event variable to track player events
	SDL_Event event;

	// tracks current time in milliseconds
	unsigned int current_time;

	// tracks the time previously the current time
	unsigned int prev_time = SDL_GetTicks();

	// tacks the state of the keyboard
	const Uint8 *key_state;

	// game loop
	while (running) {
		// manage events
		key_state = SDL_GetKeyboardState(NULL);
		if (key_state[SDL_SCANCODE_Q]) {
			 player.v = -20;
		} else if (key_state[SDL_SCANCODE_A]) {
			 player.v = 20;
		} else {
			 player.v = 0;
		}

		if (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
							running = false;
							break;
					}
			}
		}

		// manage collisions between the ball and the players (player and CPU)
//		if (SDL_HasIntersection(&ball.rectangle, &player.rectangle)) {
//			ball.v[0] *= -1;
//			ball.v[1] += player.v;
//		} else if (SDL_HasIntersection(&ball.rectangle, &cpu.rectangle)) {
//			ball.v[0] *= -1;
//			ball.v[1] += cpu.v;
//		}

		manage_cpu(&player, &ball);
		manage_cpu(&cpu, &ball);

		// manage CPU movement based off of the movement of the ball
		manage_cpu(&cpu, &ball);
		move_player(&player);
		move_player(&player);
		move_ball(&ball);

		// draw once every tick
		current_time = SDL_GetTicks();
		if (current_time - prev_time > MILLISECONDS_PER_TICK) {
			prev_time = current_time;
			draw(3, &player.rectangle, &cpu.rectangle, &ball.rectangle);
		}
	}

	cleanup();

	return 0;
}

