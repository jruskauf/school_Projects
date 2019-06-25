#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pong.h"

Missile *alloc_missile(Pong *game, int num, char *img_wd)
{
	Missile *mtmp         = NULL;
	size_t   count        = 0;

	fprintf(verbose, "[verbose]    ball %d:\n", num);

	fprintf(verbose, "[verbose]\tmalloc ... ");
	count                 = sizeof(Missile);
	mtmp                  = (Missile *) malloc (count);
	if (mtmp             == NULL)
	{
		fprintf(verbose, "FAIL\n");
		exit(6);
	}
	fprintf(verbose, "OK\n");

	fprintf(verbose, "[verbose]\timage  ... ");
	count                 = strlen(img_wd)+strlen("/ballXX.png")+20;
	mtmp -> filename      = (char *)malloc(count);
	if (mtmp -> filename == NULL)
	{
		fprintf(verbose, "FAIL\n");
		exit(6);
	}
	fprintf(verbose, "OK\n");
	sprintf(mtmp -> filename, "%s/ball%.2d.png", img_wd, num);
	fprintf(debug,   "[debug]  \tfile   ... %s\n", mtmp -> filename);

	fprintf(verbose, "[verbose]\tsprite ... ");
	mtmp -> sprite        = load_image(mtmp -> filename);
	if (mtmp -> sprite   == NULL)
	{
		fprintf(verbose, "FAIL\n");
		exit(7);
	}
	fprintf(verbose, "OK\n");

	mtmp -> pos.x         = game -> field.width /2-(mtmp -> wide/2)+(num * 2);
	mtmp -> pos.y         = game -> field.height/2-(mtmp -> high/2)+(num * 2);
	mtmp -> wide          = mtmp -> sprite -> w;
	mtmp -> high          = mtmp -> sprite -> h;
	mtmp -> xmove         = 2 + num;
//	mtmp -> xmove         = 4 + num; //faster old moving speed
	mtmp -> ymove         = 1 + num;
	mtmp -> Bhit		  = 0;
	mtmp -> bhit		  = 0x7F;
//	mtmp -> ymove         = 2 + num; //faster old moving speed
	mtmp -> next          = NULL;

	return (mtmp);
}
