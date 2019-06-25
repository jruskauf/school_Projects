#include <stdio.h>
#include <stdlib.h>

//Loop that handles creation of the array.  Accepts user input of integer numbers until input of -1
char build (char inarray);


int main ()
{

	//int array[ 1 ];

	char input = 0;
	
	char *usrin = NULL;

	usrin = &input;

	fprintf(stdout, "0. build list\n");
	fprintf(stdout, "1. display list forward\n");
	fprintf(stdout, "2. display list backward\n");
	fprintf(stdout, "3. insert into list\n");
	fprintf(stdout, "4. append into list\n");
	fprintf(stdout, "5. obtain from list\n");
	fprintf(stdout, "6. clear list\n");
	fprintf(stdout, "7. quit\n");
	fprintf(stdout, ">>> ");

	fscanf(stdin, "%hhd", usrin);

	if ( *usrin == 0 ){
		build(*usrin);
		fprintf (stdout, "User input is %d\n", *usrin);
	} else if  (*usrin == 1){
		return (0);
	}
}


char build (char inarray)
{
	return (inarray);
}
