#include <stdlib.h>
#include <SDL/SDL.h>

int main()
{
	SDL_Surface *image   = NULL;
	SDL_Surface *screen  = NULL;

	SDL_Init (SDL_INIT_EVERYTHING); // turn it on, all of it

	screen  = SDL_SetVideoMode (800, 600, 32, SDL_SWSURFACE);

	image   = SDL_LoadBMP ("mudkip.bmp");

	SDL_BlitSurface (image, NULL, screen, NULL);

	SDL_Flip (screen);

	SDL_Delay (2000);

	SDL_FreeSurface (image);

	SDL_Quit ();

	return (0);
}
