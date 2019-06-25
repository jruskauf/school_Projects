#ifndef _PLAYER_H
#define _PLAYER_H

struct player {
	SDL_Surface   *sprite;
	SDL_Rect       pos;
	SDL_Joystick  *joystick;
	int            joynum;
	int            device;
	int            type;
	int            location;
	int            num;
	int            wide;
	int            high;
	int            move;
	int			   ORIENTATION; //HORIZONTAL or VERTICAL
	int			   MOVEMENT1; //SET INDIVIDUAL PLAYER MOVEMENT1
	int			   MOVEMENT2; //SET INDIVIDUAL PLAYER MOVEMENT1
	int            score;
	int			   autopilot;
	Uint8		   Phit;
	Uint8		   phit;
	char          *filename;
	struct player *next;
};
typedef struct player Player;

struct config {
	int            num;
	int            device;
	int            location;
	int            type;
	struct config *next;
};
typedef struct config Config;

#endif
