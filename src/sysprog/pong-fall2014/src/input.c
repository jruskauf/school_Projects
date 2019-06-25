#include <stdio.h>
#include <stdlib.h>
#include "pong.h"

#define  X_AXIS		0
#define  Y_AXIS		1

Pong *input(Pong * game)
{
	Player *ptmp = game->paddle;

	Uint8 *keystate;

	keystate = SDL_GetKeyState(NULL);
	if (SDL_PollEvent(&game->event))
	{
		while (ptmp != NULL)
		{
			if (keystate[ptmp->MOVEMENT1] == 1)
			{
				ptmp->move = -10;
				ptmp->autopilot = OFF;
			}
			else if (keystate[ptmp->MOVEMENT2] == 1)
			{
				ptmp->move = 10;
				ptmp->autopilot = OFF;
			}
			else if (keystate[SDLK_ESCAPE] == 1)
				game_quit = 1;
			else if (keystate[SDLK_TAB] == 1)
			{
				game -> autopilot = game -> num_players + 1;
			}
			else if (keystate[SDLK_SPACE] == 1)
			{
				game -> autopilot = OFF;
			}
			else if (game->event.key.keysym.sym == SDLK_RETURN)
			{
				game -> autopilot = OFF;
				game->fps_cap = !game->fps_cap;
				if (game->fps_cap == 0)
					fprintf(debug,
						"[debug] fps_cap is OFF\n");
				else
					fprintf(debug,
						"[debug] fps_cap is ON\n");
			}
			else if (game->event.type == SDL_QUIT)
				game_quit = 1;
			else if (game->event.type == SDL_JOYAXISMOTION)
			{
				if (SDL_JoystickGetAxis(ptmp->joystick, X_AXIS) < -3200)
				{
					fprintf(verbose2,
						"[info] player %d LEFT pressed\n",
						ptmp->num);
				}
				else if (SDL_JoystickGetAxis (ptmp->joystick, X_AXIS) > 3200)
				{
					fprintf(verbose2, "[info] player %d RIGHT pressed\n", ptmp->num);
				}
				else if (SDL_JoystickGetAxis (ptmp->joystick, Y_AXIS) < -3200)
				{
					fprintf(verbose2, "[info] player %d UP pressed\n", ptmp->num);
				}
				else if (SDL_JoystickGetAxis (ptmp->joystick, Y_AXIS) > 3200)
				{
					fprintf(verbose2, "[info] player %d DOWN pressed\n", ptmp->num);
				}
			}
			else if (game->event.type == SDL_JOYBUTTONDOWN)
			{
				if (SDL_JoystickGetButton (ptmp->joystick, game->event.jbutton.button) == 1)
				{
					fprintf(verbose2, "[info] player %d button %d pressed\n", ptmp->num, game->event.jbutton.button);
				}
			}
			else
			{
//				printf("in the place we want to be\n");
				ptmp->move = 0;
			}
			ptmp = ptmp->next;
		}
	}

	return (game);
}
