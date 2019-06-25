#include "sysprog.h"
#include <stdio.h>

TTF_Font *font;

int main(int argc, char **argv)
{
	SDL_Surface *screen                 = NULL;
	SDL_Surface *bg                     = NULL;
	SDL_Surface *report_front           = NULL;
    SDL_Surface *report_back            = NULL;
    SDL_Surface *score_text             = NULL;
    SDL_Surface *score_back             = NULL;
	SDL_Surface *hb1		    = NULL;
	SDL_Surface *hb2		    = NULL;
	SDL_Surface *hb3		    = NULL;
	SDL_Surface *hb4		    = NULL;
	SDL_Event    event;

	Uint8       *keystates              = NULL;

	int          x                      = 100;
	int          y                      = 300;
	int          quit                   = FALSE;
	int          width                  = 800;
	int          height                 = 800;
	unsigned int	         score		            = 0;
	int	         upY;
	int	         downY;
	int	         rightX;
	int	         leftX;
    int report_state                    = 0;
    char str[8];

    TTF_Init();
    font = TTF_OpenFont("SteadfastOblique.otf", 35);
    SDL_Color text_Black        = {   0,   0,   0 };
    SDL_Color text_Red          = { 255,   0,   0 };
    SDL_Color text_Green        = {   0, 255,   0 };
    SDL_Color text_Blue         = {   0,   0, 255 };
    SDL_Color text_Light_Blue   = { 100, 100, 255 };

	if (SDL_Init (SDL_INIT_EVERYTHING) != 0)
	{
		exit (1);
	}

	screen       = SDL_SetVideoMode (width, height, 32, SDL_SWSURFACE);
	if (screen  == NULL)
	{
		exit (2);
	}

	keystates    = SDL_GetKeyState (NULL);

	bg          = load_image ("bg.png"); 
	hb1	        = load_image ("red_box.png");
	hb2	        = load_image ("green_box.png");
	hb3	        = load_image ("blue_box.png");
	hb4	        = load_image ("black_box.png");
	
	List *U      = populateList(U, 40, 390,  780, "D_arrow.jpg"); 
    List *D      = populateList(D, 40, 390,    0, "U_arrow.jpg");	
	List *L      = populateList(L, 40, 780,  390, "R_arrow.jpg");
	List *R      = populateList(R, 40,   0,  390, "L_arrow.jpg");

	while (quit == FALSE)
	{

		upY    = U -> start -> Y;
		downY  = D -> start -> Y;
		leftX  = L -> start -> X;
		rightX = R -> start -> X;
        

	    apply_surface (0,   0,   bg,      screen, NULL);
        
        sprintf(str, "%i", score);
        score_back = TTF_RenderText_Solid(font, str, text_Black);
        apply_surface (652, 22, score_back, screen, NULL);
        score_text = TTF_RenderText_Solid(font, str, text_Light_Blue);
        apply_surface (650, 20, score_text, screen, NULL);
        

        if (report_state > 0)
        {
            if(report_state >= 60)
            {
                report_front = TTF_RenderText_Solid(font, "PERFECT!", text_Black);
                apply_surface (22,   22,   report_front,      screen, NULL);   
            
                report_back = TTF_RenderText_Solid(font, "PERFECT!", text_Blue);
                apply_surface (20,   20,   report_back,      screen, NULL); 

            }
            else if(report_state >= 45)
            {
                report_front = TTF_RenderText_Solid(font, "GREAT!", text_Black);
                apply_surface (22,   22,   report_front,      screen, NULL);   
            
                report_back = TTF_RenderText_Solid(font, "GREAT!", text_Blue);
                apply_surface (20,   20,   report_back,      screen, NULL); 

            }
            else if(report_state >= 30)
            {
                report_front = TTF_RenderText_Solid(font, "GOOD!", text_Black);
                apply_surface (22,   22,   report_front,      screen, NULL);   
            
                report_back = TTF_RenderText_Solid(font, "GOOD!", text_Green);
                apply_surface (20,   20,   report_back,      screen, NULL); 

            } 
            else if (report_state >= 15)
            {
                report_front = TTF_RenderText_Solid(font, "POOR!", text_Black);
                apply_surface (22,   22,   report_front,      screen, NULL);   
            
                report_back = TTF_RenderText_Solid(font, "POOR!", text_Red);
                apply_surface (20,   20,   report_back,      screen, NULL); 
            }
            else if(report_state >= 0)
            {
                report_front = TTF_RenderText_Solid(font, "MISS!", text_Black);
                apply_surface (22,   22,   report_front,      screen, NULL);   
            
                report_back = TTF_RenderText_Solid(font, "MISS!", text_Red);
                apply_surface (20,   20,   report_back,      screen, NULL); 
            }
            if(report_state % 15 != 0)
            {
                report_state--; 
            } 
            else
            {
                report_state = 0;
            }

        }
		apply_surface (330,    330,   hb1,     screen, NULL);
		apply_surface (350,    350,   hb2,     screen, NULL);
		apply_surface (370,    370,   hb3,     screen, NULL);
		apply_surface (390,    390,   hb4,     screen, NULL);
		applyList(U, screen);
		applyList(D, screen);
		applyList(L, screen);
		applyList(R, screen);

		SDL_Flip (screen);

		if(upY <= 400)
		{
			popNswap(U, U -> start -> X, 780);
			score = score - 25;
            report_state = 14;
		}

		if(downY >= 380)
		{
			popNswap(D, D -> start -> X,   0);
			score = score - 25;
            report_state = 14;
		}

		if(leftX <= 400)
		{
			popNswap(L, 780, L -> start -> Y);
			score = score - 25;
            report_state = 14;
		}
		
		if(rightX >= 380)
		{
			popNswap(R, 0, R -> start -> Y);
			score = score - 25;
            report_state = 14;
		}

		while (SDL_PollEvent (&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
			if(event.key.keysym.sym == SDLK_LSHIFT)
			{
				while(quit == FALSE){
					if(event.type == SDL_QUIT)
						quit = TRUE;
		upY    = U -> start -> Y;
		downY  = D -> start -> Y;
		leftX  = L -> start -> X;
		rightX = R -> start -> X;
        

	    apply_surface (0,   0,   bg,      screen, NULL);
        
        sprintf(str, "%i", score);
        score_back = TTF_RenderText_Solid(font, str, text_Black);
        apply_surface (652, 22, score_back, screen, NULL);
        score_text = TTF_RenderText_Solid(font, str, text_Light_Blue);
        apply_surface (650, 20, score_text, screen, NULL);
        

        if (report_state > 0)
        {
            if(report_state >= 60)
            {
                report_front = TTF_RenderText_Solid(font, "PERFECT!", text_Black);
                apply_surface (22,   22,   report_front,      screen, NULL);   
            
                report_back = TTF_RenderText_Solid(font, "PERFECT!", text_Blue);
                apply_surface (20,   20,   report_back,      screen, NULL); 

            }
            else if(report_state >= 45)
            {
                report_front = TTF_RenderText_Solid(font, "GREAT!", text_Black);
                apply_surface (22,   22,   report_front,      screen, NULL);   
            
                report_back = TTF_RenderText_Solid(font, "GREAT!", text_Blue);
                apply_surface (20,   20,   report_back,      screen, NULL); 

            }
            else if(report_state >= 30)
            {
                report_front = TTF_RenderText_Solid(font, "GOOD!", text_Black);
                apply_surface (22,   22,   report_front,      screen, NULL);   
            
                report_back = TTF_RenderText_Solid(font, "GOOD!", text_Green);
                apply_surface (20,   20,   report_back,      screen, NULL); 

            } 
            else if (report_state >= 15)
            {
                report_front = TTF_RenderText_Solid(font, "POOR!", text_Black);
                apply_surface (22,   22,   report_front,      screen, NULL);   
            
                report_back = TTF_RenderText_Solid(font, "POOR!", text_Red);
                apply_surface (20,   20,   report_back,      screen, NULL); 
            }
            else if(report_state >= 0)
            {
                report_front = TTF_RenderText_Solid(font, "MISS!", text_Black);
                apply_surface (22,   22,   report_front,      screen, NULL);   
            
                report_back = TTF_RenderText_Solid(font, "MISS!", text_Red);
                apply_surface (20,   20,   report_back,      screen, NULL); 
            }
            if(report_state % 15 != 0)
            {
                report_state--; 
            } 
            else
            {
                report_state = 0;
            }

        }
		apply_surface (330,    330,   hb1,     screen, NULL);
		apply_surface (350,    350,   hb2,     screen, NULL);
		apply_surface (370,    370,   hb3,     screen, NULL);
		apply_surface (390,    390,   hb4,     screen, NULL);
		applyList(U, screen);
		applyList(D, screen);
		applyList(L, screen);
		applyList(R, screen);

		SDL_Flip (screen);
					SDL_PumpEvents();
				}
			}
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = TRUE;
				}
				else if (event.key.keysym.sym == SDLK_DOWN)
				{
					if(upY >= 410 && upY <= 415)
					{
						score = score + 20;
						popNswap(U, U -> start -> X, 780);
                        report_state = 74;
					}
					else if(upY > 415 && upY <= 430)
					{
						score = score + 10;
						popNswap(U, U -> start -> X, 780);
                        report_state = 59;
					}
					else if(upY > 430 && upY <= 450)
					{
						score = score + 5;
						popNswap(U, U -> start -> X, 780);
                        report_state = 44;
					}
					else if(upY > 450 && upY <= 470)
					{
						score = score + 1;
						popNswap(U, U -> start -> X, 780);
                        report_state = 29;
					}
					else
					{
						score = score - 10;
						popNswap(U, U -> start -> X, 780);
                        report_state = 14;
					}
				}
				else if (event.key.keysym.sym == SDLK_UP)
				{
					if(downY <= 370 && downY >= 365)
					{
						score = score + 20;
						popNswap(D, D -> start -> X,   0);
                        report_state = 74;

					}
                    else if (downY < 365 && downY >= 350)
                    {
						score = score + 10;
						popNswap(D, D -> start -> X,   0);
                        report_state = 59;

                    }
                    else if (downY < 350 && downY >= 330)
                    {
						score = score + 5;
						popNswap(D, D -> start -> X,   0);
                        report_state = 44;

                    }
                    else if (downY < 330 && downY >= 310)
                    {
						score = score + 1;
						popNswap(D, D -> start -> X,   0);
                        			report_state = 29;
                    }
					else
					{
						score = score - 10;
						popNswap(D, D -> start -> X,   0);
                        			report_state = 14;

					}
				}
				else if (event.key.keysym.sym == SDLK_RIGHT)
				{
					if(leftX <= 470 && leftX > 450)
					{
						score = score + 1;
						popNswap(L, 780, L -> start -> Y);
                        			report_state = 29;
					}
                    else if(leftX <= 450 && leftX > 430)
                    {
 						score = score + 5;
						popNswap(L, 780, L -> start -> Y);
                        			report_state = 44;
                    }
                    else if (leftX <= 430 && leftX > 415)
                    {
 						score = score + 10;
						popNswap(L, 780, L -> start -> Y);
                        			report_state = 59;
                    } 
                    else if (leftX <= 415 && leftX > 410)
                    {
 						score = score + 20;
						popNswap(L, 780, L -> start -> Y);
                        			report_state = 74;                
                    }
					else
					{
						score = score - 10;
						popNswap(L, 780, L -> start -> Y);
                        			report_state = 14;
					}
				}
				else if (event.key.keysym.sym == SDLK_LEFT)
				{
					if(rightX <= 370 && rightX > 365)
					{
						score = score + 20;
						popNswap(R,   0, R -> start -> Y);
                        			report_state = 74;
					}
                    else if (rightX <= 365 && rightX > 350)
                    {
						score = score + 10;
						popNswap(R,   0, R -> start -> Y);
                       				report_state = 59;
                    }
                    else if (rightX <= 350 && rightX > 330)
                    {
						score = score + 5;
						popNswap(R,   0, R -> start -> Y);
                        			report_state = 44;
                    }
                    else if (rightX <= 330 && rightX > 310)
                    {
						score = score + 1;
						popNswap(R,   0, R -> start -> Y);
                        report_state = 29;
                    }
					else
					{
						score = score - 10;
						popNswap(R,   0, R -> start -> Y);
                        			report_state = 14;
					}
				}


			}
			else if (event.type == SDL_QUIT)
			{
				quit = TRUE;
			}
        }

		moveUp    (U, 4);
		moveDown  (D, 4);
		moveLeft  (L, 4);
		moveRight (R, 4);

		SDL_PumpEvents();
	}

	SDL_FreeSurface (bg);
	SDL_Quit();

	return (0);
}
