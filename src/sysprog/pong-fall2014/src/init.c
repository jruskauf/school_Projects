#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pong.h"

Pong * init(Pong *game, Config *cfg)
{
	char     *img_wd                  = NULL;
	char     *img_filename            = NULL;
	char     *txt_wd                  = NULL;
	char     *txt_filename            = NULL;
	int       i                       = 0;
	int       j                       = 0;
	int       k                       = 0;
	Missile  *mtmp                    = NULL;
	Object   *otmp                    = NULL;
	Player   *ptmp                    = NULL;
	Config   *stmp                    = cfg;
	size_t    count                   = 0;

	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		fprintf(stderr, "[error] SDL_Init()\n");
		exit(1);
	}

	// OSX crashes here when run on 2nd head
	game -> screen                    = SDL_SetVideoMode(game -> field.width, game -> field.height, game -> field.bpp, SDL_SWSURFACE);

	if (game -> screen               == NULL)
	{
		fprintf(stderr, "[error] SDL_SetVideoMode()\n");
		exit(2);
	}

	if (game -> sfx == ON)
		game -> sfx_thread = SDL_CreateThread(sfxplay, (void *)game);

	txt_wd                            = dirproc("txt");
	fprintf(debug,   "[debug]     Font directory is: '%s'\n", txt_wd);

	count                             = strlen(txt_wd) + strlen("lazy.ttf");
	txt_filename                      = (char *) malloc (sizeof(char) * count);
	if (txt_filename                 == NULL)
	{
		fprintf(stderr, "[error] malloc()\n");
		exit(7);
	}

	sprintf(txt_filename, "%s/lazy.ttf", txt_wd);
	fprintf(verbose, "[verbose]    game font  .. ");

	if (TTF_Init()                   == -1)
	{
		fprintf(stderr, "[error] TTF_Init()\n");
		exit(2);
	}
	else
		game -> font                      = TTF_OpenFont(txt_filename, 64);

	if (game -> font                 == NULL)
	{
		fprintf(stderr, "[error] TTF_OpenFont()\n");
		exit(2);
	}
	fprintf(verbose, "OK\n");
	free(txt_filename);
	txt_filename                      = NULL;

	img_wd                            = dirproc("img");
	fprintf(debug,   "[debug]    Image directory is: '%s'\n", img_wd);

	count                             = strlen(img_wd) + strlen("background.png");
	img_filename                      = (char *) malloc (sizeof(char) * count);
	if (img_filename                 == NULL)
	{
		fprintf(stderr, "[error] malloc()\n");
		exit(7);
	}

	sprintf(img_filename, "%s/background.png", img_wd);
	fprintf(verbose, "[verbose]    background .. ");
	game -> background                = load_image(img_filename);
	if (game -> background           == NULL)
	{
		fprintf(verbose, "FAIL\n");
		exit(8);
	}
	fprintf(verbose, "OK\n");
	free(img_filename);
	img_filename                      = NULL;

//	if (game -> num_paddles           < game -> num_players) //LL
//		game -> num_paddles           = game -> num_players;

	fprintf(verbose, "[verbose]   number of paddles: %d\n", game -> num_paddles);
	fprintf(verbose, "[verbose]   number of players: %d\n", game -> num_players);
	fprintf(verbose, "[verbose] loading game assets:\n");

	for(i = 0; i < game -> num_paddles; i++)
	{
		if (stmp                     == NULL)
		{
			stmp                      = (Config *) malloc (sizeof(Config) * 1);
			stmp -> next              = NULL;
			stmp -> num               = i;
			if ((game -> num_paddles >  game -> num_players) &&
                (i                   >= game -> num_players))
			{
				stmp -> type          = NPC;
				stmp -> device        = NONE;
			}
			else
			{
				stmp -> type          = HUMAN;
				stmp -> device        = KEYBOARD;
			}

			stmp -> location          = LOCAL;
		}

		if (game -> paddle           == NULL)
		{
			ptmp                      = alloc_player(game, stmp, img_wd);
			game -> paddle            = ptmp;
		}
		else
		{
			ptmp -> next              = alloc_player(game, stmp, img_wd);
			ptmp                      = ptmp -> next;
		}	

		stmp                          = stmp -> next;
	}

	stmp                              = cfg;
	while (cfg                       != NULL)
	{
		cfg                           = cfg -> next;
		stmp -> next                  = NULL;
		free(stmp);
		stmp                          = NULL;
		stmp                          = cfg;
	}
		
	for (i = 0; i < game -> num_missiles; i++)
	{
		if (mtmp                     == NULL)
		{
			mtmp                      = alloc_missile(game, i, img_wd);
			game -> ball              = mtmp;
		}
		else
		{
			mtmp -> next              = alloc_missile(game, i, img_wd);
			mtmp                      = mtmp -> next;
		}
	}

	for (i = 0; i < NUM_OBJECTS; i++)
	{
		for (j = 0; j < game -> num[i]; j++)
		{
			if (otmp                 == NULL)
			{
				otmp                  = alloc_object(game, k, img_wd, i);
				game -> item          = otmp;
			}
			else
			{
				otmp -> next          = alloc_object(game, k, img_wd, i);
				otmp                  = otmp -> next;
			}
			k++;
		}
	}

	return (game);
}
