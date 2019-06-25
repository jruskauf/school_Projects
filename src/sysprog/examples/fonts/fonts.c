#include "sysprog.h"
#include <stdio.h>

#define DOWN   0
#define LEFT   1
#define RIGHT  2
#define UP     3

int main (int argc, char **argv)
{
	SDL_Surface *image   = NULL;
	SDL_Surface *sprite  = NULL;
	SDL_Surface *upmsg   = NULL;
	SDL_Surface *dnmsg   = NULL;
	SDL_Surface *ltmsg   = NULL;
	SDL_Surface *rtmsg   = NULL;
	SDL_Surface *screen  = NULL;

	SDL_Rect     clip;

	SDL_Event    event;

	TTF_Font    *font    = NULL;

	SDL_Color    textColor = { 255, 255, 255 };

	char *filename       = NULL;
	int   x              = 0;
	int   y              = 0;
	int   frame          = -1;
	int   quit           = FALSE;
	int   upc            = 0;
	int   dnc            = 0;
	int   ltc            = 0;
	int   rtc            = 0;

	clip.x               = 128;
	clip.y               = 128;
	clip.w               = 32;
	clip.h               = 32;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		exit (1);

	screen               = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
	if (screen          == NULL)
		exit (2);

	if (TTF_Init() == -1)
	{
		exit (2);
	}

	font = TTF_OpenFont("lazy.ttf", 28);
	if (font == NULL)
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
	sprite               = load_image ("CatSprites.png");

	while (quit         == FALSE)
	{
		apply_surface (0, 0, image,  screen, NULL);
		
		apply_surface (x, y, sprite, screen, &clip);
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
					frame       = (frame + 1) % 3;
					clip.x      = frame * 32;
					clip.y      = UP * 32;
					upc         = upc + 1;
				}
				else if (event.key.keysym.sym == SDLK_DOWN)
				{
					y           = y + 5;
					frame       = (frame + 1) % 3;
					clip.x      = frame * 32;
					clip.y      = DOWN * 32;
					dnc         = dnc + 1;
				}
				else if (event.key.keysym.sym == SDLK_LEFT)
				{
					x           = x - 5;
					frame       = (frame + 1) % 3;
					clip.x      = frame * 32;
					clip.y      = LEFT * 32;
					ltc         = ltc + 1;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT)
				{
					x           = x + 5;
					frame       = (frame + 1) % 3;
					clip.x      = frame * 32;
					clip.y      = RIGHT * 32;
					rtc         = rtc + 1;
				}
			}
			else if (event.type == SDL_QUIT)
			{
				quit        = TRUE;
			}
		}
	}

	SDL_FreeSurface(image);
	SDL_FreeSurface(sprite);
	SDL_FreeSurface(upmsg);
	SDL_FreeSurface(dnmsg);
	SDL_FreeSurface(ltmsg);
	SDL_FreeSurface(rtmsg);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();

	return (0);
}
