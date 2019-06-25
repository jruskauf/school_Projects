#ifndef _SYSPROG_H
#define _SYSPROG_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>

#define  TRUE  1
#define  FALSE 0

#define  ON    1
#define  OFF   0

#define  YES   1
#define  NO    0

SDL_Surface *load_image(char *);
void apply_surface(int, int, SDL_Surface *, SDL_Surface *);

#endif
