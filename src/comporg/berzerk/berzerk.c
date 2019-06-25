#define TV_NTSC 1
#include "nes.h"
#include "reset.h"
#include "data.h"
#include <stddef.h>
#include <stdint.h>
#include <6502.h>

#define BLANK_TILE      0x00
#define BORDER_TL       0x01
#define BORDER_TR       0x02
#define BORDER_BL       0x11
#define BORDER_BR       0x12
#define BORDER_T        0x04
#define BORDER_B        0x14
#define BORDER_L        0x03
#define BORDER_R        0x13
#define SPRITE_PLAYER   0x10
#define SPRITE_MISSILE1 0x2E
#define SPRITE_MISSILE2 0x6F

#define UP              0
#define DOWN            1
#define LEFT            2
#define RIGHT           3

#pragma bss-name(push, "ZEROPAGE")
uint8_t    i;
uint8_t    j;
uint8_t    p1d;
uint8_t    p2d;
uint8_t    m1d;
uint8_t    m2d;
uint8_t    m1t;
uint8_t    m2t;

uintptr_t  ppu_addr;
uint8_t    const * ppu_data;
uint8_t    ppu_data_size;
#pragma bss-name(pop)

#pragma bss-name(push, "OAM")
sprite_t player1;
sprite_t player2;
sprite_t missile1;
sprite_t missile2;
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
	player1.tile_index  = SPRITE_PLAYER;
	player1.attributes  = player1.attributes & 0x00;

	missile1.x           = -2;
	missile1.y           = -2;
	missile1.tile_index  = SPRITE_MISSILE1;
	missile1.attributes  = missile1.attributes & 0x00;
	missile1.attributes  = missile1.attributes | 0x02;

	player2.x           = (MAX_X / 2) - (SPRITE_WIDTH  / 2) + 50;
	player2.y           = (MAX_Y / 2) - (SPRITE_HEIGHT / 2);
	player2.tile_index  = SPRITE_PLAYER;
	player2.attributes  = player2.attributes & 0x00;
	player2.attributes  = player2.attributes | 0x01;

	missile2.x           = -2;
	missile2.y           = -2;
	missile2.tile_index  = SPRITE_MISSILE2;
	missile2.attributes  = missile2.attributes & 0x00;
	missile2.attributes  = missile2.attributes | 0x02;

	ResetScroll();
	EnablePPU();

	while (1)
	{
		WaitFrame();
		ResetScroll();

		if (InputPort1 & BUTTON_UP)
		{
			if (player1.y > MIN_Y + SPRITE_HEIGHT)
			{
				--player1.y;
				p1d = UP;
			}		
		}

		if (InputPort1 & BUTTON_DOWN)
		{
			if (player1.y < MAX_Y - (2 * SPRITE_HEIGHT))
			{
				++player1.y;
				p1d = DOWN;
			}
		}

		if (InputPort1 & BUTTON_LEFT)
		{
			if (player1.x > MIN_X + SPRITE_WIDTH)
			{
				--player1.x;
				p1d = LEFT;
			}
		}

		if (InputPort1 & BUTTON_RIGHT)
		{
			if (player1.x < MAX_X - (2 * SPRITE_WIDTH))
			{
				++player1.x;
				p1d = RIGHT;
			}
		}

		if (InputPort1 & BUTTON_B)
		{
			m1d         = p1d; // set missile direction to player dir
			m1t         = 0;   // reset missile1 tally

			missile1.x  = player1.x;
			missile1.y  = player1.y;
		}

		if ((missile1.x != 0) && (missile1.y != 0))
		{
			if (m1d == UP)
				--missile1.y;
			else if (m1d == DOWN)
				++missile1.y;
			else if (m1d == LEFT)
				--missile1.x;
			else
				++missile1.x;

			++m1t;
		}

		if (m1d         >  64)
			missile1.tile_index = SPRITE_MISSILE2;
		else
			missile1.tile_index = SPRITE_MISSILE1;

		if ((missile1.x <= 0)     ||
			(missile1.x >= MAX_X) ||
			(missile1.y <= 0)     ||
			(missile1.y >= MAX_Y))
		{
			missile1.x = -2;
			missile1.y = -2;
		}

		if (InputPort2 & BUTTON_UP)
		{
			if (player2.y > MIN_Y + SPRITE_HEIGHT)
			{
				--player2.y;
				p2d = UP;
			}		
		}

		if (InputPort2 & BUTTON_DOWN)
		{
			if (player2.y < MAX_Y - (2 * SPRITE_HEIGHT))
			{
				++player2.y;
				p2d = DOWN;
			}
		}

		if (InputPort2 & BUTTON_LEFT)
		{
			if (player2.x > MIN_X + SPRITE_WIDTH)
			{
				--player2.x;
				p2d = LEFT;
			}
		}

		if (InputPort2 & BUTTON_RIGHT)
		{
			if (player2.x < MAX_X - (2 * SPRITE_WIDTH))
			{
				++player2.x;
				p2d = RIGHT;
			}
		}

		if (InputPort2 & BUTTON_B)
		{
			m2d         = p2d; // set missile direction to player dir
			m2t         = 0;

			missile2.x  = player2.x;
			missile2.y  = player2.y;
		}

		if ((missile2.x != 0) && (missile2.y != 0))
		{
			if (m2d == UP)
				--missile2.y;
			else if (m2d == DOWN)
				++missile2.y;
			else if (m2d == LEFT)
				--missile2.x;
			else
				++missile2.x;
		}

		if (m2d         >  64)
			missile2.tile_index = SPRITE_MISSILE2;
		else
			missile2.tile_index = SPRITE_MISSILE1;

		if ((missile2.x <= 0)     ||
			(missile2.x >= MAX_X) ||
			(missile2.y <= 0)     ||
			(missile2.y >= MAX_Y))
		{
			missile2.x = -2;
			missile2.y = -2;
		}
	};
};
