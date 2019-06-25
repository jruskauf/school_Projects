#include "pong.h"

SDL_Surface *load_image(char *filename)
{
	SDL_Surface *loaded_img = NULL;
	SDL_Surface *opt_img    = NULL;

	if ((loaded_img = IMG_Load(filename)) != NULL)
	{
		if ((opt_img = SDL_DisplayFormat(loaded_img)) != NULL)
		{
			SDL_SetColorKey(opt_img, SDL_SRCCOLORKEY, SDL_MapRGB(opt_img->format, 0, 0xFF, 0xFF));
		}
		SDL_FreeSurface(loaded_img);
	}
	return(opt_img);
}
