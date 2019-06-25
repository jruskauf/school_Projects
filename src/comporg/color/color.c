#define TV_NTSC 1
#include "nes.h"
#include "reset.h"
#include "data.h"
#include <stddef.h>
#include <stdint.h>
#include <6502.h>

#pragma bss-name(push, "ZEROPAGE")
uint8_t    i;
uint8_t    attr_offset;

uintptr_t  ppu_addr;
uint8_t    const * ppu_data;
uint8_t    ppu_data_size;

#pragma bss-name(pop)

void ResetScroll()
{
    PPU_SCROLL = 0x00;
    PPU_SCROLL = 0x00;
}

void EnablePPU()
{
    PPU_CTRL = PPUCTRL_NAMETABLE_0 | PPUCTRL_BPATTERN_0 | PPUCTRL_NMI_ON;
    PPU_MASK = PPUMASK_COLOR       | PPUMASK_BSHOW;
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

void main(void)
{
    ppu_addr = PPU_PALETTE;
    ppu_data = PALETTES;
    ppu_data_size = sizeof(PALETTES);
    WritePPU();

    ppu_addr = PPU_NAMETABLE_0 + TEXT_OFFSET;
    ppu_data = (uint8_t const *) TEXT;
    ppu_data_size = sizeof(TEXT);
    WritePPU();

    ppu_addr = PPU_NAMETABLE_0 + (TEXT_OFFSET + 32);
    ppu_data = (uint8_t const *) TEXT;
    ppu_data_size = sizeof(TEXT);
    WritePPU();

    ppu_addr = PPU_ATTRIB_TABLE_0 + ATTR_OFFSET;
    ppu_data = ATTRIBUTES;
    ppu_data_size = ATTR_SIZE;
    WritePPU();

    ResetScroll();
    EnablePPU();

    attr_offset = ATTR_SIZE;
    while(1)
    {
	if (FrameCount == (FRAMES_PER_SEC / 2))
	{
	    ppu_data = ATTRIBUTES + attr_offset;
	    WritePPU();

	    attr_offset = attr_offset + ATTR_SIZE;
	    if (attr_offset == sizeof (ATTRIBUTES))
	    {
		attr_offset = 0;

	    }

	    ResetScroll();
	    FrameCount = 0;
	}
    }
}
