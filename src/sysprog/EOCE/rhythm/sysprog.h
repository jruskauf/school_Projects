#ifndef _SYSPROG_H
#define _SYSPROG_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define  TRUE  1
#define  FALSE 0

#define  ON    1
#define  OFF   0

#define  YES   1
#define  NO    0

//Setting up the struct for the node, along with a "next" node to allow
//traversal of a list.
typedef struct Node_t
{
    int delay;
    int X;
    int Y;
    SDL_Surface *sprite;
    struct Node_t *next;
} Node;

//List struct with access to the start and end of the list
typedef struct List_t
{
    Node *start;
    Node *end;
} List;

SDL_Surface *load_image(char *);
void apply_surface(int, int, SDL_Surface *, SDL_Surface *, SDL_Rect *);
Node * makeNode(int, int , int);
List * makeList();
List * populateList(List *, int, int, int, char *);
void applyList(List *, SDL_Surface *);
void moveUp(List *, int);
void moveDown(List *, int);
void moveLeft(List *, int);
void moveRight(List *, int);
int randomNum();
void delay(int);
void popNswap(List *, int, int);

#endif
