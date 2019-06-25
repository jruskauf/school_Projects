#include "breakout.h"

int main()
{
	SDL_Surface *bg      = NULL; // background
	SDL_Surface *screen  = NULL; // screen/window

	Block       *tmp     = NULL; // pointer to current block

	SDL_Event    event;
	Uint8       *keystates = NULL;

	int JOYSTICK_DEAD_ZONE = 8000;

	SDL_Joystick *js       = NULL;
	short int value   = 0;
	Uint8 button      = 0;
	
	Uint8 mousestat = 0;
	int mx = 0;
	int my = 0;

	int width            = 1024;  // width (in pixels)
	int height           = 640;   // height
	int bpp              = 32;    // bits per pixel (color depth)

	int index            = 0;
	int row              = 0;
	int R                = 0;
	int G                = 0;
	int B                = 64;
	int cleared          = FALSE;

	int quit             = 0;

	srand (time(NULL));

	if (SDL_Init (SDL_INIT_EVERYTHING) == -1)
	{
		exit (1);
	}

	screen = SDL_SetVideoMode (width, height, bpp, SDL_SWSURFACE);
	if (screen == NULL)
	{
		exit (2);
	}

	// Check for joysticks
	if (SDL_NumJoysticks() < 1)
	{
		fprintf (stdout, "WARNING: No joysticks connected\n");
	//	exit (3);
	}
	else
	{
		js = SDL_JoystickOpen(0);
		if (js == NULL)
		{
			fprintf (stderr, "WARNING: Unable to open controller! SDL Error: %s\n", SDL_GetError());
	//		exit (4);
		}
	}

	// initialize paddle resources
	paddle             = (Player *) malloc (sizeof (Player));
	paddle -> next     = NULL;
	paddle -> xvel     = 10;
	paddle -> sprite   = load_image ("images/paddle.png");
	paddle -> pos.x    = (width / 2) - (paddle -> sprite -> w / 2);
	paddle -> pos.y    = height - 20 - (paddle -> sprite -> h);
	paddle -> pos.w    = paddle -> sprite -> w;
	paddle -> pos.h    = paddle -> sprite -> h;

	// initialize ball resources
	ball               = (Missile *) malloc (sizeof (Missile));
	ball -> next       = NULL;
	ball -> xmag       = 10;
	ball -> xdir       = rand() % 2;
	ball -> xdir = (ball -> xdir == 0) ? -1 : 1;
	ball -> ymag       = 10;
	ball -> ydir       = -1;
	ball -> move       = FALSE;
	ball -> sprite     = load_image ("images/ball.png");
	ball -> pos.x      = (width / 2) - (ball -> sprite -> w / 2);
	ball -> pos.y      = paddle -> pos.y - ball -> sprite -> h;
	ball -> pos.w      = ball -> sprite -> w;
	ball -> pos.h      = ball -> sprite -> h;

	// initialize brick resources
	bricks             = (Block *) malloc (sizeof (Block));
	bricks -> next     = NULL;
	bricks -> sprite   = load_image ("images/block.png");
	bricks -> pos.x    = 0;
	bricks -> pos.y    = 0;
	bricks -> pos.w    = bricks -> sprite -> w;
	bricks -> pos.h    = bricks -> sprite -> h;
	bricks -> visible  = TRUE;
	SDL_FillRect (bricks -> sprite, NULL, SDL_MapRGB (bricks -> sprite -> format, R, G, B));
	R                  = (R + 24) % 255;
	G                  = (G + 8)  % 255;
	B                  = (B + 32) % 255;

	tmp                = bricks;
	index              = bricks -> pos.x;
	for (row = 0; row < 8; row++)
	{
		while (index + tmp -> pos.w < width)
		{
			tmp -> next    = (Block *) malloc (sizeof (Block));
			tmp            = tmp -> next;
			tmp -> next    = NULL;
			tmp -> sprite  = load_image ("images/block.png");
			tmp -> pos.x   = index;
//			tmp -> pos.y   = 0;
			tmp -> pos.y   = row * (tmp -> sprite -> h + 1);
			tmp -> pos.w   = tmp -> sprite -> w;
			tmp -> pos.h   = tmp -> sprite -> h;
			tmp -> visible = TRUE;
			SDL_FillRect (tmp -> sprite, NULL, SDL_MapRGB (tmp -> sprite -> format, R, G, B));
			R              = (R + 24) % 255;
			G              = (G + 8)  % 255;
			B              = (B + 32) % 255;

			index = index + tmp -> sprite -> w + 1;
		}
		index              = 0;
	}
	

	SDL_WM_SetCaption ("Breakout 3000XL", NULL);

	bg   = load_image ("images/background.png");

	// MAIN GAME LOOP
	while (quit == 0)
	{
		apply_surface (0, 0, bg, screen);  // place background
		apply_surface (paddle -> pos.x, paddle -> pos.y, paddle -> sprite, screen); // place paddle
		apply_surface (ball -> pos.x, ball -> pos.y, ball -> sprite, screen); // place ball

		tmp = bricks; // point tmp at first brick in brick list
		cleared = TRUE;
		while (tmp != NULL)
		{
			if (tmp -> visible == TRUE)
			{
				apply_surface (tmp -> pos.x, tmp -> pos.y, tmp -> sprite, screen); // place current brick on screen
				cleared = FALSE;
			}
			tmp  = tmp -> next; // advance to next brick
		}

		if (cleared == TRUE)
			quit = 1;

		if (SDL_Flip (screen) == -1)
			exit (3);
		
//		SDL_Delay (1000);

//		x = x + 10;
//		y = y + 5;

		keystates  = SDL_GetKeyState(NULL);
		if ((keystates[SDLK_LEFT]) && (paddle -> pos.x - paddle -> xvel > 0))
			paddle -> pos.x = paddle -> pos.x - paddle -> xvel;
			
		if ((keystates[SDLK_RIGHT]) && (paddle -> pos.x + paddle -> pos.w + paddle -> xvel < width))
			paddle -> pos.x = paddle -> pos.x + paddle -> xvel;

		mousestat = SDL_GetMouseState(&mx, &my);
		paddle -> pos.x = mx;
		if ((mousestat & SDL_BUTTON(1)) == SDL_BUTTON(1))
			paddle -> pos.y = paddle -> pos.y - 5;
		if ((mousestat & SDL_BUTTON(3)) == SDL_BUTTON(3))
			paddle -> pos.y = paddle -> pos.y + 5;

		// https://www.libsdl.org/release/SDL-1.2.15/docs/html/joystick.html
		SDL_JoystickUpdate();
		value = SDL_JoystickGetAxis(js, 0);
		if (value < -JOYSTICK_DEAD_ZONE)
			paddle -> pos.x = paddle -> pos.x - paddle -> xvel;
		else if (value > JOYSTICK_DEAD_ZONE)
			paddle -> pos.x = paddle -> pos.x + paddle -> xvel;

		button = SDL_JoystickGetButton(js, 0);
		if (button == 1) // 1 means pressed, 0 means not pressed
		{
			if (ball -> move == FALSE)
				ball -> move =  TRUE;
		}

		if (keystates[SDLK_SPACE])
		{
			if (ball -> move == FALSE)
				ball -> move = TRUE;
			else
				paddle -> pos.x = ball -> pos.x - (paddle -> pos.w / 2);
		}

		if (ball -> move == TRUE)
		{
			ball -> pos.x = ball -> pos.x + (ball -> xmag * ball -> xdir);
			if (ball -> pos.x < 0)
			{
				ball -> pos.x = 0;
				ball -> xdir  = ball -> xdir * -1;
			}

			if ((ball -> pos.x + ball -> pos.w) >= width)
			{
				ball -> pos.x = width - ball -> pos.w;
				ball -> xdir  = ball -> xdir * -1;
			}

			ball -> pos.y = ball -> pos.y + (ball -> ymag * ball -> ydir);
			if (ball -> pos.y < 0)
			{
				ball -> pos.y = 0;
				ball -> ydir  = ball -> ydir * -1;
			}

			if ((ball -> pos.y + ball -> pos.h) >= height)
			{
//				ball -> move  = FALSE;
				ball -> xmag  = rand() % 10 + 1;
				ball -> xdir       = rand() % 2;
				ball -> xdir = (ball -> xdir == 0) ? -1 : 1;
				ball -> pos.x = (width / 2) - (ball -> sprite -> w / 2);
				ball -> pos.y = height / 2;
//				ball -> pos.y = paddle -> pos.y - ball -> sprite -> h;
//				ball -> ydir  = ball -> ydir * -1;
			}

			// ball and brick collision check
			tmp = bricks;
			while (tmp != NULL)
			{
				if (tmp -> visible == TRUE)
				{
					// if top of ball is above bottom of current brick
					if (ball -> pos.y <= tmp -> pos.y + tmp -> pos.h)
					{
						// left side of ball is less than right side of brick
						if (ball -> pos.x <= (tmp -> pos.x + tmp -> pos.w))
						{
							// left side of ball is greater than leftish side
							if (ball -> pos.x >= (tmp -> pos.x - ball -> pos.w))
							{
								if (ball -> pos.x < tmp -> pos.x + (tmp -> pos.w / 2))
									ball -> xdir = -1;
								else
									ball -> xdir = 1;
								ball -> ydir = ball -> ydir * -1;
								tmp -> visible = FALSE;
							}
						}
					}
				}
				tmp = tmp -> next;
			}

			if (ball -> ydir == 1)
			{
				if (ball -> pos.y + ball -> pos.h >= paddle -> pos.y)
				{
					// left side of ball is less than right side of paddle
					if (ball -> pos.x <= (paddle -> pos.x + paddle -> pos.w))
					{
						if (ball -> pos.x >= (paddle -> pos.x - ball -> pos.w))
						{
							if (ball -> pos.x < paddle -> pos.x + (paddle -> pos.w / 2))
							{
					//			ball -> xmag = (paddle -> pos.x + paddle -> pos.w) / ball -> pos.x;
								ball -> xdir = -1;
							}
							else
							{
								ball -> xdir = 1;
							}
							ball -> ydir = ball -> ydir * -1;
						}
					}
				}
			}
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

					case SDLK_f:
						if (paddle -> xvel < 20)
							paddle -> xvel = paddle -> xvel + 1;
						break;

					case SDLK_s:
						if (paddle -> xvel > 1)
							paddle -> xvel = paddle -> xvel - 1;
						break;

					default:
						break;
				}
			}
		/*	else if (event.type == SDL_MOUSEMOTION)
			{
				paddle -> pos.x = event.motion.x;
			} 
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					paddle -> pos.y = paddle -> pos.y - 5;
				}

				if(event.button.button == SDL_BUTTON_RIGHT)
				{
					paddle -> pos.y = paddle -> pos.y + 5;
				}
			}
			else if (event.type == SDL_QUIT)
			{
				quit = 1;
			}
			
			else if (event.type == SDL_JOYAXISMOTION)
			{
				// motion on controller #0
				if (event.jaxis.which == 0)
				{
					// x axis motion (axis 0 is "x", axis 1 is "y")
					if (event.jaxis.axis == 0)
					{
						// left of dead zone
						if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
						{
							paddle -> pos.x = paddle -> pos.x - paddle -> xvel;
						}
						// right of dead zone
						else if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
						{
							paddle -> pos.x = paddle -> pos.x + paddle -> xvel;
						}
					}
				}
			}*/
		}
	}

	SDL_FreeSurface (paddle -> sprite);
	SDL_FreeSurface (ball -> sprite);
	SDL_FreeSurface (bg);

	SDL_JoystickClose (js);
	js = NULL;

	SDL_Quit ();

	return (0);
}
