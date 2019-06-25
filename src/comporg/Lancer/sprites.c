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

uint8_t    STATE;

uint8_t    START1_X;
uint8_t    START1_Y;
uint8_t    START2_X;
uint8_t    START2_Y;    

uint8_t    SPEED;
uint8_t    SPEED2;
uint8_t    SCORE1;
uint8_t    SCORE2;

uint8_t    B_TOP;
uint8_t    B_BOT;
uint8_t    B_RGT;
uint8_t    B_LFT;

uint8_t    P1_TOP;
uint8_t    P1_BOT;
uint8_t    P1_RGT;
uint8_t    P1_LFT;

uint8_t    P2_TOP;
uint8_t    P2_BOT;
uint8_t    P2_RGT;
uint8_t    P2_LFT;

uint8_t    tmp_sprite;

uintptr_t  ppu_addr;
uint8_t    const * ppu_data;
uint8_t    ppu_data_size;
#pragma bss-name(pop)

#pragma bss-name(push, "OAM")
sprite_t player1;
sprite_t player2;
sprite_t score1;
sprite_t score2;

#pragma bss-name(pop)

void ResetScroll()
{
    PPU_SCROLL = 0x00;
    PPU_SCROLL = 0x00;
}

void EnablePPU()
{
    PPU_CTRL = PPUCTRL_NAMETABLE_0 | PPUCTRL_BPATTERN_0 | PPUCTRL_NMI_ON;
    PPU_MASK = PPUMASK_COLOR       | PPUMASK_BSHOW      | PPUMASK_L8_BSHOW |
	       PPUMASK_SSHOW       | PPUMASK_L8_SSHOW;;
}

void WritePPU()
{
    PPU_ADDRESS = (uint8_t)(ppu_addr >> 8);
    PPU_ADDRESS = (uint8_t)(ppu_addr);
    for (i = 0; i < ppu_data_size; ++i) 
    {
	PPU_DATA = ppu_data[i];
    }
}



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

void Title_Setup()
{
    START1_X = (MAX_X / 2) - (SPRITE_WIDTH  / 2) - 50;
    START1_Y = (MAX_Y / 2) - (SPRITE_HEIGHT / 2);

    START2_X = (MAX_X / 2) - (SPRITE_WIDTH  / 2) + 50;
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
    score1.attributes   = player1.attributes & 0x00;


    score2.x = MAX_X - SPRITE_WIDTH - SPRITE_WIDTH;
    score2.y = MIN_Y + SPRITE_HEIGHT;
    score2.tile_index   = 0x55;
    score2.attributes   = score2.attributes & 0x00;


}

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


        if(InputPort1 & BUTTON_START)
            STATE++;

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
}


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

/*
    ppu_addr           = PPU_PALETTE >> 16;
    ppu_data           = PALETTES;
    DrawArena();
*/

    Game_Setup();

    ResetScroll();
    EnablePPU();

    Game_Loop();

    //End_Setup;
    //End_Loop;     

};
