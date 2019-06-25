#include "sysprog.h"

SDL_Surface *load_image (char *filename)
{
	SDL_Surface *loadedImage  = NULL;
	SDL_Surface *optImage     = NULL;

	Uint32       colorkey     = 0;

	loadedImage  = IMG_Load(filename);
	if (loadedImage == NULL)
		exit (3);

	optImage = SDL_DisplayFormat (loadedImage);

	SDL_FreeSurface (loadedImage);

	if (optImage != NULL)
	{
		colorkey  = SDL_MapRGB (optImage -> format, 120, 195, 128);
		SDL_SetColorKey (optImage, SDL_SRCCOLORKEY, colorkey);
	}

	return (optImage);
}

void apply_surface (int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface (source, clip, destination, &offset);
}

Node *makeNode (int dValue, int xValue, int yValue)
{
	Node * new = NULL;
	new = (Node *)malloc(sizeof(Node));
	new -> delay = dValue;
	new -> X = xValue;
	new -> Y = yValue;
	new -> sprite = NULL;

	return(new);
}
   
List *makeList()
{
	List * new = NULL;
	new = (List*)malloc(sizeof(List));
	new -> start = NULL;
	new -> end   = NULL;

	return(new);
}

List *populateList(List *emptyList, int num, int X, int Y, char *image)
{
	int i = 0;
	List * full = makeList();
	Node * tmp = NULL;
	srand(time(NULL));
	full -> start = makeNode(randomNum(), X, Y);
	tmp = full -> start;
	for(i = 0; i < num; i++)
	{
		tmp -> delay = tmp -> delay + randomNum();
		tmp -> next = makeNode(tmp -> delay, X, Y);
		tmp -> sprite = load_image(image);
		tmp = tmp -> next;
	}
	full -> end = tmp;
	full -> end -> next = NULL;
	delay(1000);
	return(full);
}

void applyList(List *list, SDL_Surface *screen)
{
	Node *tmp = list -> start;
	while(tmp != NULL)
	{
		apply_surface(tmp -> X, tmp -> Y, tmp -> sprite, screen, NULL);
		tmp = tmp -> next;
	}
}

void moveDown(List *list, int move)
{
	Node *tmp = list -> start;
	while(tmp != NULL)
	{
		if(tmp -> delay <= 0)
		{
			tmp -> Y = tmp -> Y + move;
		} 
		else 
		{
			tmp -> delay--;
		}
		tmp = tmp -> next;
	}
}

void moveUp(List *list, int move)
{
	Node *tmp = list -> start;
	while(tmp != NULL)
	{
		if(tmp -> delay <= 0)
		{
			tmp -> Y = tmp -> Y - move;
		} 
		else 
		{
			tmp -> delay--;
		}
		tmp = tmp -> next;
	}
}

void moveLeft(List *list, int move)
{
	Node *tmp = list -> start;
	while(tmp != NULL)
	{
		if(tmp -> delay <= 0)
		{
			tmp -> X = tmp -> X - move;
		} 
		else 
		{
			tmp -> delay--;
		}
		tmp = tmp -> next;
	}
}

void moveRight(List *list, int move)
{
	Node *tmp = list -> start;
	while(tmp != NULL)
	{
		if(tmp -> delay <= 0)
		{
			tmp -> X = tmp -> X + move;
		} 
		else 
		{
			tmp -> delay--;
		}
		tmp = tmp -> next;
	}
}

int randomNum()
{
	int upper = 120;
	int lower = 60;
	int num   = (rand() % (upper - lower + 1)) + lower;
	
	return(num);
}

void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

void popNswap(List *list, int X, int Y)
{
	Node *tmp = list -> start;
	list -> start = tmp -> next;
	tmp -> next = NULL;
	list -> end -> next = tmp;
	tmp -> delay = randomNum() + list -> end -> delay;
	tmp -> X = X;
	tmp -> Y = Y;
	list -> end = tmp;
	list -> end -> next = NULL;
}
