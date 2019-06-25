#include "breakout.h"

SDL_Surface *load_image(char *filename)
{
	SDL_Surface *loadedImg  = NULL;
	SDL_Surface *optImg     = NULL;

	loadedImg      = IMG_Load (filename);
	if (loadedImg != NULL)
	{
		optImg     = SDL_DisplayFormat (loadedImg);
		SDL_FreeSurface (loadedImg);
	}

	if (optImg    != NULL)
	{
		Uint32 colorkey  = SDL_MapRGB (optImg -> format, 0x00, 0xFF, 0xFF);
		SDL_SetColorKey (optImg, SDL_SRCCOLORKEY, colorkey);
	}

	return (optImg);
}

void apply_surface (int x, int y, SDL_Surface *src, SDL_Surface *dst)
{
	SDL_Rect  offset;

	offset.x  = x;
	offset.y  = y;

	SDL_BlitSurface (src, NULL, dst, &offset);
}
