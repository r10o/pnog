#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct Ball {
	SDL_Rect rectangle;
	float v[2];
} Ball_t;

typedef struct Player {
	SDL_Rect rectangle;
	int score;
	float v;
} Player_t;

static const int screen_width = 800;					// width of the screen
static const int screen_height = 400;					// height of the screen in pixels

static const int player_width = 10;					// width of the player paddle
static const int player_height = 80;					// height of the player paddle

static const int ball_radius = 10;					// radius of the ball

static const int ticks_per_second = 30;					// ticks per second
static const int milliseconds_per_tick = 1000 / ticks_per_second;	// time per tick in milliseconds

int main(int argc, char *argv[])
{
	// Parsing Arguments
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

	// Initializing the SDL library
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf(stderr, "pnog:SDL_Init: %s.\n", SDL_GetError());
		return 1;
	}

	// Create the game window
	SDL_Window *window = SDL_CreateWindow(
		"pnog",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		screen_width,
		screen_height,
		SDL_WINDOW_SHOWN
	);
	if (window == NULL) {
		fprintf(stderr, "pnog:SDL_CreateWindow: %s.\n", SDL_GetError());
		return 1;
	}

	// Create the render window
	SDL_Renderer *ren = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	); 
	if (ren == NULL) {
		fprintf(stderr, "pnog:SDL_CreateRenderer: %s.\n", SDL_GetError()); 
		return 1;
	}

	// initialize the player paddle and velocity
	Player_t player;
	player.rectangle.x = 20;
	player.rectangle.y = 160;
	player.rectangle.h = player_height;
	player.rectangle.w = player_width;
	player.v = 0;

	// initialize the CPU paddle and velocity
	Player_t cpu;
	cpu.rectangle.x = 770;
	cpu.rectangle.y = 160;
	cpu.rectangle.h = player_height;
	cpu.rectangle.w = player_width;
	cpu.v = 0;

	// initialize the ball paddle and velocity
	Ball_t ball;
	ball.rectangle.x = 395;
	ball.rectangle.y = 195;
	ball.rectangle.h = ball_radius;
	ball.rectangle.w = ball_radius;
	ball.v[0] = 20;
	ball.v[1] = 0;

	bool running = true;				// determines if the game loop is running

	SDL_Event event;				// the SDL_Event variable to track player events
	unsigned int current_time;			// tracks current time in milliseconds
	unsigned int prev_time = SDL_GetTicks();	// tracks the time previously the current time

	// game loop
	while (running) {
		// manage events
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_UP:
							player.v = -20;
							break;
						case SDLK_w:
							player.v = -20;
							break;
						case SDLK_DOWN:
							player.v = 20;
							break;
						case SDLK_s:
							player.v = 20;
							break;
						default: break;
					}
				case SDL_KEYUP:
					switch (event.key.keysym.sym) {
						case SDLK_UP:
							if (player.v > 0)
								player.v = 0;
							break;
						case SDLK_w:
							if (player.v > 0)
								player.v = 0;
							break;
						case SDLK_DOWN:
							if (player.v < 0)
								player.v = 0;
							break;
						case SDLK_s:
							if (player.v < 0)
								player.v = 0;
							break;
						case SDLK_ESCAPE:
							running = false;
							break;
						default: break;
					}
				default: break;
			}
		}

		// manage CPU movement based off of the movement of the ball
		if (ball.v[0] > 0) {
			if (cpu.rectangle.y - (cpu.rectangle.h - ball.rectangle.h) / 2 > ball.rectangle.y) {
				cpu.v = 1;
			} else if (cpu.rectangle.y - (cpu.rectangle.h - ball.rectangle.h) / 2 < ball.rectangle.y) {
				cpu.v = -1;
			} else {
				cpu.v = 0;
			}
		} else {
			cpu.v = 0;
		}

		// draw once every tick
		current_time = SDL_GetTicks();
		if (current_time - prev_time > milliseconds_per_tick) {
			prev_time = current_time;

			// have the player move with respect to its velocity, within the bounds of the screen
			if (player.rectangle.y < 320 || player.v < 0) {
				player.rectangle.y += player.v;
			}
			if (player.rectangle.y > 0 || player.v > 0) {
				player.rectangle.y += player.v;
			}

			// have the CPU move with respect to its velocity, within the bounds of the screen
			if (cpu.rectangle.y < 320 || cpu.v < 0) {
				cpu.rectangle.y += cpu.v;
			}
			if (cpu.rectangle.y > 0 || cpu.v > 0) {
				cpu.rectangle.y += cpu.v;
			}

			// have the ball move with respect to its velocity, within the bounds of the screen
			if (ball.rectangle.y < 400 && ball.rectangle.y > 0) {
				if (ball.rectangle.x < 800 && ball.rectangle.x > 0) {
					ball.rectangle.x += ball.v[0];
					ball.rectangle.y += ball.v[1];
				}
			}

			// manage collisions between the ball and the players (player and CPU)
			if (SDL_HasIntersection(&ball.rectangle, &player.rectangle)) {
				ball.v[0] *= -1;
				ball.v[1] += player.v;
			} else if (SDL_HasIntersection(&ball.rectangle, &cpu.rectangle)) {
				ball.v[0] *= -1;
				ball.v[1] += cpu.v;
			}

			printf("*********************\n");
			printf("player: (%d, %d), (%d, %d)\n", player.rectangle.x, player.rectangle.y, player.rectangle.w, player.rectangle.h);
			printf("cpu: (%d, %d), (%d, %d)\n", cpu.rectangle.x, cpu.rectangle.y, cpu.rectangle.w, cpu.rectangle.h);
			printf("ball: (%d, %d), (%d, %d)\n", ball.rectangle.x, ball.rectangle.y, ball.rectangle.w, ball.rectangle.h);
			printf("*********************\n");

			// clear the screen with white
			SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(ren);

			// set the color back to black
			SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);

			// draw the outlines of the player, CPU and ball
			SDL_RenderDrawRect(ren, &player.rectangle);
			SDL_RenderDrawRect(ren, &cpu.rectangle);
			SDL_RenderDrawRect(ren, &ball.rectangle);

			// fill the outlines of the player, CPU and ball
			SDL_RenderFillRect(ren, &player.rectangle);
			SDL_RenderFillRect(ren, &cpu.rectangle);
			SDL_RenderFillRect(ren, &ball.rectangle);

			// draw to the window
			SDL_RenderPresent(ren);
		}
	}

	// SDL cleanup
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

