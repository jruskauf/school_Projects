#indef  _SYSPROG_H
#define _SYSPROG_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>

SDL_Surface *load_image(char *);
void apply_surface( int, int, SDL_Surface *, SDL_Surface *);

#endif
