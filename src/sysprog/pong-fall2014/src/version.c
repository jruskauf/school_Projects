#include <stdio.h>
#include "pong.h"

void display_version(void)
{
	fprintf(stdout, "%s %11s\n", PROGNAME, RELEASE);
}
