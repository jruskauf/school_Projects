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

int SPEED = WALK;

#pragma bss-name(push, "ZEROPAGE")
uint8_t    i;
uint8_t    j;

uintptr_t  ppu_addr;
uint8_t    const * ppu_data;
uint8_t    ppu_data_size;
#pragma bss-name(pop)

#pragma bss-name(push, "OAM")
sprite_t player1;
sprite_t player2;
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

void DrawBackground()
{
	PPU_ADDRESS = (uint8_t)((PPU_NAMETABLE_0 + NAMETABLE_OFFSET) >> 8);
	PPU_ADDRESS = (uint8_t) (PPU_NAMETABLE_0 + NAMETABLE_OFFSET);

	PPU_DATA = BORDER_TL;
	for(i = 0; i < (NUM_COLS - 2); ++i)
	{
		PPU_DATA = BORDER_T;
	}
	PPU_DATA = BORDER_TR;

	for (i = 0; i < (NUM_ROWS - 2); ++i)
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

void main (void)
{
	ppu_addr           = PPU_PALETTE;
	ppu_data           = PALETTES;
	ppu_data_size      = sizeof(PALETTES);
	WritePPU();

	DrawBackground();

	player1.x           = (MAX_X / 2) - (SPRITE_WIDTH  / 2) - 50;
	player1.y           = (MAX_Y / 2) - (SPRITE_HEIGHT / 2);
	player1.tile_index  = SPRITE_DOWN;
	player1.attributes  = player1.attributes & 0x00;

	player2.x           = (MAX_X / 2) - (SPRITE_WIDTH  / 2) + 50;
	player2.y           = (MAX_Y / 2) - (SPRITE_HEIGHT / 2);
	player2.tile_index  = SPRITE_DOWN;
	player2.attributes  = player2.attributes & 0x00;
	player2.attributes  = player2.attributes | 0x01;

	ResetScroll();
	EnablePPU();

	SPEED = WALK;

	while (1)
	{
		WaitFrame();
		ResetScroll();


		if (InputPort1 & BUTTON_B)
		{
			SPEED = SPRINT;
		} else {
			SPEED = WALK;
		}

		if (InputPort1 & BUTTON_UP)
		{
			player1.tile_index  = SPRITE_UP;
			if (player1.y > MIN_Y + SPRITE_HEIGHT)
			{
				player1.y = player1.y - SPEED;
			}		
		}

		if (InputPort1 & BUTTON_DOWN)
		{
			player1.tile_index  = SPRITE_DOWN;
			if (player1.y < MAX_Y - (2 * SPRITE_HEIGHT))
			{
				player1.y = player1.y + SPEED;;
			}
		}

		if (InputPort1 & BUTTON_LEFT)
		{
			player1.tile_index  = SPRITE_LEFT;
			if (player1.x > MIN_X + SPRITE_WIDTH)
			{
				player1.x = player1.x - SPEED;
			}
		}

		if (InputPort1 & BUTTON_RIGHT)
		{
			player1.tile_index  = SPRITE_RIGHT;
			if (player1.x < MAX_X - (2 * SPRITE_WIDTH))
			{
				player1.x = player1.x + SPEED;
			}
		}

		if (InputPort2 & BUTTON_UP)
		{
			player2.tile_index  = SPRITE_UP;
			if (player2.y > MIN_Y + SPRITE_HEIGHT)
			{
				--player2.y;
			}		
		}

		if (InputPort2 & BUTTON_DOWN)
		{
			player2.tile_index  = SPRITE_DOWN;
			if (player2.y < MAX_Y - (2 * SPRITE_HEIGHT))
			{
				++player2.y;
			}
		}

		if (InputPort2 & BUTTON_LEFT)
		{
			player2.tile_index  = SPRITE_LEFT;
			if (player2.x > MIN_X + SPRITE_WIDTH)
			{
				--player2.x;
			}
		}

		if (InputPort2 & BUTTON_RIGHT)
		{
			player2.tile_index  = SPRITE_RIGHT;
			if (player2.x < MAX_X - (2 * SPRITE_WIDTH))
			{
				++player2.x;
			}
		}
	};
};
