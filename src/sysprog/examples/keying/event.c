#include "sysprog.h"

int main (int argc, char **argv)
{
	SDL_Surface *image   = NULL;
	SDL_Surface *screen  = NULL;

	SDL_Event    event;

	char *filename       = NULL;
	int   x              = 0;
	int   y              = 0;
	int   quit           = FALSE;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		exit (1);

	screen               = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
	if (screen          == NULL)
		exit (2);

	if (argc >= 2)
	{
		x                = atoi (argv[1]);
	}

	if (argc >= 3)
	{
		y                = atoi (argv[2]);
	}

	if (argc >= 4)
	{
		filename         = argv[3];
	}
	else
	{
		filename         = "mudkip.bmp";
	}

	image                = load_image (filename);

	while (quit         == FALSE)
	{
		apply_surface (x, y, image, screen);
		SDL_Flip(screen);

		while (SDL_PollEvent (&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym      == SDLK_ESCAPE)
				{
					quit        = TRUE;
				}
				else if (event.key.keysym.sym == SDLK_UP)
				{
					y           = y - 5;
				}
				else if (event.key.keysym.sym == SDLK_DOWN)
				{
					y           = y + 5;
				}
				else if (event.key.keysym.sym == SDLK_LEFT)
				{
					x           = x - 5;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT)
				{
					x           = x + 5;
				}
			}
			else if (event.type == SDL_QUIT)
			{
				quit        = TRUE;
			}
		}
	}

	SDL_FreeSurface(image);
	SDL_Quit();

	return (0);
}
