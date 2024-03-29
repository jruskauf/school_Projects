#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	//////////////////////////////////////////////////////////////////
	//
	// variables
	//
	FILE		  *in					 = NULL;
	FILE		  *out				     = NULL;
	unsigned char  header[12];

	//////////////////////////////////////////////////////////////////
	//
	// process command-line, no arguments get an error
	//
	if (argc							<  2)
	{
		fprintf(stderr, "ERROR: Not enough arguments\n");
		exit(1);
	}

	//////////////////////////////////////////////////////////////////
	//
	// if given, open specified file for reading
	//
	else
	{
		in							     = fopen(argv[1], "r");
		if (in						    == NULL)
		{
			fprintf(stderr, "Error opening '%s' for reading\n", argv[1]);
			exit (1);
		}
	}

	//////////////////////////////////////////////////////////////////
	//
	// your dcfX RLE v2 decoding implementation
	//

	//////////////////////////////////////////////////////////////////
	//
	// close our open files
	//
//	fclose(in);
//	fclose(out);

	return(0);
}
