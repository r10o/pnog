#include "types.h"
#include "vars.h"
#include "lib.h"

void run()
{
	while (game.state != STOPPED) {
		switch (game.state) {
			case MENU:
				break;
			case GAME:
				while (game.state == GAME) {
					manage_input();
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

