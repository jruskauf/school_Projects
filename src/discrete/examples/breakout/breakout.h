#ifndef  _BREAKOUT_H
#define  _BREAKOUT_H

#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define  TRUE    0
#define  FALSE   1

struct player
{
	SDL_Rect        pos;
	SDL_Surface    *sprite;
	struct player  *next;
	int             xvel;
};
typedef struct player Player;

struct missile
{
	SDL_Rect        pos;
	SDL_Surface    *sprite;
	int             xdir;
	int             xmag;
	int             ydir;
	int             ymag;
	int             visible;
	int             move;
	struct missile *next;
};
typedef struct missile Missile;

struct block
{
	SDL_Rect        pos;
	SDL_Surface    *sprite;
	int             visible;
	struct block   *next;
};
typedef struct block Block;

// Game variables
Player  *paddle;
Missile *ball;
Block   *bricks;

SDL_Surface *load_image (char *);
void apply_surface (int, int, SDL_Surface *, SDL_Surface *);

#endif
