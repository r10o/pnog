#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "lib.h"
#include "vars.h"
#include "game.h"
#include "ball.h"
#include "player.h"

#define VERTEX_SHADER 0
#define FRAGMENT_SHADER 0

void load_files(char* file_name, char** buffer) {
	FILE *f = fopen(file_name, "r");
	unsigned int file_size;
	if (f != NULL) {
		fseek(f, 0L, SEEK_END);
		file_size = ftell(f);
		fseek(f, 0L, SEEK_SET);
		*buffer = malloc(file_size);
		fread(*buffer, file_size, 1, f);
		fclose(f);
	} else {
		fprintf(stderr, "error:File \"%s\" could not be loaded\n", file_name);
		exit(EXIT_FAILURE);
	}
}

GLuint load_shader(int type)
{
	GLuint current_shader = glCreateShader((type == VERTEX_SHADER) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
	char* buffer;
	load_files((type == VERTEX_SHADER) ? "../rsc/shader/vertex.glsl" : "../rsc/shader/fragment.glsl", &buffer);
	const GLchar* current_shader_source = buffer;
	glShaderSource(current_shader, 1, &current_shader_source, NULL);
	glCompileShader(current_shader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(current_shader, GL_COMPILE_STATUS, &success);
	if (success) {
		return current_shader;
	}

	glGetShaderInfoLog(current_shader, 512, NULL, infoLog);
	fprintf(stderr, "error:Could not compile %s : %s\n", (type == VERTEX_SHADER) ? "vertex shader" : "fragment shader", infoLog);
	exit(EXIT_FAILURE);
}

void create_gl_program()
{
	GLuint vertex_shader = load_shader(VERTEX_SHADER);
	GLuint fragment_shader = load_shader(FRAGMENT_SHADER);
	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader_program, 512, NULL, infoLog);
		fprintf(stderr, "error:Could not link program : %s\n", infoLog);
		exit(EXIT_FAILURE);
	}

	glUseProgram(shader_program);
	
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void init_lib()
{
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf(stderr, "error:SDL_Init: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	create_gl_program();

	window = SDL_CreateWindow("pnog", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		fprintf(stderr, "error:SDL_CreateWindow: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	context = SDL_GL_CreateContext(window);
	if (context == NULL) {
		fprintf(stderr, "error:SDL_GL_CreateContext: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}


	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "error:glewInit: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
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

void prep_player(Player_t* player)
{
}

void prep_ball(Ball_t* ball)
{
}

void draw(unsigned int vao)
{
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void draw_game(Game_t* game)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 3; i++) {
		draw(game->drawables[i]);
	}

	SDL_GL_SwapWindow(window);
}

int get_time()
{
	return SDL_GetTicks();
}

void clean_lib()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

