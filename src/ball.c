#include "ball.h"
#include "types.h"
#include "var.h"

void init_ball(Ball_t *ball)
{
	ball->rectangle.x = 395;
	ball->rectangle.y = 195;
	ball->rectangle.h = BALL_RADIUS;
	ball->rectangle.w = BALL_RADIUS;

	ball->v[0] = -20;
	ball->v[1] = 0;
}

void reset_ball(Ball_t *ball)
{
	init_ball(ball);
}

void move_ball(Ball_t *ball)
{
	if (ball->rectangle.x < 790 && ball->rectangle.x > 0) {
		if (ball->rectangle.y < 390 && ball->rectangle.y > 0) {
			ball->rectangle.x += ball->v[0];
			ball->rectangle.y += ball->v[1];
		} else {
			ball->v[1] = -ball->v[1];
			ball->rectangle.x += ball->v[0];
			ball->rectangle.y += ball->v[1];
		}
	}
}
