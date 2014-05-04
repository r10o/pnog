#include "types.h"
#include "cpu.h"

void manage_cpu(Player_t *cpu, Ball_t *ball)
{
	if (ball->v[0] > 0) {
		if (cpu->rectangle.y + (cpu->rectangle.h / 2) > ball->rectangle.y + (ball->rectangle.h / 2)) {
			cpu->v = 20;
		} else if (cpu->rectangle.y + (cpu->rectangle.h / 2) < ball->rectangle.y + (ball->rectangle.h / 2)) {
			cpu->v = -20;
		} else {
			cpu->v = 0;
		}
	} else {
		cpu->v = 0;
	}
}
