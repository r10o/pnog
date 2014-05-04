#include <stdlib.h>
#include <stdbool.h>

#include "types.h"
#include "var.h"

void init_player(Player_t *_player, bool cpu)
{
	_player->rectangle.x = cpu ? 770 : 20;
	_player->rectangle.y = 160;
	_player->rectangle.w = PLAYER_WIDTH;
	_player->rectangle.h = PLAYER_HEIGHT;

	_player->score = 0;
	_player->v = 0;
}

void add_score(Player_t *_player)
{
	_player->score += 1;
}

void reset_score(Player_t *_player)
{
	_player->score = 0;
}

void move_player(Player_t *_player)
{
	if (_player->rectangle.y < 320 && _player->rectangle.y > 0) {
		_player->rectangle.y += _player->v;
	} else if (_player->rectangle.y < 320) {
		if (_player->v > 0) {
			_player->rectangle.y += _player->v;
		}
	} else if (_player->rectangle.y > 0) {
		if (_player->v < 0) {
			_player->rectangle.y += _player->v;
		}
	}
}

void manage_collisions(Player_t *_player, Ball_t *_ball)
{
	if (SDL_HasIntersection(&_player->rectangle, &_ball->rectangle)) {
		_ball->v[0] *= -1;
		_ball->v[1] *= _player->v;
	}
}

