#include "sysprog.h"

SDL_Surface *load_image (char *filename)
{
	SDL_Surface *loadedImage  = NULL;
	SDL_Surface *optImage     = NULL;

	loadedImage  = IMG_Load(filename);
	if (loadedImage == NULL)
		exit (3);

	optImage = SDL_DisplayFormat (loadedImage);

	SDL_FreeSurface (loadedImage);

	return (optImage);
}

void apply_surface (int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface (source, NULL, destination, &offset);
}
