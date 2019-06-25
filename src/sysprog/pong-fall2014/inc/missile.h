#ifndef _MISSILE_H
#define _MISSILE_H

struct missile {
	SDL_Surface *sprite;
	SDL_Rect pos;
	int wide;
	int high;
	int xmove;
	int ymove;
	Uint8 Bhit;
	Uint8 bhit;
	char *filename;
	struct missile *next;
};
typedef struct missile Missile;

#endif
