#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pong.h"

Player * alloc_player(Pong *game, Config *tmp, char *img_wd)
{
	Player *ptmp              = NULL;
	size_t  count             = 0;
 
	fprintf(verbose, "[verbose]    paddle %d:\n", tmp -> num);

	fprintf(verbose, "[verbose]\tmalloc ... ");
	ptmp                      = (Player *) malloc (sizeof(Player) * 1);
	if (ptmp                 == NULL)
	{
		fprintf(verbose, "FAIL\n");
		exit(6);
	}
	fprintf(verbose, "OK\n");

	ptmp -> num               = tmp -> num;
	ptmp -> type              = tmp -> type;

	fprintf(verbose, "[verbose]\t  type ... ");
	if (ptmp -> type         == HUMAN)
		fprintf(verbose, "HUMAN\n");
	else
		fprintf(verbose, "COMPUTER\n");
	
	ptmp -> location          = tmp -> location;
	fprintf(verbose, "[verbose]     location ... ");
	if (ptmp -> location     == LOCAL)
		fprintf(verbose, "LOCAL\n");
	else
		fprintf(verbose, "REMOTE\n");

	ptmp -> device            = tmp -> device;
	fprintf(verbose, "[verbose]\tdevice ... ");
	if (ptmp -> device       == JOYSTICK)
		fprintf(verbose, "JOYSTICK\n");
	else if (ptmp -> device  == MOUSE)
		fprintf(verbose, "MOUSE\n");
	else if (ptmp -> device  == NONE)
		fprintf(verbose, "NONE\n");
	else
		fprintf(verbose, "KEYBOARD\n");

	fprintf(verbose, "[verbose]\timage  ... ");
	count                     = strlen(img_wd)+strlen("/paddleXX.png");
	ptmp -> filename          = (char *) malloc (sizeof(char) * count);
	if (ptmp -> filename     == NULL)
	{
		fprintf(verbose, "FAIL\n");
		exit(6);
	}
	fprintf(verbose, "OK\n");

	sprintf(ptmp -> filename, "%s/paddle%.2d.png", img_wd, ptmp -> num);
	fprintf(debug, "[debug]  \tfile   ... %s\n", ptmp -> filename);

	fprintf(verbose, "[verbose]\tsprite ... ");
	ptmp -> sprite            = load_image(ptmp -> filename);
	if (ptmp -> sprite       == NULL)
	{
		fprintf(verbose, "FAIL\n");
		exit(6);
	}
	fprintf(verbose, "OK\n");

	if (ptmp -> device       == JOYSTICK)
	{
		fprintf(verbose, "[verbose]\tgamepad .. ");
		ptmp -> joystick      = SDL_JoystickOpen(game -> joystick_num++);
		ptmp -> joynum        = game -> joystick_num - 1;

		if (ptmp -> joystick == NULL)
			fprintf(verbose, "NO\n");
		else
			fprintf(verbose, "OK\n");

		fprintf(debug,"[info]\t\tID: %s\n",  SDL_JoystickName(ptmp -> joynum));
		fprintf(debug,"[info]\t\tAxis: %d\n",SDL_JoystickNumAxes(ptmp->joystick));
		fprintf(debug,"[info]\t\tButtons: %d\n",SDL_JoystickNumButtons(ptmp -> joystick));
	}
	else if (ptmp -> device  == KEYBOARD)
	{
		if (ptmp ->num       == 0)
		{
			ptmp -> MOVEMENT1 = SDLK_UP;
			ptmp -> MOVEMENT2 = SDLK_DOWN;
//			ptmp -> ORIENTATION = &(ptmp->pos.y);
			ptmp -> ORIENTATION = LEFT;
			game -> wallflower = game -> wallflower | LEFT;
		}
		else if (ptmp ->num  == 1)
        {   
            ptmp -> MOVEMENT1 = SDLK_w;
            ptmp -> MOVEMENT2 = SDLK_s;
			ptmp -> ORIENTATION = RIGHT;
			game -> wallflower = game -> wallflower | RIGHT;
        }
		else if (ptmp ->num  == 2)
		{
			ptmp -> MOVEMENT1 = SDLK_t;
			ptmp -> MOVEMENT2 = SDLK_g;
			ptmp -> ORIENTATION = TOP;
			game -> wallflower = game -> wallflower | TOP;
		}
		else if (ptmp -> num == 3)
		{
			ptmp -> MOVEMENT1 = SDLK_i;
			ptmp -> MOVEMENT2 = SDLK_k;
			ptmp -> ORIENTATION = BOTTOM;
			game -> wallflower = game -> wallflower | BOTTOM;
		}
	}
	else if (ptmp -> device  == MOUSE)
	{
		// mouse
	}
	else
	{
		// none, likely computer player
	}
	ptmp -> autopilot		  = OFF;
	ptmp -> move              = 0;
	ptmp -> score             = 0;
	ptmp -> wide              = ptmp -> sprite -> w;
	ptmp -> high              = ptmp -> sprite -> h;
	ptmp -> pos.x             = 0;
	ptmp -> pos.y             = 0;
	ptmp -> phit 			  = 0x7f;
	ptmp -> Phit			  = 0;
	ptmp -> next              = NULL;

	return (ptmp);
}
