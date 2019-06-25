#include <stdlib.h>
#include <SDL/SDL.h>

SDL_Surface *load_image(char *);
void apply_surface (int, int, SDL_Surface *, SDL_Surface *);

int main()
{
	SDL_Surface *image       = NULL;
	SDL_Surface *background  = NULL;
	SDL_Surface *screen      = NULL;

	int WIDTH                = 800;
	int HEIGHT               = 600;
	int DEPTH                = 32;

	if (SDL_Init (SDL_INIT_EVERYTHING) == -1) // turn it on, all of it
	{
		exit (1);
	}

	screen  = SDL_SetVideoMode (WIDTH, HEIGHT, DEPTH, SDL_SWSURFACE);
	if (screen == NULL)
	{
		exit (2);
	}

	SDL_WM_SetCaption ("Sample Text", NULL);

	image   = load_image ("sprite.bmp");
	background  = load_image ("largerfile.bmp");

	apply_surface (0, 0, background, screen);
	apply_surface (200, 100, image, screen);

	if (SDL_Flip (screen) == -1)
		exit (3);

	SDL_Delay (2000);

	SDL_FreeSurface (image);
	SDL_FreeSurface (background);

	SDL_Quit ();

	return (0);
}

SDL_Surface *load_image(char *filename)
{
	SDL_Surface *loadedImage   = NULL;
	SDL_Surface *optimizedImg  = NULL;

	loadedImage = SDL_LoadBMP(filename);

	if (loadedImage != NULL)
	{
		optimizedImg = SDL_DisplayFormat (loadedImage);
		SDL_FreeSurface (loadedImage);
	}

	return (optimizedImg);
}

void apply_surface (int x, int y, SDL_Surface *src, SDL_Surface *dst)
{
	SDL_Rect  offset;

	offset.x  = x;
	offset.y  = y;

	SDL_BlitSurface (src, NULL, dst, &offset);
}
