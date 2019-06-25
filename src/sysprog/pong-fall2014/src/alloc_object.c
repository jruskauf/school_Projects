#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pong.h"

Object *alloc_object(Pong *game, int num, char *img_wd, int type)
{
	char     *img_filename    = NULL;
	int       i               = 0;
	int       j               = 0;
	Object   *otmp            = NULL;
	size_t    count           = 0;

	fprintf(verbose3, "[verbose]    object %d:\n", num);
	fprintf(verbose3, "[verbose]\tmalloc ... ");

	count                     = sizeof(Object);
	otmp                      = (Object *) malloc (count);
	if (otmp                 == NULL)
	{
		fprintf(verbose3, "FAIL\n");
		exit(11);
	}
	fprintf(verbose3, "OK\n");

	fprintf(verbose3, "[verbose]\timage  ... ");

	count                         = strlen(img_wd)+strlen("/XXXXXXXX.png");
	otmp -> filename              = (char *)malloc(count);
	if (otmp -> filename         == NULL)
	{   
		fprintf(verbose3, "FAIL\n");
	    exit(6);
	}   
	fprintf(verbose3, "OK\n");

	otmp -> type                  = type;

	fprintf(verbose3, "[verbose]\t type  ... ");
	switch(type)
	{
		case HWALL:
			fprintf(verbose3, "HORIZONTAL WALL\n");
			sprintf(otmp -> filename, "%s/hwall.png", img_wd);
			break;

		case VWALL:
			fprintf(verbose3, "VERTICAL WALL\n");
			sprintf(otmp -> filename, "%s/vwall.png", img_wd);
			break;

		case HBLOCK:
			sprintf(otmp -> filename, "%s/hblock.png", img_wd);
			break;

		case VBLOCK:
			sprintf(otmp -> filename, "%s/vblock.png", img_wd);
			break;

		case FBLOCK:
			sprintf(otmp -> filename, "%s/fblock.png", img_wd);
			break;

		default:
			break;
	}

	if (verbosity_level > 2)
		fprintf(debug,   "[debug]  \tfile   ... %s\n", otmp -> filename);

	fprintf(verbose3, "[verbose]\tsprite ... ");

	otmp -> sprite        = load_image(otmp -> filename);
	if (otmp -> sprite   == NULL)
	{
		fprintf(verbose3, "FAIL\n");
	    exit(7);
	}
	fprintf(verbose3, "OK\n");

	otmp -> pos.x         = 0;
	otmp -> pos.y         = 0;
	otmp -> wide          = otmp -> sprite -> w;
	otmp -> high          = otmp -> sprite -> h;
	otmp -> solid         = PASSTHRU;
	otmp -> visible       = INVISIBLE;
	otmp -> next          = NULL;

	return (otmp);
}
