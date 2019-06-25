#include "pong.h"

void title(Pong *game)
{
	char        *img_filename         = NULL;
	char        *img_filename_short   = NULL;
	char        *img_wd               = NULL;
	int          alpha                = 0;
	int          i                    = 0;
	size_t       count                = 0;
	SDL_Rect     offset;
	SDL_Surface *logo[NUM_LOGOS];

	img_wd                            = dirproc("img");

	for (i = 0; i < NUM_LOGOS; i++)
	{
		count                         = strlen("logoX.png");
		img_filename_short            = (char *) malloc (sizeof(char) * count);
		sprintf(img_filename_short, "logo%d.png", i);

		count                         = strlen(img_wd)+strlen(img_filename_short);
		img_filename                  = (char *) malloc (sizeof(char) * count);
		sprintf(img_filename, "%s/%s", img_wd, img_filename_short);
		fprintf(verbose, "[verbose]    logo %d    ... ", i);
		logo[i]                       = load_image(img_filename);
		if (logo[i] == NULL)
		{
			fprintf(verbose, "FAIL\n");
			exit(9);
		}
		fprintf(verbose, "OK\n");
		free(img_filename);
		img_filename                  = NULL;

		alpha                         = SDL_ALPHA_OPAQUE;
		offset.x                      = game -> field.width /2 - logo[i] -> w/2;
		offset.y                      = game -> field.height/2 - logo[i] -> h/2;

		SDL_SetAlpha(logo[i], SDL_SRCALPHA, alpha);
		SDL_BlitSurface(game -> background, NULL, game -> screen, &(game -> offset));
		SDL_BlitSurface(logo[i], NULL, game -> screen, &offset);
		SDL_Flip(game -> screen);

		SDL_Delay(4000);

		while (alpha > 0)
		{

			SDL_Flip(game -> screen);
			SDL_Delay(20);
			alpha = alpha - 10;

			SDL_SetAlpha(logo[i], SDL_SRCALPHA, alpha);
			SDL_BlitSurface(game->background,NULL,game->screen,&(game->offset));
			SDL_BlitSurface(logo[i], NULL, game -> screen, &offset);
		}
	}
}
