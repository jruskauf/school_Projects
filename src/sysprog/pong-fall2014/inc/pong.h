#ifndef _PONG_H
#define _PONG_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_ttf.h>

#include "player.h"
#include "missile.h"
#include "object.h"
#include "config.h"

#define	 ON			1
#define	 OFF		0

#define	 NPC		0
#define	 HUMAN		1

#define	 LOCAL		0
#define	 REMOTE		1

#define  NONE		0
#define	 JOYSTICK	1
#define	 KEYBOARD	2
#define	 MOUSE		4

#define  LEFT		1
#define  RIGHT		2
#define  TOP		4
#define	 BOTTOM		8

struct pong {
	SDL_Surface    *screen;
	SDL_Surface    *background;
	SDL_Surface    *message;
	SDL_Surface    *score; //SCORE ADDITION
	SDL_Rect        offset;
	SDL_Rect        textpos;
	SDL_Rect        stextpos; //SCORE ADDITION
	Player         *paddle;
	Object         *item;
	Missile        *ball;
	SDL_Event       event;
	TTF_Font       *font;
	SDL_Color       textColor;
	int             textalpha;
	SDL_Thread     *sfx_thread;
	struct {
		int         width;
		int         height;
		int         bpp;
	} field;
	int             num[NUM_OBJECTS];
	int             joystick_num;
	int             num_missiles;
	int             num_paddles;
	int             num_players;
	int             fps_cap;
	int             newserve;
	int             logos;
	int             sfx;
	unsigned char	wallflower;
	unsigned char	autopilot;
};
typedef struct pong Pong;

FILE               *debug;
FILE               *output;
FILE               *verbose;
FILE               *verbose2;
FILE               *verbose3;
unsigned char       verbosity_level;
int                 game_quit;
int                 readysfx;
Mix_Chunk          *sfx;
Mix_Chunk          *ball[3];	// 0 - hit, 1 - miss, 2 - serve

Config             *args           (int, char **, Pong *    );
Missile            *alloc_missile  (Pong *, int, char *     );
Object             *alloc_object   (Pong *, int, char *, int);
Player             *alloc_player   (Pong *, Config *, char *);
Pong               *collision      (Pong *                  );
void                deinit         (Pong *                  );
void                display_usage  (void                    );
void                display_version(void                    );
char               *dirproc        (const char *            );
Pong               *init           (Pong *, Config *        );
Pong               *input          (Pong *                  );
SDL_Surface        *load_image     (char *                  );
int                 sfxplay        (void *                  );
Pong               *set_scenario   (Pong *, int             );
void                title          (Pong *                  );

#endif
