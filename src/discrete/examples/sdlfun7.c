#include "stuff.h"

int main()
{
	SDL_Surface *img     = NULL; // image (to put on background)
	SDL_Surface *bg      = NULL; // background
	SDL_Surface *screen  = NULL; // screen/window

	SDL_Event    event;

	int width            = 800;  // width (in pixels)
	int height           = 600;  // height
	int bpp              = 32;   // bits per pixel (color depth)

	int quit             = 0;
	int x                = 0;
	int y                = 0;
	int check	     = 0;
	int itery	     = 10;
	int iterx	     = 10;


	if (SDL_Init (SDL_INIT_EVERYTHING) == -1)
	{
		exit (1);
	}

	screen = SDL_SetVideoMode (width, height, bpp, SDL_SWSURFACE);
	if (screen == NULL)
	{
		exit (2);
	}

	SDL_WM_SetCaption ("Moar Images", NULL);

	img  = load_image ("mudkip.png");
	bg   = load_image ("mudkip.bmp");

	// MAIN GAME LOOP
	while (quit == 0)
	{
		apply_surface (0, 0, bg, screen);
		apply_surface (x, y, img, screen);

		if (SDL_Flip (screen) == -1)
			exit (3);
		
		SDL_Delay (1);
		
		x = x + iterx;
		y = y + itery;

		if (y >= height - (img -> h)){
			itery = itery * -1;
		} else if (y <= 0){
			itery = itery * -1;
		}
	
		if (x >= width - (img -> w)){
			iterx = iterx * -1;
		} else if (x <= 0){
			iterx = iterx * -1;
		}


		while (SDL_PollEvent (&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						quit = 1;
						break;	

					case SDLK_UP:
						itery = abs(itery) - 10;
						break;

					case SDLK_DOWN:
						itery = abs(itery) + 10;
						break;
					
					case SDLK_LEFT:
						iterx = abs(iterx) - 10;
						break;

					case SDLK_RIGHT:
						iterx = abs(iterx) + 10;
						break;

					default:
						break;
				}
			}
			else if (event.type == SDL_QUIT)
			{
				quit = 1;
			}
		}
	}

	SDL_FreeSurface (img);
	SDL_FreeSurface (bg);

	SDL_Quit ();

	return (0);
}
