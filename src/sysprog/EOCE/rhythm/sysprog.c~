#include "sysprog.h"

//This handles all the messy work of loading an image, hooray!
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

//This condenses the process of blitting an image onto the surface of your game
void apply_surface (int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface (source, clip, destination, &offset);
}

//This is where we create the nodes for the list, or the "arrows" in essence.
//Each node contains a variable for time delay, X pos, Y pos, AND an image file
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
   
//Initiliazing an empty list
List *makeList()
{
	List * new = NULL;
	new = (List*)malloc(sizeof(List));
	new -> start = NULL;
	new -> end   = NULL;

	return(new);
}

//Here we populate a list with nodes.  By feeding them all the same values
//and image file we can create a list of copies.  However, by having the
//node after another have a stacked delay (node2 delay = node1 delay + random)
//we don't have arrows that won't be detected getting ahead of an arrow that
//is going to be detected.  Essentially, this prevents anyone from "cutting"
//to the front of the line.
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

//This applies all of the elements of a list onto the surface.
void applyList(List *list, SDL_Surface *screen)
{
	Node *tmp = list -> start;
	while(tmp != NULL)
	{
		apply_surface(tmp -> X, tmp -> Y, tmp -> sprite, screen, NULL);
		tmp = tmp -> next;
	}
}

//This is for the arrows starting at the top of the screen, as they must
//increment their Y value.
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

//This is for arrows starting at the bottom of the screen, and thusly
//must decriment their Y value
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

//This is for my bois on the right, who must move left
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

//I think we get the picture here.
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

//Here we feed an upper and lower bound into a function to help produce random
//time delays for the nodes
int randomNum()
{
	int upper = 90;
	int lower = 40;
	int num   = (rand() % (upper - lower + 1)) + lower;
	
	return(num);
}

//This is the delay used for generating the lists.  As each list relies on a 
//seeded random generation number, if they all generated at the same time they
//recieve the EXACT same random numbers.  So by delaying each by a second, we
//seed each list differently.
void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

//This pops a node off the front of a list, puts it on the end, and
//resets its variables while adding a new delay plus the delay of the
//node in front of it, to prevent any cutting in line.
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
