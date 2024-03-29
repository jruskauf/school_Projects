/**
 * data.h
 *
 * http://timcheeseman.com/nesdev/
 */

#ifndef DATA_H_
#define DATA_H_

#include <stdint.h>

#include "nes.h"

// palettes
uint8_t const PALETTES[] = {
    COLOR_BLACK,                           // background color
    COLOR_RED, COLOR_NO, COLOR_OLIVE,       // background palette 0
    0,                                     // ignored
    0, 0, 0,                               // background palette 1
    0,                                     // ignored
    0, 0, 0,                               // background palette 2
    0,                                     // ignored
    0, 0, 0,                               // background palette 3

    COLOR_WHY,                           // background color (mirror)
    COLOR_RED, COLOR_NO, COLOR_OLIVE,    // sprite palette 0
    COLOR_BLACK,                           // ignored
    COLOR_YELLOW, COLOR_GREEN, COLOR_BLUE, // sprite palette 1
    0,                                     // ignored
    COLOR_WHITE, COLOR_YELLOW, COLOR_BROWN,// sprite palette 2
    0,                                     // ignored
    0, 0, 0,                               // sprite palette 3
};

// tile indices
/*#define BLANK_TILE    0x00
#define BORDER_TL     0x01
#define BORDER_TR     0x02
#define BORDER_BL     0x11
#define BORDER_BR     0x12
#define BORDER_T      0x04
#define BORDER_B      0x14
#define BORDER_L      0x03
#define BORDER_R      0x13
#define SPRITE_PLAYER 0x10
*/
#endif // DATA_H_
