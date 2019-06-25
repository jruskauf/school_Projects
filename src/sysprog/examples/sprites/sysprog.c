#include "sysprog.h"

SDL_Surface *load_image (char *filename)
{
	SDL_Surface *loadedImage  = NULL;
	SDL_Surface *optImage     = NULL;

	Uint32       colorkey     = 0;

	loadedImage  = IMG_Load(filename);
	if (loadedImage == NULL)
		exit (3);

	optImage = SDL_DisplayFormat (loadedImage);

	SDL_FreeSurface (loadedImage);

	if (optImage != NULL)
	{
		colorkey  = SDL_MapRGB (optImage -> format, 120, 195, 128);
		SDL_SetColorKey (optImage, SDL_SRCCOLORKEY, colorkey);
	}

	return (optImage);
}

void apply_surface (int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface (source, clip, destination, &offset);
}
