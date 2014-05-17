#include <stdlib.h>
#include <stdarg.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "lib.h"
#include "vars.h"

SDL_Window *window;
SDL_Renderer *ren;

void init_lib()
{
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf(stderr, "error:SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow(
			"pnog",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_OPENGL );
	if (window == NULL) {
		fprintf(stderr, "error:SDL_CreateWindow: %s", SDL_GetError());
		exit(1);
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context == NULL) {
		fprintf(stderr, "error:SDL_GL_CreateContext: %s", SDL_GetError());
		exit(1);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	glewExperimental = GL_TRUE;
	glewInit();
	if (!GLEW_VERSION_3_1) {
		fprintf(stderr, "error:glewInit: %s\n", SDL_GetError());
		exit(1);
	}
}

void manage_input()
{
	SDL_Event event;
	const Uint8 *key_state;

	key_state = SDL_GetKeyboardState(NULL);
	if (key_state[SDL_SCANCODE_Q]) {
		game.player.v_y = -20;
	} else if (key_state[SDL_SCANCODE_A]) {
		game.player.v_y = 20;
	} else {
		game.player.v_y = 0;
	}

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game.state = STOPPED;
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						game.state = PAUSED;
						break;
				}
		}
	}
}

void draw(int count, ...)
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glOrtho(0, 1, 0, 1, -1, 1);
	glBegin(GL_POLYGON);
		glVertex3f(0.25, 0.25, 0);
	glEnd();
	glFlush();

	SDL_GL_SwapWindow(window);
	count = 0;
}

void play_sound()
{
}

void play_music()
{
}

void cleanup()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(ren);
	SDL_Quit();
}

