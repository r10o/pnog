#include <stdlib.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "lib.h"
#include "vars.h"
#include "game.h"
#include "ball.h"
#include "player.h"

void init_lib()
{
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf(stderr, "error:SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow("pnog", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		fprintf(stderr, "error:SDL_CreateWindow: %s", SDL_GetError());
		exit(1);
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context == NULL) {
		fprintf(stderr, "error:SDL_GL_CreateContext: %s", SDL_GetError());
		exit(1);
	}


	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "error:glewInit: %s\n", SDL_GetError());
		exit(1);
	}

	glViewport(0, 0, 800, 600);
}

void manage_input(Game_t* game)
{
	SDL_Event event;
	const Uint8 *key_state;

	key_state = SDL_GetKeyboardState(NULL);

	switch (game->state) {
		case MENU: break;
		case GAME:
			   if (key_state[SDL_SCANCODE_Q]) {
				   game->player->v_y = 4;
			   } else if (key_state[SDL_SCANCODE_A]) {
				   game->player->v_y = -4;
			   } else if (key_state[SDL_SCANCODE_K]) {
				   game->player->v_y = 4;
			   } else if (key_state[SDL_SCANCODE_J]) {
				   game->player->v_y = -4;
			   } else {
				   game->player->v_y = 0;
			   }

			   if (SDL_PollEvent(&event)) {
				   switch (event.type) {
					   case SDL_QUIT:
						   game->state = STOPPED;
						   break;
					   case SDL_KEYUP:
						   switch (event.key.keysym.sym) {
							   case SDLK_ESCAPE:
								   game->state = PAUSED;
								   break;
						   }
				   }
			   }
			   break;
		case OPTIONS: break;
		case PAUSED:
			      if (SDL_PollEvent(&event)) {
				      switch (event.type) {
					      case SDL_QUIT:
						      game->state = STOPPED;
						      break;
					      case SDL_KEYUP:
						      switch (event.key.keysym.sym) {
							      case SDLK_ESCAPE:
								      game->state = GAME;
								      break;
						      }
				      }
			      }
			      break;
		default: break;
	}
}

void draw_player(Player_t* player)
{
	glBegin(GL_POLYGON);
		glVertex2i(player->x, player->y);
		glVertex2i(player->x + player->w, player->y);
		glVertex2i(player->x + player->w, player->y + player->h);
		glVertex2i(player->x, player->y + player->h);
	glEnd();
}

void draw_ball(Ball_t* ball)
{
	float theta = 2 * 3.1415926 / 40.0f;
	float tangetial_factor = tanf(theta);

	float radial_factor = cosf(theta);

	float x = ball->r;

	float y = 0;

	glBegin(GL_POLYGON);
	for (int i = 0; i < 40; i++) {
		glVertex2f(x + ball->x, y + ball->y);

		float tx = -y;
		float ty = x;

		x += tx * tangetial_factor; 
		y += ty * tangetial_factor; 

		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}

void draw_game(Game_t* game)
{
	glClear(GL_COLOR_BUFFER_BIT);

	draw_player(game->player);
	draw_player(game->cpu);
	draw_ball(game->ball);

	glFlush();

	SDL_GL_SwapWindow(window);
}

int get_time()
{
	return SDL_GetTicks();
}

void clean_lib()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

