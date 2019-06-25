#define TV_NTSC 1
#include "nes.h"
#include "reset.h"
#include "data.h"
#include <stddef.h>
#include <stdint.h>
#include <6502.h>

#define BLANK_TILE    0x00
#define BORDER_TL     0x01
#define BORDER_TR     0x02
#define BORDER_BL     0x11
#define BORDER_BR     0x12
#define BORDER_T      0x04
#define BORDER_B      0x14
#define BORDER_L      0x03
#define BORDER_R      0x13
#define SPRITE_PLAYER 0x10

#pragma bss-name(push, "ZEROPAGE")
uint8_t    i;
uint8_t    j;

uintptr_t  ppu_addr;
uint8_t    const * ppu_data;
uint8_t    ppu_data_size;
#pragma bss-name(pop)

#pragma bss-name(push, "OAM")
sprite_t player;
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

	player.x           = (MAX_X / 2) - (SPRITE_WIDTH  / 2);
	player.y           = (MAX_Y / 2) - (SPRITE_HEIGHT / 2);
	player.tile_index  = SPRITE_PLAYER;
//	player.attributes  = player.attributes | 0x01;

	ResetScroll();
	EnablePPU();

	while (1)
	{
		WaitFrame();
		ResetScroll();

		if (InputPort1 & BUTTON_UP)
		{
			if (player.y > MIN_Y + SPRITE_HEIGHT)
			{
				--player.y;
			}		
		}

		if (InputPort1 & BUTTON_DOWN)
		{
			if (player.y < MAX_Y - (2 * SPRITE_HEIGHT))
			{
				++player.y;
			}
		}

		if (InputPort1 & BUTTON_LEFT)
		{
			if (player.x > MIN_X + SPRITE_WIDTH)
			{
				--player.x;
			}
		}

		if (InputPort1 & BUTTON_RIGHT)
		{
			if (player.x < MAX_X - (2 * SPRITE_WIDTH))
			{
				++player.x;
			}
		}
	};
};
