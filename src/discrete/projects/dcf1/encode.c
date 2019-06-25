#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	//////////////////////////////////////////////////////////////////
	//
	// Variable declarations
	//
	FILE *in						   = NULL;
	FILE *out						   = NULL;
	char *filename					   = NULL;

	//////////////////////////////////////////////////////////////////
	//
	// Command-line argument checking; if no argument, error out
	//
	if (argc						  == 1)
	{
		fprintf(stderr, "ERROR: Not enough arguments\n");
		fprintf(stderr, "usage:\n");
		fprintf(stderr, "\t%s FILENAME STRIDE\n\n", argv[0]);
		exit (1);
	}

	//////////////////////////////////////////////////////////////////
	//
	// otherwise, argument is file name to encode
	//
	else
	{
		in							   = fopen(argv[1], "r");
		if (in						  == NULL)
		{
			fprintf(stderr, "Error opening '%s' for reading.\n", argv[1]);
			exit (1);
		}
	}

	//////////////////////////////////////////////////////////////////
	//
	// Your dcfX RLE v2 encoding implementation here
	//

	//////////////////////////////////////////////////////////////////
	//
	// close open file pointers
	//
//	fclose(in);
//	fclose(out);

	return(0);
}
