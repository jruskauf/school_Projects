#include <SDL/SDL.h>
#include <stdlib.h>

SDL_Surface *load_image(char *);
void apply_surface( int, int, SDL_Surface *, SDL_Surface *);

int main (int argc, char **argv)
{
    
    SDL_Surface *image  = NULL;            //Initializing 
    SDL_Surface *screen = NULL;            //Initializing the screen's variable

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) //Initializing everything in SDL
        exit(1);			   //Returning 1 if SDL_Init fails

    /*
    || SDL_Init can also be used specifically; the example below initializing
    || only the timer and audio in SDL
    ||  
    || SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO); 
    */
    
    //Initializing the screen with an 800x600 pixel surface, a 32-bit color
    //palette, and SWSURFACE sets up the surface in software memory.
    screen              = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
    if(screen          == NULL)
	exit(2);			  //Returning 2 if screen failed

    //Loading the image by specifying the name of the image we downloaded
    //(in this casea bmp file by the name of "mudkip.bmp")
    image               = load_image ("sprite.bmp");

    //This places the image on the surface, the NULL after the variable
    //meaning that we want the WHOLE image to be on the screen.
    apply_surface (0, 0, image, screen);

    SDL_Flip(screen);                   //Flipping from offscreen to onscreen

    SDL_Delay(2000);                    //Delaying the process by 2 seconds

    SDL_FreeSurface(image);             //Cleaning up made surfaces

    SDL_Quit();                         //De-initializes SDL
 
    return(0);                          //Returning 0 upon successful completion
}

SDL_Surface *load_image (char *filename)
{
    SDL_Surface *loadedImage = NULL;
    SDL_Surface *optImage = NULL;

    loadedImage = SDL_LoadBMP(filename);
    if(loadedImage == NULL)
	exit(3);

    optImage = SDL_DisplayFormat (loadedImage);

    SDL_FreeSurface (loadedImage);

    return(optImage);
}

void apply_surface (int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface (source, NULL, destination, &offset);
}
