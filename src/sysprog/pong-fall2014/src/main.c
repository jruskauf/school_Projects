#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include "pong.h"

int main(int argc, char **argv)
{
//	----------------------------------- DEFAULT -------------------------------------
	Pong    *game                     = NULL;
	Player  *ptmp                     = NULL;
	Object  *otmp                     = NULL;
	Missile *mtmp                     = NULL;
	Config  *cfg                      = NULL;
	int start_ticks                   = 0;
	int tally_ticks                   = 0;
	int i                             = 0; //What is this FOR

	debug                             = NULL;
	output                            = stdout;
	verbose                           = NULL;
	verbose2                          = NULL;
	verbose3                          = NULL;
	verbosity_level                   = 0;

	game                              = (Pong *) malloc (sizeof(Pong) * 1);
	if (game                         == NULL)
		error(1, 0, "game = malloc()\n");

	game -> paddle                    = NULL;
	game -> ball                      = NULL;
	game -> item                      = NULL;

	game -> message                   = NULL;
	game -> font                      = NULL;
	game -> textColor.r               = 0xFF;
	game -> textColor.g               = 0xFF;
	game -> textColor.b               = 0xFF;
	game -> textalpha                 = SDL_ALPHA_OPAQUE;

	char playscore[64];	//SCORE ADDITION
	game -> score					  = NULL; //SCORE ADDITION

	//Game settings
	game -> num_paddles               = 4;
	game -> num_players               = 4;
	game -> field.width               = 640;
	game -> field.height              = 640;
	game -> field.bpp                 = 32;
	game -> num_missiles              = 1;
	game -> fps_cap                   = 1;
	game -> offset.x                  = 0;
	game -> offset.y                  = 0;
	game -> newserve                  = 1;
	game -> logos                     = 0;
	game -> sfx                       = 0;
	game -> wallflower				  = 0;
	game -> autopilot				  = OFF;

	game_quit                         = 0;

	sfx                               = NULL;
	readysfx                          = 0;
	ball[0]                           = NULL;
	ball[1]                           = NULL;
	ball[2]                           = NULL;

	if (argc                          > 1)
		cfg                           = args(argc, argv, game);

	game -> num[HWALL]                = 4 - game -> num_paddles;
	game -> num[VWALL]                = 4 - game -> num_paddles - game -> num[HWALL];
	printf("num[VWALL]: %d\n", game->num[VWALL]);
	game -> num[HBLOCK]               = 0;
	game -> num[VBLOCK]               = 0;
	game -> num[FBLOCK]               = 0;
//	-------------------------------- END OF DEFAULT ---------------------------------

//	------------------------------- DEBUG STUFF -------------------------------------
	if (debug                        == NULL)
	{
		debug                         = fopen("/dev/null", "w");
		if (debug                    == NULL)
			error(1, 0, "debug = fopen()\n");
	}
	else
		fprintf(debug, "[debug] Debugging ENABLED\n");
	
	if (verbose                      == NULL)
	{
		verbose                       = fopen("/dev/null", "w");
		if (verbose                  == NULL)
			error(1, 0, "verbose = fopen()\n");
	}
	else
		fprintf(debug, "[debug] Verbosity ENABLED, level %d\n", verbosity_level);

	if (verbose2                     == NULL)
	{
		verbose2                      = fopen("/dev/null", "w");
		if (verbose2                 == NULL)
			error(1, 0, "verbose2 = fopen()\n");
	}

	if (verbose3                     == NULL)
	{
		verbose3                      = fopen("/dev/null", "w");
		if (verbose3                 == NULL)
			error(1, 0, "verbose3 = fopen()\n");
	}

	if (output                       == NULL)
	{
		output                        = fopen("/dev/null", "w");
		if (output                   == NULL)
			error(1, 0, "output = fopen()\n");
		fprintf(debug, "[debug] Output    DISABLED\n");
	}
//	---------------------------  END OF DEBUG STUFF ---------------------------------

//	---------------------- INITIALIZATION --------------------------
	game -> offset.w                  = game -> field.width;
	game -> offset.h                  = game -> field.height;

	fprintf(debug, "[debug] init() starting\n");
	game                              = init(game, cfg);
	fprintf(debug, "[debug] init() complete\n");
	if (game -> logos                == 1)
	{
		fprintf(debug, "[debug] title() starting\n");
		title(game);
		fprintf(debug, "[debug] title() complete\n");
	}
	else
		fprintf(verbose, "[verbose] title sequence DISABLED\n");

//	Setup Game Mode
	fprintf(debug, "[debug] set_scenario() starting\n");
	game                              = set_scenario(game, 1);
	fprintf(debug, "[debug] set_scenario() complete\n");

	fprintf(debug, "[debug] main game loop starting\n");
//	------------------- END OF INITIALIZATION ----------------------

//------------------------------------------------------------- Main Loop ------------------------------------------------------------------
	while (game_quit                 == 0)
	{
		SDL_BlitSurface(game->background, NULL, game->screen, &(game->offset));	//Draw in window

		start_ticks                   = SDL_GetTicks(); //Timer for frame lock

//		---------------------------------------- READY MESSAGE --------------------------------------------
		if (game -> newserve         == 1)
		{
			game -> message           = TTF_RenderText_Solid(game -> font, "READY", game -> textColor);
			if (game -> message      == NULL)
				error(2, 0, "game -> message = TTF_RenderText_Solid()\n");

			game -> textpos.x         = game->field.width /2 - game->message -> w/2;
			game -> textpos.y         = game->field.height/2 - game->message -> h/2;

			SDL_SetAlpha(game    -> message, SDL_SRCALPHA, game -> textalpha);
			SDL_BlitSurface(game -> message, NULL, game->screen, &(game->textpos));

			tally_ticks               = tally_ticks + SDL_GetTicks();
			if ((tally_ticks          > 2000) &&
				(game -> textalpha   == SDL_ALPHA_OPAQUE))
			{
				sfx                   = ball[2];
				readysfx              = 1;
			}

			if ((tally_ticks          > 2000) &&
				(game -> textalpha    > 0))
			{
				game -> textalpha    -= 8;
			}
			else if ((tally_ticks     > 2000) &&
		  	         (game -> textalpha <= 0))
			{
				game -> newserve      = 0;
				game -> textalpha     = SDL_ALPHA_OPAQUE;
				tally_ticks           = 0;
			}

//			printf("tally_ticks: %d\n", tally_ticks);
//			printf("textalpha:   %d\n", game -> textalpha);
		}
//		------------------------------------- END OF READY MESSAGE ----------------------------------------

		game                          = input(game);

		game                          = collision(game);


//		----------------------------------- DISPLAY ----------------------------------
		ptmp                          = game -> paddle;
		while (ptmp                  != NULL)
		{
			sprintf(playscore, "%d", ptmp -> score);
			game -> score = TTF_RenderText_Solid(game -> font, playscore, game -> textColor);
			game -> stextpos.x = ((game->field.width / game->num_players) * ptmp->num);
			game -> stextpos.y = game->field.height /5;
			SDL_SetAlpha(game -> score, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
			SDL_BlitSurface(game -> score, NULL, game->screen, &(game->stextpos));
//			printf("ptmp -> score is: %d\n", ptmp -> score);

			if ((game -> autopilot > 1) && (ptmp -> autopilot != ON))
			{
				ptmp -> autopilot = ON;
				game -> autopilot--;
			}
			else if (game -> autopilot == OFF)
				ptmp -> autopilot = OFF;

			if (game -> autopilot == ON && ptmp -> autopilot == ON)
			{
				if (ptmp -> ORIENTATION == LEFT || ptmp -> ORIENTATION == RIGHT)
				{
					ptmp -> pos.y = game -> ball -> pos.y  - (ptmp -> pos.h/2) + (game -> ball -> high/2);
				}
				else
				{
					ptmp -> pos.x = game -> ball -> pos.x + (game -> ball -> wide/2) - (ptmp -> pos.w/2);
				}
			}
			else
			{
					if (ptmp -> ORIENTATION == LEFT || ptmp -> ORIENTATION == RIGHT)
						ptmp -> pos.y	+= ptmp -> move;
					else 	
						ptmp -> pos.x	+= ptmp -> move;
			}
//paddle hit alpha change
			if (ptmp -> Phit > 0)
			{
				ptmp -> phit = 0xff;
				ptmp -> Phit = 0;
			}
			else if (ptmp -> phit > 0x7f)
    	        ptmp -> phit = ptmp -> phit - 4;
	        else
       	    	ptmp -> phit = 0x7f;

			SDL_SetAlpha(ptmp -> sprite, SDL_SRCALPHA, ptmp -> phit);
//end paddle hit alpha change
	
			SDL_BlitSurface(ptmp -> sprite, NULL, game -> screen, &(ptmp -> pos));
			ptmp                      = ptmp -> next;
		}

		mtmp = game -> ball;
		while (mtmp                  != NULL)
		{
			mtmp -> pos.x            += mtmp -> xmove;
			mtmp -> pos.y            += mtmp -> ymove;

//ball hit alpha change
	        if (mtmp -> Bhit > 0)
	        {   
	            mtmp -> bhit = 0xff;
	            mtmp -> Bhit = 0;
	        }   
	        else if (mtmp -> bhit > 0x7f)
	            mtmp -> bhit = mtmp -> bhit - 4;
   	        else
            	mtmp -> bhit = 0x7f;
	
            SDL_SetAlpha(mtmp -> sprite, SDL_SRCALPHA, mtmp -> bhit);
//end ball hit alpha change

			SDL_BlitSurface(mtmp -> sprite, NULL, game -> screen, &(mtmp -> pos));
			mtmp                      = mtmp -> next;
		}

		otmp = game -> item;
		while (otmp                  != NULL)
		{
			SDL_BlitSurface(otmp -> sprite, NULL, game -> screen, &(otmp -> pos));
			otmp                      = otmp -> next;
		}

		if (SDL_Flip(game -> screen) == -1)
		{
			fprintf(stderr, "[error] SDL_Flip()\n");
			exit(3);
		}
//		-------------------------------- END OF DISPLAY ------------------------------

//		-- FRAME LOCK --
		if ((game -> fps_cap         == 1) && ((SDL_GetTicks() - start_ticks) < 1000 / FRAMES_PER_SECOND))
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - (SDL_GetTicks() - start_ticks));
		}
	}

//	---------------------- GAME END --------------------
	fprintf(debug, "[debug] main game loop complete\n");

	fprintf(debug, "[debug] deinit() starting\n");
	deinit(game);
	fprintf(debug, "[debug] deinit() complete\n");

	fprintf(debug, "[debug] game complete\n");

	if (debug      != stdout)
		fclose(debug);

	if (output     != stdout)
		fclose(output);

	if (verbose    != stdout)
		fclose(verbose);
//	------------------- END OF GAME END ----------------

	return(0);
}
