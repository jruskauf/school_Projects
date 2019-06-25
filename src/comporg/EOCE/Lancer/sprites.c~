#define TV_NTSC 1
#include "nes.h"
#include "reset.h"
#include "data.h"
#include <stddef.h>
#include <stdint.h>
#include <6502.h>

#define BLANK_TILE    0x00
#define BORDER_TL     0x04
#define BORDER_TR     0x05
#define BORDER_BL     0x14
#define BORDER_BR     0x15
#define BORDER_T      0x07
#define BORDER_B      0x17
#define BORDER_L      0x06
#define BORDER_R      0x16
#define SPRITE_DOWN   0x10
#define SPRITE_RIGHT  0x11
#define SPRITE_LEFT   0x12
#define SPRITE_UP     0x13

#define WALK          1
#define SPRINT        3

#pragma bss-name(push, "ZEROPAGE")
uint8_t    i;
uint8_t    j;

//Variables for end-game state, determines whether to show player 1 win or
//player 2 win.
uint8_t    STATE;

//Starting positions for Player 1 & 2
uint8_t    START1_X;
uint8_t    START1_Y;
uint8_t    START2_X;
uint8_t    START2_Y;    

//Speed and score variables for player 1 & 2
uint8_t    SPEED;
uint8_t    SPEED2;
uint8_t    SCORE1;
uint8_t    SCORE2;

//Border hit detection variables
uint8_t    B_TOP;
uint8_t    B_BOT;
uint8_t    B_RGT;
uint8_t    B_LFT;

//Player 1 hit detection variables
uint8_t    P1_TOP;
uint8_t    P1_BOT;
uint8_t    P1_RGT;
uint8_t    P1_LFT;

//Player 2 hit detection variables
uint8_t    P2_TOP;
uint8_t    P2_BOT;
uint8_t    P2_RGT;
uint8_t    P2_LFT;

//Testing sprite for drawing background
uint8_t    tmp_sprite;

uintptr_t  ppu_addr;
uint8_t    const * ppu_data;
uint8_t    ppu_data_size;
#pragma bss-name(pop)

//Sprite variable setup
#pragma bss-name(push, "OAM")
sprite_t player1;
sprite_t player2;
sprite_t score1;
sprite_t score2;

#pragma bss-name(pop)

//Resets the needed scroll memory to prevent overflow of bits
void ResetScroll()
{
    PPU_SCROLL = 0x00;
    PPU_SCROLL = 0x00;
}

//Enabling PPU so we can then write to it
void EnablePPU()
{
    PPU_CTRL = PPUCTRL_NAMETABLE_0 | PPUCTRL_BPATTERN_0 | PPUCTRL_NMI_ON;
    PPU_MASK = PPUMASK_COLOR       | PPUMASK_BSHOW      | PPUMASK_L8_BSHOW |
	       PPUMASK_SSHOW       | PPUMASK_L8_SSHOW;;
}

//Writing the background data to the PPU
void WritePPU()
{
    PPU_ADDRESS = (uint8_t)(ppu_addr >> 8);
    PPU_ADDRESS = (uint8_t)(ppu_addr);
    for (i = 0; i < ppu_data_size; ++i) 
    {
	PPU_DATA = ppu_data[i];
    }
}


//Drawing the game screen, or "arena".  This is done by calling a sprite tiles
//sequentially.  When a row of background sprites is filled, they automatically
//go down to the next line, so we can use loops to help "fill" the background
//with the tiles we want.  I also drew the LANCER logo in the background, as 
//one of the limitations of the NES is that you can't have more than 8 sprites
//on a single row.
void DrawArena()
{
    PPU_DATA = BORDER_TL;

    for(i = 0; i < (NUM_COLS - 2); ++i)
    {
        PPU_DATA = BORDER_T;
    }	
    PPU_DATA = BORDER_TR;
    
        
    PPU_DATA = BORDER_L;
    for (j = 0; j < ((NUM_COLS / 2) - 7); j++)
    {
        PPU_DATA = BLANK_TILE;
    }

    tmp_sprite = 0xA0;
    for (j = 0; j < (12); j++)
    {
        PPU_DATA = tmp_sprite;
        tmp_sprite++;
    }

    for (j = 0; j < ((NUM_COLS / 2) - 7); j++)
    {
	PPU_DATA = BLANK_TILE;
    }
    PPU_DATA = BORDER_R;
    

    PPU_DATA = BORDER_L;
    for (j = 0; j < ((NUM_COLS / 2) - 7); j++)
    {
        PPU_DATA = BLANK_TILE;
    }

    tmp_sprite = 0xB0;
    for (j = 0; j < (12); j++)
    {
        PPU_DATA = tmp_sprite;
        tmp_sprite++;
    }

    for (j = 0; j < ((NUM_COLS / 2) - 7); j++)
    {
	    PPU_DATA = BLANK_TILE;
    }
    PPU_DATA = BORDER_R;

    for (i = 0; i < (NUM_ROWS - 4); ++i)
    {
	    PPU_DATA = BORDER_L;
	    for (j = 0; j < (NUM_COLS - 2); ++j)
	    {
	        PPU_DATA = BLANK_TILE;
	    }
	    PPU_DATA = BORDER_R;
    }


    PPU_DATA = BORDER_BL;
    for(i = 0; i < (NUM_COLS - 2); ++i)
    {
        PPU_DATA = BORDER_B;
    }
    PPU_DATA = BORDER_BR;
}

//This is an unused Title screen, as i have had trouble redrawing the game
//screen, even with the use of the PPU_MASK and PPU_CTRL.  I don't get any
//graphical bugs when i redraw the background, however, i haven't been able
//to find a way to "draw over" the first screen.  So with the large 
//"PRESS START" being in the middle of the screen for the whole game, it was
//a big eyesore.  I'm leaving this in here in case i come back to this in 
//the future, or if someone wishes to look at the "title" screen.

void DrawTitle()
{
    PPU_DATA = BORDER_TL;

    for(i = 0; i < (NUM_COLS - 2); ++i)
    {
        PPU_DATA = BORDER_T;
    }	
    PPU_DATA = BORDER_TR;
    
        
    PPU_DATA = BORDER_L;
    for (j = 0; j < ((NUM_COLS / 2) - 7); j++)
    {
        PPU_DATA = BLANK_TILE;
    }

    tmp_sprite = 0xA0;
    for (j = 0; j < (12); j++)
    {
        PPU_DATA = tmp_sprite;
        tmp_sprite++;
    }

    for (j = 0; j < ((NUM_COLS / 2) - 7); j++)
    {
	PPU_DATA = BLANK_TILE;
    }
    PPU_DATA = BORDER_R;
    

    PPU_DATA = BORDER_L;
    for (j = 0; j < ((NUM_COLS / 2) - 7); j++)
    {
        PPU_DATA = BLANK_TILE;
    }

    tmp_sprite = 0xB0;
    for (j = 0; j < (12); j++)
    {
        PPU_DATA = tmp_sprite;
        tmp_sprite++;
    }

    for (j = 0; j < ((NUM_COLS / 2) - 7); j++)
    {
	    PPU_DATA = BLANK_TILE;
    }
    PPU_DATA = BORDER_R;

    for (i = 0; i < ((NUM_ROWS/2) - 4); ++i)
    {
	    PPU_DATA = BORDER_L;
	    for (j = 0; j < (NUM_COLS - 2); ++j)
	    {
	        PPU_DATA = BLANK_TILE;
	    }
	    PPU_DATA = BORDER_R;
    }
    
    PPU_DATA = BORDER_L;
    for ( j = 0; j < (NUM_COLS / 2) - 7; ++j)
    {
        PPU_DATA = BLANK_TILE;
    }
    
    PPU_DATA = 0x70;
    PPU_DATA = 0x72;
    PPU_DATA = 0x65;
    PPU_DATA = 0x73;
    PPU_DATA = 0x73;
    PPU_DATA = BLANK_TILE;
    PPU_DATA = BLANK_TILE;
    PPU_DATA = 0x73;
    PPU_DATA = 0x74;
    PPU_DATA = 0x61;
    PPU_DATA = 0x72;
    PPU_DATA = 0x74; 
	
    for ( j = 0; j < (NUM_COLS / 2) - 7; ++j)
    {
        PPU_DATA = BLANK_TILE;
    }
    PPU_DATA = BORDER_R;

    for (i = 0; i < ((NUM_ROWS/2) - 1); ++i)
    {
	    PPU_DATA = BORDER_L;
	    for (j = 0; j < (NUM_COLS - 2); ++j)
	    {
	        PPU_DATA = BLANK_TILE;
	    }
	    PPU_DATA = BORDER_R;
    }


    PPU_DATA = BORDER_BL;
    for(i = 0; i < (NUM_COLS - 2); ++i)
    {
        PPU_DATA = BORDER_B;
    }
    PPU_DATA = BORDER_BR;
}

//This sets up the starting conditions of the 2 sprites in the title screen,
//as i plan on making a single player mode for this in addition to the current
//2 player mode.  The sprites are currently set for the "top" option, but in
//game there is only blank space between them.  However, if you swap out the
//DrawArena() for DrawTitle(), you will see the "PRESS START" fits in between
//the arrows. 
void Title_Setup()
{
    START1_X = (MAX_X / 2) - (SPRITE_WIDTH  / 2) - 60;
    START1_Y = (MAX_Y / 2) - (SPRITE_HEIGHT / 2);

    START2_X = (MAX_X / 2) - (SPRITE_WIDTH  / 2) + 60;
    START2_Y = (MAX_Y / 2) - (SPRITE_HEIGHT / 2);

    SCORE1 = 0;

    WritePPU();

    player1.x           = START1_X; 
    player1.y           = START1_Y;
    player1.tile_index  = SPRITE_RIGHT;
    player1.attributes  = player1.attributes & 0x00;

    player2.x           = START2_X;
    player2.y           = START2_Y;
    player2.tile_index  = SPRITE_LEFT;
    player2.attributes  = player2.attributes & 0x00;
    player2.attributes  = player2.attributes | 0x01;

    ResetScroll();
    EnablePPU();
}

//This is the input loop for the title screen, allowing you to currently start
//the game from either controller.
void Title_Loop()
{
    while(SCORE1 == 0)
    {
        WaitFrame();
	    ResetScroll();

	    if(InputPort1 & BUTTON_START)
	    {
	        SCORE1++;
	    }

	    if(InputPort2 & BUTTON_START)
	    {
	        SCORE1++;
	    }
    }
}

//This sets up the main game initial state, which includes the sprites for the
//arrows as well as the score
void Game_Setup()
{
    B_TOP = MIN_Y + SPRITE_HEIGHT;
    B_BOT = MAX_Y - (SPRITE_HEIGHT + SPRITE_HEIGHT);
    B_RGT = MAX_X - (SPRITE_WIDTH + SPRITE_WIDTH);
    B_LFT = MIN_X + SPRITE_WIDTH;

    START1_X = (MAX_X / 2) - (SPRITE_WIDTH  / 2) - 50;
    START1_Y = (MAX_Y / 2) - (SPRITE_HEIGHT / 2);

    START2_X = (MAX_X / 2) - (SPRITE_WIDTH  / 2) + 50;
    START2_Y = (MAX_Y / 2) - (SPRITE_HEIGHT / 2);
    
    SPEED =  SPRINT;
    SPEED2 = SPRINT;

    SCORE1 = 0;
    SCORE2 = 0;

    //WritePPU();
    
    player1.x           = START1_X; 
    player1.y           = START1_Y;
    player1.tile_index  = SPRITE_RIGHT;
    player1.attributes  = player1.attributes & 0x00;

    player2.x           = START2_X;
    player2.y           = START2_Y;
    player2.tile_index  = SPRITE_LEFT;
    player2.attributes  = player2.attributes & 0x00;
    player2.attributes  = player2.attributes | 0x01;

    score1.x = MIN_X + SPRITE_WIDTH;
    score1.y = MIN_Y + SPRITE_HEIGHT;
    score1.tile_index   = 0x55;
    score1.attributes   = player1.attributes;


    score2.x = MAX_X - SPRITE_WIDTH - SPRITE_WIDTH;
    score2.y = MIN_Y + SPRITE_HEIGHT;
    score2.tile_index   = 0x55;
    score2.attributes   = score2.attributes;

    ResetScroll();
    EnablePPU();
}

//this is the main game loop.  We have variables at the top, which are the main
//variables for hit detection.  These have to be "refreshed" every iteration of
//the loop, as we cannot have the math they stand in for inside the if 
//statements due to constraints with the CC65 compiler suite.  Assembly code
//does not like math in some instances.
//
//Hit detection is done by checking above, below, and to the sides of each 
//sprite.  The values change depending on what direction you are travelling,
//however the idea remains the same.  The only way to win is to hit
//the sides or back of the sprite, so we only check to see if the sprite is
//NOT the direct opposite on the tile-sheet.
//
//The end-game state happens when the lives of the other player reach 0.
//When the lives of the other players reaches 0, we set the score to either
//W or L depending on what player won or lost.  When that happens, the sprites
//reset to their starting positions, and the game is "paused" through use of a 
//smaller loop.  Whenever a player presses the start button, the game restarts
//and you're allowed to play again.
void Game_Loop()
{
    while (SCORE1 < 5 && SCORE2 < 5)
    {
        P1_TOP = player1.y + SPRITE_HEIGHT;
        P1_BOT = player1.y - SPRITE_HEIGHT;
        P1_RGT = player1.x + SPRITE_HEIGHT;
        P1_LFT = player1.x - SPRITE_HEIGHT;

        P2_TOP = player2.y + SPRITE_HEIGHT;
        P2_BOT = player2.y - SPRITE_HEIGHT;
        P2_RGT = player2.x + SPRITE_HEIGHT;
        P2_LFT = player2.x - SPRITE_HEIGHT;

    	if (InputPort1 & BUTTON_UP)
    	{
    	    player1.tile_index  = SPRITE_UP;
      	    if (player1.y > B_TOP)
    	    {
     	        if (player1.y >= player2.y)
        		{
                    if( P1_RGT >= player2.x &&
                        P1_LFT <= player2.x)
                    {
    		            if(P1_BOT <= player2.y)
                        {
                            if(player2.tile_index != SPRITE_DOWN)
			                {
                                SCORE1++;
				                score2.tile_index = score2.tile_index - 1;
			                }

                            player1.x = START1_X;
                            player1.y = START1_Y;
                            player1.tile_index = SPRITE_RIGHT;
                            player2.x = START2_X;
                            player2.y = START2_Y;
                            player2.tile_index = SPRITE_LEFT;
                            
                        } 
                        else 
                        {
                            player1.y = player1.y - SPEED;
                        }
                    }
                    else
                    {
                        player1.y = player1.y - SPEED;
                    }
       	        } 
                else 
                {
                    player1.y = player1.y - SPEED;
                }   
    	    }
    	} 	
    	else if (InputPort1 & BUTTON_DOWN)		
    	{
    	    player1.tile_index  = SPRITE_DOWN;	
            if (player1.y < B_BOT)
    	    {
        	    if (player1.y <= player2.y)
        		{
                    if(P1_RGT >= player2.x &&
                       P1_LFT <= player2.x)
                    {
    		            if(P1_TOP >= player2.y)
                        {
                            if(player2.tile_index != SPRITE_UP)
                            {
                                SCORE1++;
				                score2.tile_index = score2.tile_index - 1;
			                }

                            player1.x = START1_X;
                            player1.y = START1_Y;
                            player1.tile_index = SPRITE_RIGHT;
                            player2.x = START2_X;
                            player2.y = START2_Y;
                            player2.tile_index = SPRITE_LEFT;
                        } 
                        else 
                        {
                                player1.y = player1.y + SPEED;
                        }
                    }
                    else
                    {
                        player1.y = player1.y + SPEED;
                    }
       	        } 
                else 
                {
                    player1.y = player1.y + SPEED;
                }
    	    }
    	}
    	else if (InputPort1 & BUTTON_LEFT)		
    	{	
    	    player1.tile_index  = SPRITE_LEFT;	
    	    if (player1.x > B_LFT)
    	    {
         	if (player1.x >= player2.x)
        	{
                    if(player1.y + SPRITE_HEIGHT >= player2.y &&
                       player1.y - SPRITE_HEIGHT <= player2.y)
                    {
    		            if(P1_LFT <= player2.x)
                        {
                            if(player2.tile_index != SPRITE_RIGHT)
                            {
                                SCORE1++;
				                score2.tile_index = score2.tile_index - 1;
			                }

                                
                            player1.x = START1_X; 
                            player1.y = START1_Y;
                            player1.tile_index = SPRITE_RIGHT;
                            player2.x = START2_X;
                            player2.y = START2_Y;
                            player2.tile_index = SPRITE_LEFT;
                        } 
                        else 
                        {
                            player1.x = player1.x - SPEED;
                        }
                    }
                    else
                    {
                        player1.x = player1.x - SPEED;
                    }
       	        } 
                else 
                {
                    player1.x = player1.x - SPEED;
                }
    	    } 	 
    	}
    	else if (InputPort1 & BUTTON_RIGHT)		
    	{
    	    player1.tile_index  = SPRITE_RIGHT;
    	    if (player1.x < B_RGT)		 
    	    {
          	if (player1.x <= player2.x)
        	{
                    if(P1_TOP >= player2.y &&
                       P1_BOT <= player2.y)
                    {
    		            if(P1_RGT >= player2.x)
                        {
                            if(player2.tile_index != SPRITE_LEFT)
                            {
                                SCORE1++;
				                score2.tile_index = score2.tile_index - 1;
			                }
 
                            
                            player1.x = START1_X; 
                            player1.y = START1_Y;
                            player1.tile_index = SPRITE_RIGHT;
                            player2.x = START2_X;
                            player2.y = START2_Y;
                            player2.tile_index = SPRITE_LEFT;                          
                        }  
                        else 
                        {
                            player1.x = player1.x + SPEED;
                        }
                    }
                    else
                    {
                        player1.x = player1.x + SPEED;
                    }
       	        } 
                else 
                {
                    player1.x = player1.x + SPEED;
                }
     
    	    }	
    	}

    	if (InputPort2 & BUTTON_UP)
    	{
    	    player2.tile_index  = SPRITE_UP;
      	    if (player2.y > B_TOP)
    	    {
     	        if (player2.y >= player1.y)
        		{
                    if( P2_RGT >= player1.x &&
                        P2_LFT <= player1.x)
                    {
    		            if(P2_BOT <= player1.y)
                        {
                            if(player1.tile_index != SPRITE_DOWN)
                            {
                                SCORE2++;
				                score1.tile_index = score1.tile_index - 1;
			                }

                            player1.x = START1_X;
                            player1.y = START1_Y;
                            player1.tile_index = SPRITE_RIGHT;
                            player2.x = START2_X;
                            player2.y = START2_Y;
                            player2.tile_index = SPRITE_LEFT;
                            
                        } 
                        else 
                        {
                            player2.y = player2.y - SPEED2;
                        }
                    }
                    else
                    {
                        player2.y = player2.y - SPEED2;
                    }
       	        } 
                else 
                {
                    player2.y = player2.y - SPEED2;
                }   
    	    }
    	} 	
    	else if (InputPort2 & BUTTON_DOWN)		
    	{
    	    player2.tile_index  = SPRITE_DOWN;	
            if (player2.y < B_BOT)
    	    {
        	if (player2.y <= player1.y)
        	{
                    if(P2_RGT >= player1.x &&
                       P2_LFT <= player1.x)
                    {
    		            if(P2_TOP >= player1.y)
                        {
                            if(player1.tile_index != SPRITE_UP)
                            {
                                SCORE2++;
				                score1.tile_index = score1.tile_index - 1;
			                }

                            player1.x = START1_X;
                            player1.y = START1_Y;
                            player1.tile_index = SPRITE_RIGHT;
                            player2.x = START2_X;
                            player2.y = START2_Y;
                            player2.tile_index = SPRITE_LEFT;
                        } 
                        else 
                        {
                                player2.y = player2.y + SPEED2;
                        }
                    }
                    else
                    {
                        player2.y = player2.y + SPEED2;
                    }
       	        } 
                else 
                {
                    player2.y = player2.y + SPEED2;
                }
    	    }
    	}
    	else if (InputPort2 & BUTTON_LEFT)		
    	{	
    	    player2.tile_index  = SPRITE_LEFT;	
    	    if (player2.x > B_LFT)
    	    {
         	if (player2.x >= player1.x)
        	{
                    if(P2_TOP >= player1.y &&
                       P2_BOT <= player1.y)
		    {
    		            if(P2_LFT <= player1.x)
                        {
                            if(player1.tile_index != SPRITE_RIGHT)
                            {
                                SCORE2++;
				                score1.tile_index = score1.tile_index - 1;
			                }
                                
                            player1.x = START1_X; 
                            player1.y = START1_Y;
                            player1.tile_index = SPRITE_RIGHT;
                            player2.x = START2_X;
                            player2.y = START2_Y;
                            player2.tile_index = SPRITE_LEFT;
                        } 
                        else 
                        {
                            player2.x = player2.x - SPEED2;
                        }
                    }
                    else
                    {
                        player2.x = player2.x - SPEED2;
                    }
       	        } 
                else 
                {
                    player2.x = player2.x - SPEED2;
                }
    	    } 	 
    	}
    	else if (InputPort2 & BUTTON_RIGHT)		
    	{
    	    player2.tile_index  = SPRITE_RIGHT;
    	    if (player2.x < B_RGT)		 
    	    {
          	if (player2.x <= player1.x)
        	{
                    if(P2_TOP >= player1.y &&
                       P2_BOT <= player1.y)
                    {
    		            if(P2_RGT >= player1.x)
                        {
                            if(player1.tile_index != SPRITE_LEFT)
                            {
                                SCORE2++;
				                score1.tile_index = score1.tile_index - 1;
			                }  
                            
                            player1.x = START1_X; 
                            player1.y = START1_Y;
                            player1.tile_index = SPRITE_RIGHT;
                            player2.x = START2_X;
                            player2.y = START2_Y;
                            player2.tile_index = SPRITE_LEFT;                          
                        }  
                        else 
                        {
                            player2.x = player2.x + SPEED2;
                        }
                    }
                    else
                    {
                        player2.x = player2.x + SPEED2;
                    }
       	        } 
                else 
                {
                    player2.x = player2.x + SPEED2;
                }
     
    	    }	    
    	}

        //Player1 pause
        if(InputPort1 & BUTTON_SELECT)
        {
            //This would, in it's current state, the pause screen.  As the title
            //screen only has "PRESS START" on it, it would be used indicate 
            //that after pressing select to pause the game, you need to press 
            //start in order to resume the game
            //
            //PPU_MASK = 0x00;
            //PPU_CTRL = 0x00;
            //DrawTitle();

            while(1)
            {
                if(InputPort1 & BUTTON_START)
                {
                    break;
                }
                WaitFrame();
	            ResetScroll();
            }
        }

        //Player2 pause
        if(InputPort2 & BUTTON_SELECT)
        {
            while(1)
            {
                if(InputPort2 & BUTTON_START)
                {
                    break;
                } 
                WaitFrame();
	            ResetScroll();
            }
        }

	    if (SCORE1 == 5)
	    {
	        score1.tile_index = 0x77;
	        score2.tile_index = 0x6C;
	        while(1)
	        {
		        if(InputPort1 & BUTTON_START)
		        {	
		            Game_Setup();
		            break;
		        } 
		        else if (InputPort2 & BUTTON_START)
		        {
		            Game_Setup();
		            break;
		        }
                WaitFrame();
	            ResetScroll();
	        }
	    }
	
	    if(SCORE2 == 5)
	    {
	        score1.tile_index = 0x6C;
	        score2.tile_index = 0x77;
	        while(1)
	        {
		        if(InputPort1 & BUTTON_START)
		        {	
		            Game_Setup();
		            break;
		        } 
		        else if (InputPort2 & BUTTON_START)
		        {
		            Game_Setup();
		            break;
		        }
                WaitFrame();
	            ResetScroll();
	        }
	    }

        WaitFrame();
	    ResetScroll();
    };
    //A note, i did have a "slow" powerup working, kind of.  There was an 
    //issue with it bogging down the game, so this version excludes it.  
    //However, i'll quickly describe how it worked.  You had a powerup sprite
    //set to the "S" on the sprite sheet.   This would appear in the middle of
    //the screen after 500 frames during one life of the players.  If someone
    //"died" or "tied", the counter would reset.  However, if it appeared, and
    //a player ran through it, a state variable would be flipped.  While this
    //variable was flipped, the counter would reset to 100.  During the duration
    //of the timer, the other player was slowed to 1 pixel movement speed versus
    //the normal 3 pixel movement speed.  If the players collide, the state 
    //variable flips back to normal, same with the player's speed, and then the
    //counter is reset and stuff is scored as normal.
}

//This is the main function, most of the stuff has been gutted and placed in
//functions as i had trouble reading my code otherwise.
void main (void)
{

    ppu_addr           = PPU_PALETTE;
    ppu_data           = PALETTES;
    ppu_data_size      = sizeof(PALETTES);
   
    PPU_ADDRESS = (uint8_t)((PPU_NAMETABLE_0 + NAMETABLE_OFFSET) >> 8);
    PPU_ADDRESS = (uint8_t) (PPU_NAMETABLE_0 + NAMETABLE_OFFSET);

    DrawArena();
    Title_Setup();
    Title_Loop();
    
    //An attempt at redrawing the screen, it "works", but not really.
/*
    PPU_MASK = 0x00;
    PPU_CTRL = 0x00;
    DrawArena();
*/    
    Game_Setup();

    Game_Loop();   

};
