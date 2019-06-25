#include <stdio.h>
#include <stdlib.h>
#include "pong.h"
#include <SDL/SDL_mixer.h>

Pong *collision(Pong *game)
{
	Missile *mtmp = NULL;
	Object  *otmp = NULL;
	Player  *ptmp = NULL;
	static Player  *ballown = NULL;
	
	ptmp = game -> paddle;
	while (ptmp != NULL)
	{
		if (ptmp -> pos.y + ptmp -> high > game -> field.height)
			ptmp -> pos.y = game -> field.height - ptmp -> high;
		else if (ptmp -> pos.y < 0)
			ptmp -> pos.y = 0;

		mtmp = game -> ball;
		while (mtmp != NULL)
		{
			if (ptmp -> ORIENTATION == LEFT)
			{
				// Missile impacting right edge of player
				if ((mtmp -> pos.x <= (ptmp -> pos.x + ptmp -> wide)) &&
				    (mtmp -> pos.x >= (ptmp -> pos.x)))
				{
					// For the entire height of the player
					if ((mtmp -> pos.y <= (ptmp -> pos.y + ptmp -> high)) &&
					    (mtmp -> pos.y >= (ptmp -> pos.y - mtmp -> high)))
					{
						mtmp -> xmove *= -1;
						mtmp -> pos.x += mtmp -> xmove;
						sfx            = ball[0];
						readysfx       = 1;
						ballown 	   = ptmp; //SCORE ADDITION
						ballown -> Phit = 1;
						mtmp -> Bhit   = 1;
					}
				}
			}
			// Missile impacting left edge of player
			else if (ptmp -> ORIENTATION == RIGHT)
			{
				if (((mtmp -> pos.x + mtmp -> wide) >=  ptmp -> pos.x) &&
			         ((mtmp -> pos.x + mtmp -> wide) <= (ptmp -> pos.x + ptmp -> wide)))
				{
				// For the entire height of the player
					if ((mtmp -> pos.y <= (ptmp -> pos.y + ptmp -> high)) &&
					    (mtmp -> pos.y >= (ptmp -> pos.y - mtmp -> high)))
					{
						mtmp -> xmove *= -1;
						mtmp -> pos.x += mtmp -> xmove;
						sfx            = ball[0];
						readysfx       = 1;
						ballown 	   = ptmp; //SCORE ADDITION
						ballown -> Phit = 1;
						mtmp -> Bhit   = 1;
					}
				}
			}
			// Missile impacting top edge of player
			else if (ptmp -> ORIENTATION == TOP)
			{
				if (((mtmp -> pos.y + mtmp -> high) >= ptmp -> pos.y) &&
					  (mtmp -> pos.y                 <= ptmp -> pos.y + ptmp -> high))
				{
					// For the entire width of the player
					if ((mtmp -> pos.x + mtmp -> wide >=  ptmp -> pos.x) &&
						(mtmp -> pos.x <= (ptmp -> pos.x + ptmp -> wide)))
					{
						mtmp -> ymove *= -1;
						mtmp -> pos.y += mtmp -> ymove;
						sfx            = ball[0];
						readysfx       = 1;
						ballown 	   = ptmp; //SCORE ADDITION
						ballown -> Phit = 1;
						mtmp -> Bhit   = 1;
					}
				}
			}
			// Missile impacting bottom edge of player
			else if (ptmp -> ORIENTATION == BOTTOM)
			{
				if ((mtmp -> pos.y                <= (ptmp -> pos.y + ptmp -> high)) &&
						 (mtmp -> pos.y + mtmp -> high >= ptmp -> pos.y))
				{
					// For the entire width of the player
					if ((mtmp -> pos.x >=  ptmp -> pos.x) &&
						(mtmp -> pos.x <= (ptmp -> pos.x + ptmp -> wide)))
					{
						mtmp -> ymove *= -1;
						mtmp -> pos.y += mtmp -> ymove;
						sfx            = ball[0];
						readysfx       = 1;
						ballown 	   = ptmp; //SCORE ADDITION
						ballown -> Phit = 1;
						mtmp -> Bhit   = 1;
					}
				}
			}

//Left Side Hit Deflection / Scoring
			if (mtmp -> pos.x < 0)
			{
				if ((game->wallflower & LEFT) != 0)
				{
					mtmp -> pos.x    = game -> field.width  / 2 - mtmp -> wide;
					mtmp -> pos.y    = game -> field.height / 2 - mtmp -> high;
					mtmp -> xmove    = -1 * (mtmp -> xmove);
					mtmp -> ymove    = -1 * (mtmp -> ymove);
					sfx              = ball[1];
					readysfx         = 1;
					if ((ballown != NULL) && (ballown -> ORIENTATION != LEFT))
					{
						ballown -> score++; //SCORE ADDITION
					}
					ballown = NULL;
					game -> newserve = 1;
				}
				else
				{
					mtmp -> xmove = -1 * (mtmp->xmove);
				}
			}
//Right Side Hit Deflection / Scoring
            else if (mtmp -> pos.x > game -> field.width - mtmp -> wide)
			{
            	if ((game->wallflower & RIGHT) != 0)
                {
                    mtmp -> pos.x    = game -> field.width  / 2 - mtmp -> wide;
                    mtmp -> pos.y    = game -> field.height / 2 - mtmp -> high;
                    mtmp -> xmove    = -1 * (mtmp -> xmove);
                    mtmp -> ymove    = -1 * (mtmp -> ymove);
                    sfx              = ball[1];
                    readysfx         = 1;
					if ((ballown != NULL) && (ballown -> ORIENTATION != RIGHT))
                    {
                        ballown -> score++; //SCORE ADDITION
                    }
					ballown = NULL;
                    game -> newserve = 1;
                }
                else
            	{
               		mtmp -> xmove = -1 * (mtmp->xmove);
            	}
			}
//Top Side Hit Deflection / Scoring
			else if (mtmp -> pos.y < 0)
			{	
				if ((game->wallflower & TOP) != 0)
				{
        	   	    mtmp -> pos.x    = game -> field.width  / 2 - mtmp -> wide;
        	       	mtmp -> pos.y    = game -> field.height / 2 - mtmp -> high;
        	   		mtmp -> xmove    = -1 * (mtmp -> xmove);
        	   		mtmp -> ymove    = -1 * (mtmp -> ymove);
					sfx              = ball[1];
        		    readysfx         = 1;
					if ((ballown != NULL) && (ballown -> ORIENTATION != TOP))
        	   	    {   
        	       		ballown -> score++; //SCORE ADDITION
        	   		}   
					ballown = NULL;
           			game -> newserve = 1;
          	 	}   
				else 
				{	
					mtmp -> ymove = -1 * (mtmp->ymove);
				}
			}
//Bottom Side Hit Deflection / Scoring
			else if	(mtmp -> pos.y > game-> field.height - mtmp -> high)
			{
				if ((game->wallflower & BOTTOM) != 0)
				{
                    mtmp -> pos.x    = game -> field.width  / 2 - mtmp -> wide;
                    mtmp -> pos.y    = game -> field.height / 2 - mtmp -> high;
                    mtmp -> xmove    = -1 * (mtmp -> xmove);
                    mtmp -> ymove    = -1 * (mtmp -> ymove);
					sfx              = ball[1];
                    readysfx         = 1;
					if ((ballown != NULL) && (ballown -> ORIENTATION != BOTTOM))
                    {   
                        ballown -> score++; //SCORE ADDITION
                    }   
					ballown = NULL;
                    game -> newserve = 1;
				}  
           		else
     	   	 	{   
    	       		mtmp -> ymove = -1 * (mtmp->ymove);
            	}	  
			}



/*
			if (4 - game -> num_players == 2)
			{
				if (mtmp -> pos.y < (game -> wall[0].y + game -> wall[0].h))
					mtmp -> ymove = -1 * (mtmp -> ymove);
				else if (mtmp -> pos.y + mtmp -> high > game -> wall[1].y)
					mtmp -> ymove = -1 * (mtmp -> ymove);
			}
			else if (4 - game -> num_players == 3)
			{
				//
			}

			if ((mtmp -> pos.y < 0) ||
				(mtmp -> pos.y > game -> field.height - mtmp -> high))
			{
				mtmp -> ymove = -1 * (mtmp -> ymove);
			}
*/				
/*			otmp = game -> item;
			while (otmp != NULL)
			{
				if ((mtmp -> pos.x <= (otmp -> pos.x + otmp -> wide)) &&
					(mtmp -> pos.x >= (otmp -> pos.x)))
				{
					// For the entire height of the player
					if ((mtmp -> pos.y <= (otmp -> pos.y + otmp -> high)) &&
						(mtmp -> pos.y >= (otmp -> pos.y - mtmp -> high)))
					{
						mtmp -> xmove *= -1;
						mtmp -> pos.x += mtmp -> xmove;
					}
				}
				else if (((mtmp -> pos.x + mtmp -> wide) >=  otmp -> pos.x) &&
						 ((mtmp -> pos.x+mtmp -> wide) <= (otmp -> pos.x+otmp->wide)))
				{
					if ((mtmp -> pos.y <= (otmp -> pos.y + otmp -> high)) &&
						(mtmp -> pos.y >= (otmp -> pos.y - mtmp -> high)))
					{
						mtmp -> xmove *= -1;
						mtmp -> pos.x += mtmp -> xmove;
					}
				}
				else if ((mtmp -> pos.y + mtmp -> high >= otmp -> pos.y) &&
					     (mtmp -> pos.y                <= ptmp -> pos.y+ptmp->high))
				{
					if ((mtmp -> pos.x <= (otmp -> pos.x + otmp -> wide)) &&
						(mtmp -> pos.x >=  otmp -> pos.x))
					{
						mtmp -> ymove *= -1;
						mtmp -> pos.y += mtmp -> ymove;
					}
				}
				else if ((mtmp -> pos.y                <= otmp -> pos.y+otmp->high) &&
			     		 (mtmp -> pos.y + mtmp -> high >= otmp -> pos.y))
				{
					if ((mtmp -> pos.x <= (otmp -> pos.x + otmp -> wide)) &&
						(mtmp -> pos.x >=  otmp -> pos.x))
					{
						mtmp -> ymove *= -1;
						mtmp -> pos.y += mtmp -> ymove;
					}
				}
				otmp = otmp -> next;
			}
*/
			mtmp -> pos.x += mtmp -> xmove;
			mtmp -> pos.y += mtmp -> ymove;
			mtmp = mtmp -> next;
		}

		ptmp = ptmp -> next;
	}

	return(game);
}
