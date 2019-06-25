#include "pong.h"

void deinit(Pong *game)
{
	Player  *ptmp        = NULL;
	Player  *ptmp2       = NULL;
	Object  *otmp        = NULL;
	Object  *otmp2       = NULL;
	Missile *mtmp        = NULL;
	Missile *mtmp2       = NULL;
	int      i           = 0;

	SDL_FreeSurface(game -> screen);
	SDL_FreeSurface(game -> background);
	SDL_FreeSurface(game -> message);

	for (i = 0; i < 3; i++)
		Mix_FreeChunk(ball[i]);

	TTF_CloseFont(game -> font);

	ptmp                 = game -> paddle;
	while (ptmp         != NULL)
	{
		SDL_FreeSurface(ptmp -> sprite);
		free(ptmp -> filename);
		ptmp -> filename = NULL;
		SDL_JoystickClose(ptmp -> joystick);
		ptmp2            = ptmp;
		ptmp             = ptmp -> next;
		free(ptmp2);
		ptmp2            = NULL;
	}
		
	mtmp                 = game -> ball;
	while (mtmp         != NULL)
	{
		SDL_FreeSurface(mtmp -> sprite);
		free(mtmp -> filename);
		mtmp -> filename = NULL;
		mtmp2            = mtmp;
		mtmp             = mtmp -> next;
		free(mtmp2);
		mtmp2            = NULL;
	}

	otmp                 = game -> item;
	while (otmp         != NULL)
	{
		SDL_FreeSurface(otmp -> sprite);
		free(otmp -> filename);
		otmp2            = otmp;
		otmp             = otmp -> next;
		free(otmp2);
		otmp2            = NULL;
	}

	TTF_Quit();

	Mix_CloseAudio();

	SDL_Quit();
}
