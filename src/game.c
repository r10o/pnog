#include "types.h"
#include "vars.h"

void run()
{
	while (game.state != STOPPED) {
		switch (game.state) {
			case MENU:
				break;
			case GAME:
				while (game.state == GAME) {
				}
				break;
			case OPTIONS:
				break;
			case PAUSED:
				break;
			default: break;
		}
	}
}

