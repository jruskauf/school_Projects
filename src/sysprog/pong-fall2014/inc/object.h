#ifndef _OBJECT_H
#define _OBJECT_H

#define NOTHING		0
#define HWALL		1
#define VWALL		2
#define HBLOCK		3
#define VBLOCK		4
#define FBLOCK		5
#define NUM_OBJECTS	6

#define SOLID		1
#define PASSTHRU	0

#define INVISIBLE	0

struct object {
	SDL_Surface   *sprite;
	SDL_Rect       pos;
	int            wide;
	int            high;
	int            solid;
	int            type;
	int            visible;
	char          *filename;
	struct object *next;
};
typedef struct object Object;

#endif
